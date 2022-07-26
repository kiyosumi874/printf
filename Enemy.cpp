#include "pch.h"
#include "Enemy.h"
#include "Tomato.h"

Enemy::Enemy(ObjectTag tag, VECTOR position)
{
	// 3D���f���̓ǂݍ���
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
		// �I�u�W�F�N�g�ɍ��킹������
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

		// �v���C���[�̌����̕����Ɍ�����
		VECTOR gPos = m_objects[i]->GetPosition();
		VECTOR subVector = VSub(gPos, m_position);
		double angle = atan2(subVector.x, subVector.z);
		MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, angle + DX_PI_F, 0.0f));

		// �g�}�g�������̌����ɍ��킹�Ĕ���
		m_dir = VGet(subVector.x, 0, subVector.z);
	}

	// �g�}�g�𓊂���
	m_shotTime++;
	if (m_shotTime > 100.0f)
	{
		m_tomatos.push_back(new Tomato(m_position, m_dir));
		m_shotTime = 0.0f;
	}

	// �g�}�g����
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Update();
	}
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		// �g�}�g�̐������Ԃ�5.0f�𒴂���ƍ폜
		if (m_tomatos[i]->GetTime() > 1.0f)
		{
			delete(m_tomatos[i]);
			m_tomatos.erase(std::cbegin(m_tomatos) + i);
			m_tomatos.shrink_to_fit();
		}
	}

	// 3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_position);
}

void Enemy::Draw()
{
	// 3D���f���̕`��
	MV1DrawModel(m_modelHandle);

	// �g�}�g�`��
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Draw();
	}
}

void Enemy::SetGameObjectPtr(GameObject* object)
{
	m_objects.push_back(object);
}

// @detail �v���C���[�ɍ��킹�ē�������
// @param object �v���C���[�̃Q�[���I�u�W�F�N�g
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

// @detail ���g�Ƒ��̃I�u�W�F�N�g�̋������o��
double Enemy::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}
