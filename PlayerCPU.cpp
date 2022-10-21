#include "pch.h"
#include "Tag.h"
#include "PlayerCPU.h"
#include "Tomato.h"
#include "TomatoWallManager.h"
#include "Object.h"
#include "Transform.h"
#include "Icon.h"
#include "BoxCollider.h"

PlayerCPU::PlayerCPU()
	: Human()
	, m_movePhaseTime(50)
	, m_shotPhaseTime(200.0f)
{
	m_velocity = VGet(1.0f, 1.0f, 1.0f);
	m_dir = VGet(0.0f, 0.0f, 0.0f);
	m_tomatoDir = VGet(0.0f, 0.0f, 0.0f);
	m_moveValue = VGet(0.0f, 0.0f, 0.0f);
	m_avoidVelocity = VGet(0.0f, 0.0f, 0.0f);

	m_moveType = Type::SearchTarget;
	m_aimTargetFlag = false;
	m_moveTime = 0;

	// アニメーション準備
	m_beforeAnimType = Anim::Idle;
	m_animTime = 0.0f;
	m_animSpeed = 0.3f;
	m_throwSpeed = 1.2f;
	m_pickSpeed = 1.2f;
	m_moveFlag = true;
	m_pickFlag = true;
}

PlayerCPU::~PlayerCPU()
{
}

void PlayerCPU::Start()
{
	if (m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if (m_pBox == nullptr)
	{
		m_pBox = m_pParent->GetCollider<BoxCollider>();
		m_pBox->Init(m_var.pos, m_pBox->SetOwner(this), m_pTag, CollisionInfo::CollisionType::Box);
		m_pBox->SetOnCollisionFlag(true);
	}

	if (m_pTag->tag == ObjectTag::Team1)
	{
		m_modelName = AssetManager::ModelName::Team1;
	}
	if (m_pTag->tag == ObjectTag::Team2)
	{
		m_modelName = AssetManager::ModelName::Team2;
	}
}

void PlayerCPU::Update()
{
	// エネミーの行動パターンを調べる
	CheckMovePattern();

	// アニメーションの処理
	Animation();

	// トマトの処理
	ProcessTomato();

	m_var.rotate = m_dir;
	// 3Dモデルの回転設定
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);

	// 3Dモデルのポジション設定
	m_var.pos = m_pTransform->position;
	MV1SetPosition(m_var.handle, m_var.pos);

	m_pIcon->SetOwnerPosition(m_var.pos);
	// 座標が足元にあるため、高さをモデルの半分の位置に補正をかけてます
	m_pBox->UpdatePosition(VGet(m_var.pos.x, m_var.pos.y + m_pBox->GetWorldBox()->m_scale.y / 2.0f, m_var.pos.z));
}

void PlayerCPU::Draw()
{
	SetUseLighting(false);
	// 3Dモデルの描画
	MV1DrawModel(m_var.handle);
	m_pIcon->Draw();
	SetUseLighting(true);
}

void PlayerCPU::OnCollisionEnter(ColliderComponent* ownColl, ColliderComponent* otherColl)
{
	if (otherColl->GetTag() != nullptr)
	{
		if (m_pTag->tag == ObjectTag::Team1 && otherColl->GetTag()->tag == ObjectTag::Team2Tomato ||
			m_pTag->tag == ObjectTag::Team1 && otherColl->GetTag()->tag == ObjectTag::Team3Tomato ||
			m_pTag->tag == ObjectTag::Team2 && otherColl->GetTag()->tag == ObjectTag::Team1Tomato ||
			m_pTag->tag == ObjectTag::Team2 && otherColl->GetTag()->tag == ObjectTag::Team3Tomato)
		{
			return;
		}
		if (m_pTag->tag == ObjectTag::Team1 && otherColl->GetTag()->tag == ObjectTag::Team1Tomato ||
			m_pTag->tag == ObjectTag::Team2 && otherColl->GetTag()->tag == ObjectTag::Team2Tomato)
		{
			return;
		}
	}
	
	m_pTransform->position = VAdd(m_pTransform->position, ownColl->GetCollisionInfo().m_fixVec);
}

void PlayerCPU::SetAimTargetPtr(class Object* target)
{
	m_target.push_back(target);
}

