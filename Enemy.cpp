#include "pch.h"
#include "Enemy.h"
#include "Tomato.h"

Enemy::Enemy(ObjectTag tag, VECTOR position)
{
	// 3Dモデルの読み込み
	m_modelHandle = MV1LoadModel("data/enemy/low_poly_character.mv1");
	MV1SetScale(m_modelHandle, VGet(1.0f, 1.0f, 1.0f));
	m_dir = VGet(0.0f, 0.0f, -1.0f);
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
	for (int i = 0; i < m_objects.size(); i++)
	{
		// オブジェクトに合わせた処理
		switch (m_objects[i]->GetTag())
		{
		case ObjectTag::Player1:
			Move1(m_objects[i]);
			Move2(m_objects[i]);
			break;
		case ObjectTag::Player2:
			Move1(m_objects[i]);
			Move2(m_objects[i]);
			break;
		default:
			break;
		}

		// プレイヤーの向きの方向に向ける
		VECTOR gPos = m_objects[i]->GetPosition();
		VECTOR subVector = VSub(gPos, m_position);
		double angle = atan2(subVector.x, subVector.z);
		MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));

		// トマトを自分の向きに合わせて発射
		m_dir = VGet(subVector.x, 0, subVector.z);
	}

	// トマトを投げる
	m_shotTime++;
	if (m_shotTime > 100.0f)
	{
		m_tomatos.push_back(new Tomato(m_position, m_dir));
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

	// 3Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_position);
}

void Enemy::Draw()
{
	// 3Dモデルの描画
	MV1DrawModel(m_modelHandle);

	// トマト描画
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Draw();
	}
}

void Enemy::SetGameObjectPtr(GameObject* object)
{
	m_objects.push_back(object);
}

// @detail プレイヤーに合わせて動く処理
// @param object プレイヤーのゲームオブジェクト
void Enemy::Move1(GameObject* object)
{
	VECTOR gPos = object->GetPosition();
	double distance = GetDistance(gPos, m_position);

	if (distance > 50.0f)
	{
		if (gPos.x - m_position.x >= 0.0f)
		{
			m_position = VAdd(m_position, VGet(2.0f, 0.0f, 0.0f));
		}
		else
		{
			m_position = VAdd(m_position, VGet(-2.0f, 0.0f, 0.0f));
		}

		if (gPos.z - m_position.z >= 0.0f)
		{
			m_position = VAdd(m_position, VGet(0.0f, 0.0f, 2.0f));
		}
		else
		{
			m_position = VAdd(m_position, VGet(0.0f, 0.0f, -2.0f));
		}
	}
	else if(distance < 30.0f)
	{
		if (gPos.x - m_position.x >= 0.0f)
		{
			m_position = VAdd(m_position, VGet(-2.0f, 0.0f, 0.0f));
		}
		else
		{
			m_position = VAdd(m_position, VGet(2.0f, 0.0f, 0.0f));
		}

		if (gPos.z - m_position.z >= 0.0f)
		{
			m_position = VAdd(m_position, VGet(0.0f, 0.0f, -2.0f));
		}
		else
		{
			m_position = VAdd(m_position, VGet(0.0f, 0.0f, 2.0f));
		}
	}
}

void Enemy::Move2(GameObject* object)
{
}

void Enemy::Move3(GameObject* object)
{
}

// @detail 自身と他のオブジェクトの距離を出す
double Enemy::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}
