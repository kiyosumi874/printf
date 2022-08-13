#include "pch.h"
#include "Enemy.h"
#include "Tomato.h"
#include "TomatoWall.h"
#include "ModelManager.h"

Enemy::Enemy(ObjectTag tag, VECTOR position)
	: m_movePhaseTime(50)
	, m_bulletNum(10)
	, m_bulletCapacity(10)
{
	// 3Dモデルの読み込み
	ModelManager* model = new ModelManager();
	srand(rand() % 100);
	int modelNum = rand() % MODEL_NUM;
	m_modelHandle = model->GetModelData(modelNum);
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));

	m_position = position;
	m_velocity = VGet(1.0f, 1.0f, 1.0f);
	m_dir = VGet(0.0f, 0.0f, 0.0f);
	m_tomatoDir = VGet(0.0f, 0.0f, 0.0f);
	m_moveValue = VGet(0.0f, 0.0f, 0.0f);

	m_moveType = Type::SearchTarget;
	m_aimTargetFlag = false;
	m_moveTime = 0;

	// アニメーション準備
	m_animType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
	m_animTime = 0.0f;
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);

	for (int i = 0; i < m_tomatos.size(); i++)
	{
		if (!m_tomatos[i])
		{
			delete(m_tomatos[i]);
		}
		m_tomatos.erase(std::cbegin(m_tomatos) + i);
		m_tomatos.shrink_to_fit();
	}
}

void Enemy::Update()
{
	CheckMovePattern();

	// アニメーション処理
	ChangeAnimation();
	m_animTime += 0.3f;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}
	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);

	// トマトの処理
	ProcessTomato();

	// 3Dモデルの回転設定
	MV1SetRotationXYZ(m_modelHandle, m_dir);

	// 3Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_position);
}

void Enemy::Draw()
{
	SetUseLighting(false);
	// 3Dモデルの描画
	MV1DrawModel(m_modelHandle);

	// トマト描画
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Draw();
	}
	SetUseLighting(true);

	DrawFormatString(500, 0, GetColor(255, 255, 255), "EnemyBulletNum:%d", m_bulletNum);
}

void Enemy::SetPlayerPtr(GameObject* player)
{
	m_player.push_back(player);
}

void Enemy::SetTomatoWallPtr(TomatoWall* tomatoWall)
{
	m_tomatoWall.push_back(tomatoWall);
}

// @detail トマトの処理関連をまとめたもの
void Enemy::ProcessTomato()
{
	// トマトを投げる
	m_shotTime++;
	if (m_shotTime > 100.0f && m_moveType == Type::AimTarget && m_bulletNum > 0)
	{
		m_tomatos.push_back(new Tomato(m_position, m_tomatoDir));
		m_bulletNum--;
		m_shotTime = 0.0f;
	}

	// トマト処理
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Update();
	}
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		// トマトの生存時間が5.0fを超えると削除
		if (m_tomatos[i]->GetTime() > 1.0f)
		{
			delete(m_tomatos[i]);
			m_tomatos.erase(std::cbegin(m_tomatos) + i);
			m_tomatos.shrink_to_fit();
		}
	}
}

// @detail 標的がいる方向に正面を向ける
// @param aimTargetPos
void Enemy::RotateTowardTarget(VECTOR& aimTargetPos)
{
	VECTOR subVector = VSub(aimTargetPos, m_position);
	double angle = atan2(subVector.x, subVector.z);
	m_dir = VGet(0.0f, angle + DX_PI_F, 0.0f);
	// トマトを自分の向きに合わせて発射
	m_tomatoDir = VAdd(VGet(0.0f, 0.0f, 0.0f), VGet(sin(angle), 0, cos(angle)));
}