// @detail トマトの処理関連をまとめたもの
void PlayerCPU::ProcessTomato()
{
	// トマトを投げる
	m_shotTime++;
	if (m_animType != Anim::Throw)
	{
		// 敵が近づいていたり、離れていたら投げるのをキャンセルする
		if (m_shotTime > m_shotPhaseTime && m_moveType == Type::AimTarget && m_bulletNum > 0 && !m_absolutelyMoveFlag)
		{
			for (auto tomato : m_pTomato)
			{
				if (tomato->GetActive())
				{
					continue;
				}
				m_animType = Anim::Throw;
				m_moveFlag = false;
				if (m_animTime == 0.0f)
				{
					m_bulletNum--;
					m_shotTime = 0.0f;
				}
				// 消えているトマトをアクティブにする
				tomato->ShotTomato(m_pTransform->position, m_tomatoDir, m_pTag);
				break;
			}
		}
	}
}

// @detail 標的がいる方向に正面を向ける
// @param aimTargetPos
void PlayerCPU::RotateTowardTarget(VECTOR& aimTargetPos)
{
	VECTOR subVector = VSub(aimTargetPos, m_pTransform->position);
	double angle = atan2(subVector.x, subVector.z);
	m_dir = VGet(0.0f, angle + DX_PI_F, 0.0f);
	// トマトを自分の向きに合わせて発射
	m_tomatoDir = VAdd(VGet(0.0f, 0.0f, 0.0f), VGet(sin(angle), 0, cos(angle)));
}

void PlayerCPU::Animation()
{
	// アニメーション処理
	if (m_animType == Anim::Throw)
	{
		m_animTime += m_throwSpeed;
	}
	else if (m_animType == Anim::Pick)
	{
		m_animTime += m_pickSpeed;
	}
	else
	{
		m_animTime += m_animSpeed;
	}

	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
		if (!m_moveFlag)
		{
			if (m_animType == Anim::Pick)
			{
				m_pickFlag = false;
			}
			m_animType = Anim::None;
			m_moveFlag = true;
		}
	}
	ChangeAnimation();

	MV1SetAttachAnimTime(m_var.handle, m_animIndex, m_animTime);
}

// @detail アニメーションを変更する関数
void PlayerCPU::ChangeAnimation()
{
	// 移動できるアニメーションなら
	// 今動いているのか、止まっているのかを判断
	if (m_moveFlag)
	{
		VECTOR nowPosition = MV1GetPosition(m_var.handle);
		if (nowPosition.x == m_pTransform->position.x &&
			nowPosition.y == m_pTransform->position.y &&
			nowPosition.z == m_pTransform->position.z)
		{
			m_animType = Anim::Idle;
		}
		else
		{
			m_animType = Anim::Run;
		}
	}

	// アニメーション処理
	if (m_animType != m_beforeAnimType)
	{
		MV1DetachAnim(m_var.handle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_var.handle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_var.handle, m_animType);
		m_animTime = 0.0f;
		m_beforeAnimType = m_animType;
	}
}

// @detail 行動パターンをチェックして実行する
void PlayerCPU::CheckMovePattern()
{
	m_absolutelyMoveFlag = false;
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
	// トマトの壁処理
	CheckTomatoWall();
}

// @detail ターゲットに対する行動パターンの処理
void PlayerCPU::CheckTargetMovePattern()
{
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	int i = 0;
	for (auto target : m_target)
	{
		// どのキャラクターが一番近いかを調べる
		VECTOR gPos = target->GetComponent<Transform>()->position;
		tmp = GetDistance(gPos, m_pTransform->position);

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
		i++;
	}
	if (m_moveType != Type::EscapeTarget)
	{
		// ターゲットに合わせて行動する
		Move1Target(m_target[objectNum]);
		if (m_moveType == Type::SearchTarget)
		{
			Move2Target(m_target[objectNum]);
		}
	}
	else  // ターゲットから逃げる処理
	{
		Move3Target(m_target[objectNum]);
	}
}

