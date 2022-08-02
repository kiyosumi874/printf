#include "pch.h"
#include "Enemy.h"
#include "Tomato.h"

Enemy::Enemy(ObjectTag tag, VECTOR position)
	: m_movePhaseTime(50)
{
	// 3Dモデルの読み込み
	m_modelHandle = MV1LoadModel("data/enemy/low_poly_character.mv1");
	MV1SetScale(m_modelHandle, VGet(1.0f, 1.0f, 1.0f));
	m_velocity = VGet(1.0f, 1.0f, 1.0f);
	m_dir = VGet(0.0f, 0.0f, 0.0f);
	m_tomatoDir = VGet(0.0f, 0.0f, 0.0f);
	m_moveValue = VGet(0.0f, 0.0f, 0.0f);

	m_targetFoundFlag = false;
	m_aimTargetFlag = false;
	m_moveTime = 0;
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
	int objectNum = 0;
	float distance = 0;
	int tmp = 0;
	for (int i = 0; i < m_objects.size(); i++)
	{
		// どのキャラクターが一番近いかを調べる
		VECTOR gPos = m_objects[i]->GetPosition();
		tmp = GetDistance(gPos, m_position);

		// tmpが負の値なら正の値に変える
		if (tmp < 0)
		{
			tmp = tmp * -1;
		}

		// 距離が一番近いオブジェクト番号を保存する
		if (distance > tmp && distance == 0)
		{
			distance = tmp;
			objectNum = i;
		}
	}
	// オブジェクトに合わせて行動する
	Move1(m_objects[objectNum]);
	if (!m_targetFoundFlag)
	{
		Move2(m_objects[objectNum]);
	}

	// トマトの処理
	ProcessTomato();

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
}

void Enemy::SetGameObjectPtr(GameObject* object)
{
	m_objects.push_back(object);
}

// @detail トマトの処理関連をまとめたもの
void Enemy::ProcessTomato()
{
	// トマトを投げる
	m_shotTime++;
	if (m_shotTime > 100.0f && m_targetFoundFlag)
	{
		m_tomatos.push_back(new Tomato(m_position, m_tomatoDir));
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

// @detail プレイヤーに合わせて動く処理
// @param object プレイヤーのゲームオブジェクト
void Enemy::Move1(GameObject* object)
{
	VECTOR gPos = object->GetPosition();
	double distance = GetDistance(gPos, m_position);

	if (distance >= 0.0f && distance < 150.0f)  // この範囲に標的がいたら行動
	{
		if (distance > 100.0f)  // 標的が離れていたら近づく
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
		else if (distance < 50.0f)  // 標的が近づいてきたら離れる
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
		m_targetFoundFlag = true;
		m_aimTargetFlag = false;
		m_moveTime = 0;
	}
	else
	{
		m_targetFoundFlag = false;
	}
}

void Enemy::Move2(GameObject* object)
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

void Enemy::Move3(GameObject* object)
{
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

// @detail 自身と他のオブジェクトの距離を出す
double Enemy::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}