// @detail アニメーションを変更する関数
void Enemy::ChangeAnimation()
{
	// 今動いているのか、止まっているのかを判断
	VECTOR nowPosition = MV1GetPosition(m_modelHandle);
	if (nowPosition.x == m_position.x &&
		nowPosition.y == m_position.y &&
		nowPosition.z == m_position.z)
	{
		m_moveFlag = false;
	}
	else
	{
		m_moveFlag = true;
	}

	// アニメーション処理
	if (!m_moveFlag && m_animType != Anim::Idle)  // 止まるアニメーション
	{
		m_animTime = 0.0f;
		m_animType = Anim::Idle;
		MV1DetachAnim(m_modelHandle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
		m_animTime = 0.0f;
	}
	else if (m_moveFlag && m_animType != Anim::Run)  // 走るアニメーション
	{
		m_animTime = 0.0f;
		m_animType = Anim::Run;
		MV1DetachAnim(m_modelHandle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
		m_animTime = 0.0f;
	}
}

// @detail 行動パターンをチェックして実行する
void Enemy::CheckMovePattern()
{
	// 球がなかったら、集めに行く
	if (m_bulletNum <= 0 && m_moveType != Type::EscapeTarget)
	{
		m_moveType = Type::TomatoCollect;
	}

	// 敵を探しているか、狙っているとき
	if (m_moveType == Type::SearchTarget || m_moveType == Type::AimTarget ||
		m_moveType == Type::EscapeTarget)
	{
		CheckTargetMovePattern();
	}
	// トマトを回収しに行くとき
	else if (m_moveType == Type::TomatoCollect)
	{
		CheckTomatoWall();
	}
}

// @detail ターゲットに対する行動パターンの処理
void Enemy::CheckTargetMovePattern()
{
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	for (int i = 0; i < m_player.size(); i++)
	{
		// どのキャラクターが一番近いかを調べる
		VECTOR gPos = m_player[i]->GetPosition();
		tmp = GetDistance(gPos, m_position);

		// tmpが負の値なら正の値に変える
		if (tmp < 0.0f)
		{
			tmp = tmp * -1.0f;
		}

		// 距離が一番近いオブジェクト番号を保存する
		if (distance > tmp || distance == 0.0f)
		{
			distance = tmp;
			objectNum = i;

			if (distance < m_targetRangeMax && m_moveType != Type::EscapeTarget)
			{
				m_moveType = Type::AimTarget;
			}

			// tmpが0だったら一番近いのでfor文を抜ける
			if (tmp == 0.0f)
			{
				break;
			}
		}
	}
	if (m_moveType != Type::EscapeTarget)
	{
		// ターゲットに合わせて行動する
		TargetMove1(m_player[objectNum]);
		if (m_moveType == Type::SearchTarget)
		{
			TargetMove2(m_player[objectNum]);
		}
	}
	else  // ターゲットから逃げる処理
	{
		TargetMove3(m_player[objectNum]);
	}
}

// @detail ターゲットに合わせて動く処理
// @param object ターゲットのゲームオブジェクト
void Enemy::TargetMove1(GameObject* object)
{
	VECTOR gPos = object->GetPosition();
	double distance = GetDistance(gPos, m_position);

	if (distance >= m_targetRangeMin && distance < m_targetRangeMax)  // この範囲に標的がいたら行動
	{
		if (distance > m_targetMoveRangeMax)  // 標的が離れていたら近づく
		{
			if (gPos.x - m_position.x >= 0.0f)
			{
				m_position = VAdd(m_position, VGet(0.5f, 0.0f, 0.0f));
			}
			else
			{
				m_position = VAdd(m_position, VGet(-0.5f, 0.0f, 0.0f));
			}

			if (gPos.z - m_position.z >= 0.0f)
			{
				m_position = VAdd(m_position, VGet(0.0f, 0.0f, 0.5f));
			}
			else
			{
				m_position = VAdd(m_position, VGet(0.0f, 0.0f, -0.5f));
			}
		}
		else if (distance < m_targetMoveRangeMin)  // 標的が近づいてきたら離れる
		{
			if (gPos.x - m_position.x >= 0.0f)
			{
				m_position = VAdd(m_position, VGet(-0.5f, 0.0f, 0.0f));
			}
			else
			{
				m_position = VAdd(m_position, VGet(0.5f, 0.0f, 0.0f));
			}

			if (gPos.z - m_position.z >= 0.0f)
			{
				m_position = VAdd(m_position, VGet(0.0f, 0.0f, -0.5f));
			}
			else
			{
				m_position = VAdd(m_position, VGet(0.0f, 0.0f, 0.5f));
			}
		}

		// 標的の方向に回転
		RotateTowardTarget(gPos);
		// 標的を発見
		m_moveType = Type::AimTarget;
		m_aimTargetFlag = false;
		m_moveTime = 0;
	}
	else
	{
		m_moveType = Type::SearchTarget;
	}
}

// @detail ターゲットが見つからないときの処理
// @param object ターゲットのゲームオブジェクト
void Enemy::TargetMove2(GameObject* object)
{
	// 標的の方向に移動するか乱数決定
	if (!m_aimTargetFlag && m_moveTime == 0)
	{
		srand(rand() % 100);
		int tmp = rand() % 2;

		switch (tmp)
		{
		case 0:  // 標的の方向に移動
			m_aimTargetFlag = true;
			break;
		default:  // ランダムに移動
			m_moveValue.x = rand() % 3 - 1;
			m_moveValue.z = rand() % 3 - 1;
			break;
		}
	}

	// 標的に近づく
	if (m_aimTargetFlag)
	{
		VECTOR gPos = object->GetPosition();
		VECTOR moveVector = VGet(m_position.x + m_moveValue.x, m_position.y, m_position.z + m_moveValue.z);

		if (gPos.x > m_position.x)
		{
			moveVector.x += m_velocity.x;
		}
		else if (gPos.x < m_position.x)
		{
			moveVector.x -= m_velocity.x;
		}

		if (gPos.z > m_position.z)
		{
			moveVector.z += m_velocity.z;
		}
		else if (gPos.z < m_position.z)
		{
			moveVector.z -= m_velocity.z;
		}

		// 進んでいる方向を向く
		RotateTowardTarget(moveVector);
		m_position = moveVector;

		// 時間経過で次の行動フェーズへ
		m_moveTime++;
		if (m_moveTime > m_movePhaseTime)
		{
			m_aimTargetFlag = false;
			m_moveTime = 0;
		}
	}
	else  // ランダムに移動
	{
		VECTOR moveVector = VGet(m_position.x + m_moveValue.x, m_position.y, m_position.z + m_moveValue.z);

		// 進んでいる方向を向く
		if (moveVector.x != 0.0f && moveVector.z != 0.0f)
		{
			RotateTowardTarget(moveVector);
		}

		m_position = moveVector;

		// 時間経過で次の行動フェーズへ
		m_moveTime++;
		if (m_moveTime > m_movePhaseTime)
		{
			m_moveTime = 0;
		}
	}
}

// @detail ターゲットから逃げる処理
void Enemy::TargetMove3(GameObject* object)
{
	VECTOR gPos = object->GetPosition();
	
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	// トマトの壁がないのか探す
	for (int i = 0; i < m_tomatoWall.size(); i++)
	{
		// そのトマトの壁にトマトはあるのか
		if (m_tomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// どのトマトの壁が一番近いかを調べる
			VECTOR gPos = m_tomatoWall[i]->GetPosition();
			tmp = GetDistance(gPos, m_position);

			// tmpが負の値なら正の値に変える
			if (tmp < 0.0f)
			{
				tmp = tmp * -1.0f;
			}

			
			// 距離が一番近いオブジェクト番号を保存する
			if (distance > tmp || distance == 0.0f)
			{
				distance = tmp;
				objectNum = i;

				// トマトの壁があったら行動パターンを変える
				m_moveType = Type::TomatoCollect;

				// tmpが0だったら一番近いのでfor文を抜ける
				if (tmp == 0.0f)
				{
					break;
				}
			}
		}
	}
	if (m_moveType == Type::TomatoCollect)  // トマトを回収しに行く
	{
		TomatoCollectMove(m_tomatoWall[objectNum]);
	}
	else  // トマトの壁がない間は逃げる
	{
		VECTOR moveVector = VGet(m_position.x, m_position.y, m_position.z);
		double distance = GetDistance(gPos, m_position);

		// 指定の範囲まで逃げ切る
		if (distance < m_targetEscapeRange)
		{
			if (gPos.x - m_position.x >= 0.0f)
			{
				moveVector.x -= m_velocity.x;
			}
			else
			{
				moveVector.x += m_velocity.x;
			}

			if (gPos.z - m_position.z >= 0.0f)
			{
				moveVector.z -= m_velocity.z;
			}
			else
			{
				moveVector.z += m_velocity.z;
			}

			// 進んでいる方向を向く
			RotateTowardTarget(moveVector);
			m_position = moveVector;
		}
		else  // ターゲットから逃げる範囲を出たらターゲットのほうを向く
		{
			RotateTowardTarget(gPos);
		}
	}
}

// @detail トマトを回収する行動パターンを実行する
void Enemy::CheckTomatoWall()
{
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	for (int i = 0; i < m_tomatoWall.size(); i++)
	{
		// そのトマトの壁にトマトはあるのか
		if (m_tomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// どのトマトの壁が一番近いかを調べる
			VECTOR gPos = m_tomatoWall[i]->GetPosition();
			tmp = GetDistance(gPos, m_position);

			// tmpが負の値なら正の値に変える
			if (tmp < 0.0f)
			{
				tmp = tmp * -1.0f;
			}

			// 距離が一番近いオブジェクト番号を保存する
			if (distance > tmp || distance == 0.0f)
			{
				distance = tmp;
				objectNum = i;

				// tmpが0だったら一番近いのでfor文を抜ける
				if (tmp == 0.0f)
				{
					break;
				}
			}
		}
	}
	// すべてのトマトの壁がなかったら敵から逃げる処理に変える
	if (m_tomatoWall[objectNum]->GetAllTomatoNum() == 0)
	{
		m_moveType = Type::EscapeTarget;
	}
	else
	{
		TomatoCollectMove(m_tomatoWall[objectNum]);
	}
}

// @detail トマトを回収しに行く処理
// @param object 一番近いトマトの壁オブジェクト
void Enemy::TomatoCollectMove(TomatoWall* object)
{
	VECTOR gPos = object->GetPosition();
	double distance = GetDistance(gPos, m_position);

	if (distance > object->GetWidthDistance())  // 標的が離れていたら近づく
	{
		if (gPos.x - m_position.x >= 0.0f)
		{
			m_position = VAdd(m_position, VGet(0.5f, 0.0f, 0.0f));
		}
		else
		{
			m_position = VAdd(m_position, VGet(-0.5f, 0.0f, 0.0f));
		}

		if (gPos.z - m_position.z >= 0.0f)
		{
			m_position = VAdd(m_position, VGet(0.0f, 0.0f, 0.5f));
		}
		else
		{
			m_position = VAdd(m_position, VGet(0.0f, 0.0f, -0.5f));
		}

		// 標的の方向に回転
		RotateTowardTarget(gPos);
	}
	else
	{
		m_bulletNum++;
		object->DecreaseAllTomatoNum();

		if (m_bulletNum == m_bulletCapacity)
		{
			m_moveType = Type::SearchTarget;
		}
	}
}

// @detail 自身と他のオブジェクトの距離を出す
double Enemy::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}