// @detail ターゲットに合わせて動く処理
// @param object ターゲットのゲームオブジェクト
void PlayerCPU::Move1Target(class Object* player)
{
	VECTOR gPos = player->GetComponent<Transform>()->position;
	double distance = GetDistance(gPos, m_pTransform->position);

	if (distance >= m_targetRangeMin && distance < m_targetRangeMax)  // この範囲に標的がいたら行動
	{
		if (distance > m_targetMoveRangeMax)  // 標的が離れていたら近づく
		{
			if (gPos.x - m_pTransform->position.x >= 0.0f)
			{
				m_pTransform->position = VAdd(m_pTransform->position, VGet(0.5f, 0.0f, 0.0f));
			}
			else
			{
				m_pTransform->position = VAdd(m_pTransform->position, VGet(-0.5f, 0.0f, 0.0f));
			}

			if (gPos.z - m_pTransform->position.z >= 0.0f)
			{
				m_pTransform->position = VAdd(m_pTransform->position, VGet(0.0f, 0.0f, 0.5f));
			}
			else
			{
				m_pTransform->position = VAdd(m_pTransform->position, VGet(0.0f, 0.0f, -0.5f));
			}

			m_absolutelyMoveFlag = true;
		}
		else if (distance < m_targetMoveRangeMin)  // 標的が近づいてきたら離れる
		{
			if (gPos.x - m_pTransform->position.x >= 0.0f)
			{
				m_pTransform->position = VAdd(m_pTransform->position, VGet(-0.5f, 0.0f, 0.0f));
			}
			else
			{
				m_pTransform->position = VAdd(m_pTransform->position, VGet(0.5f, 0.0f, 0.0f));
			}

			if (gPos.z - m_pTransform->position.z >= 0.0f)
			{
				m_pTransform->position = VAdd(m_pTransform->position, VGet(0.0f, 0.0f, -0.5f));
			}
			else
			{
				m_pTransform->position = VAdd(m_pTransform->position, VGet(0.0f, 0.0f, 0.5f));
			}
			m_absolutelyMoveFlag = true;
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
void PlayerCPU::Move2Target(class Object* player)
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
		VECTOR gPos = player->GetComponent<Transform>()->position;
		VECTOR moveVector = VGet(m_pTransform->position.x + m_moveValue.x, m_pTransform->position.y, m_pTransform->position.z + m_moveValue.z);

		if (gPos.x > m_pTransform->position.x)
		{
			moveVector.x += m_velocity.x;
		}
		else if (gPos.x < m_pTransform->position.x)
		{
			moveVector.x -= m_velocity.x;
		}

		if (gPos.z > m_pTransform->position.z)
		{
			moveVector.z += m_velocity.z;
		}
		else if (gPos.z < m_pTransform->position.z)
		{
			moveVector.z -= m_velocity.z;
		}

		// 進んでいる方向を向く
		RotateTowardTarget(moveVector);
		m_pTransform->position = moveVector;

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
		VECTOR moveVector = VGet(m_pTransform->position.x + m_moveValue.x, m_pTransform->position.y, m_pTransform->position.z + m_moveValue.z);

		// 進んでいる方向を向く
		if (moveVector.x != 0.0f && moveVector.z != 0.0f)
		{
			RotateTowardTarget(moveVector);
		}

		m_pTransform->position = moveVector;

		// 時間経過で次の行動フェーズへ
		m_moveTime++;
		if (m_moveTime > m_movePhaseTime)
		{
			m_moveTime = 0;
		}
	}
}

// @detail ターゲットから逃げる処理
void PlayerCPU::Move3Target(class Object* player)
{
	VECTOR gPos = player->GetComponent<Transform>()->position;

	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	// トマトの壁がないのか探す
	for (int i = 0; i < m_pTomatoWall.size(); i++)
	{
		// そのトマトの壁にトマトはあるのか
		if (m_pTomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// どのトマトの壁が一番近いかを調べる
			VECTOR gPos = m_pTomatoWall[i]->GetPosition();
			tmp = GetDistance(gPos, m_pTransform->position);

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
		CollectTomato(m_pTomatoWall[objectNum]);
	}
	else  // トマトの壁がない間は逃げる
	{
		VECTOR moveVector = VGet(m_pTransform->position.x, m_pTransform->position.y, m_pTransform->position.z);
		double distance = GetDistance(gPos, m_pTransform->position);

		// 指定の範囲まで逃げ切る
		if (distance < m_targetEscapeRange)
		{
			if (gPos.x - m_pTransform->position.x >= 0.0f)
			{
				moveVector.x -= m_velocity.x;
			}
			else
			{
				moveVector.x += m_velocity.x;
			}

			if (gPos.z - m_pTransform->position.z >= 0.0f)
			{
				moveVector.z -= m_velocity.z;
			}
			else
			{
				moveVector.z += m_velocity.z;
			}

			// 進んでいる方向を向く
			RotateTowardTarget(moveVector);
			m_pTransform->position = moveVector;
		}
		else  // ターゲットから逃げる範囲を出たらターゲットのほうを向く
		{
			RotateTowardTarget(gPos);
		}
	}
}

// @detail トマトを回収する行動パターンを実行する
void PlayerCPU::CheckTomatoWall()
{
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	for (int i = 0; i < m_pTomatoWall.size(); i++)
	{
		// そのトマトの壁にトマトはあるのか
		if (m_pTomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// どのトマトの壁が一番近いかを調べる
			VECTOR gPos = m_pTomatoWall[i]->GetPosition();
			tmp = GetDistance(gPos, m_pTransform->position);

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
	if (m_pTomatoWall[objectNum]->GetAllTomatoNum() == 0)
	{
		m_moveType = Type::EscapeTarget;
	}
	else if (m_moveType == Type::TomatoCollect)
	{
		CollectTomato(m_pTomatoWall[objectNum]);
	}

	AvoidTomatoWall(m_pTomatoWall[objectNum]);
}

// @detail トマトを回収しに行く処理
// @param object 一番近いトマトの壁オブジェクト
void PlayerCPU::CollectTomato(TomatoWallManager* object)
{
	VECTOR gPos = object->GetPosition();
	double distance = GetDistance(gPos, m_pTransform->position);

	if ((float)distance > object->GetWidthDistance() + 1)  // 標的が離れていたら近づく
	{
		if (gPos.x - m_pTransform->position.x >= 0.0f)
		{
			m_pTransform->position = VAdd(m_pTransform->position, VGet(0.5f, 0.0f, 0.0f));
		}
		else
		{
			m_pTransform->position = VAdd(m_pTransform->position, VGet(-0.5f, 0.0f, 0.0f));
		}

		if (gPos.z - m_pTransform->position.z >= 0.0f)
		{
			m_pTransform->position = VAdd(m_pTransform->position, VGet(0.0f, 0.0f, 0.5f));
		}
		else
		{
			m_pTransform->position = VAdd(m_pTransform->position, VGet(0.0f, 0.0f, -0.5f));
		}

		// 標的の方向に回転
		RotateTowardTarget(gPos);
	}
	else
	{
		if (m_bulletNum == m_bulletCapacity)
		{
			m_moveType = Type::SearchTarget;
		}
		else if (m_bulletNum < m_bulletCapacity)
		{
			if (!m_pickFlag)
			{
				m_pickFlag = true;
				m_bulletNum++;
				object->DecreaseAllTomatoNum();
			}
			m_animType = Anim::Pick;
			m_moveFlag = false;
		}
	}
}

// @detail トマトの壁を避ける処理
void PlayerCPU::AvoidTomatoWall(TomatoWallManager* object)
{
	VECTOR mPos = m_pTransform->position;
	VECTOR gPos = object->GetPosition();

	double distance = GetDistance(gPos, m_pTransform->position);

	if ((float)distance < object->GetWidthDistance() && m_moveType == Type::TomatoCollect)  // 壁に近づきすぎ内容に処理
	{
		if (gPos.x - m_pTransform->position.x >= 0.0f)
		{
			m_pTransform->position = VAdd(m_pTransform->position, VGet(-0.5f, 0.0f, 0.0f));
		}
		else
		{
			m_pTransform->position = VAdd(m_pTransform->position, VGet(0.5f, 0.0f, 0.0f));
		}

		if (gPos.z - m_pTransform->position.z >= 0.0f)
		{
			m_pTransform->position = VAdd(m_pTransform->position, VGet(0.0f, 0.0f, -0.5f));
		}
		else
		{
			m_pTransform->position = VAdd(m_pTransform->position, VGet(0.0f, 0.0f, 0.5f));
		}
	}
	else if ((float)distance <= object->GetWidthDistance() &&
		m_moveType != Type::TomatoCollect && !m_avoidWallFlag)  // 壁との距離が近づきすぎたら
	{
		m_avoidWallFlag = true;

		// 壁を避ける距離が小さい方に避ける
		if (GetSize(gPos.x, m_pTransform->position.x) < GetSize(gPos.z, m_pTransform->position.z))
		{
			if (gPos.x - m_pTransform->position.x >= 0.0f)
			{
				m_avoidVelocity = VAdd(m_avoidVelocity, VGet(-1.0f, 0.0f, 0.0f));
			}
			else
			{
				m_avoidVelocity = VAdd(m_avoidVelocity, VGet(1.0f, 0.0f, 0.0f));
			}
		}
		else
		{
			if (gPos.z - m_pTransform->position.z >= 0.0f)
			{
				m_avoidVelocity = VAdd(m_avoidVelocity, VGet(0.0f, 0.0f, -1.0f));
			}
			else
			{
				m_avoidVelocity = VAdd(m_avoidVelocity, VGet(0.0f, 0.0f, 1.0f));
			}
		}
	}

	// 避けるフラグがたったら、避ける
	if (m_avoidWallFlag)
	{
		m_pTransform->position = VAdd(m_pTransform->position, m_avoidVelocity);
		distance = GetDistance(gPos, m_pTransform->position);

		// 一定の距離が空いたら避けるのをやめる
		if ((float)distance > object->GetWidthDistance() + 15)
		{
			m_avoidWallFlag = false;
			m_avoidVelocity = VGet(0.0f, 0.0f, 0.0f);
		}
	}
}
