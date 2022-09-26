#include "pch.h"
#include "Enemy.h"
#include "Tomato.h"
#include "TomatoWall.h"
#include "ModelManager.h"
#include "Object.h"
#include "Transform.h"
#include "Collider.h"
#include "Icon.h"

Enemy::Enemy()
	: m_movePhaseTime(50)
	, m_bulletNum(10)
	, m_bulletCapacity(10)
	, m_shotPhaseTime(200.0f)
{

	m_position = VGet(0.0f, 0.0f, 0.0f);
	m_velocity = VGet(1.0f, 1.0f, 1.0f);
	m_dir = VGet(0.0f, 0.0f, 0.0f);
	m_tomatoDir = VGet(0.0f, 0.0f, 0.0f);
	m_moveValue = VGet(0.0f, 0.0f, 0.0f);
	m_avoidVelocity = VGet(0.0f, 0.0f, 0.0f);

	m_moveType = Type::SearchTarget;
	m_aimTargetFlag = false;
	m_moveTime = 0;

	// �A�j���[�V��������
	m_animType = Anim::Idle;
	m_beforeAnimType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
	m_animTime = 0.0f;
	m_animSpeed = 0.3f;
	m_throwSpeed = 1.2f;
	m_pickSpeed = 1.2f;
	m_moveFlag = true;
	m_pickFlag = true;
}

Enemy::~Enemy()
{
	MV1DeleteModel(m_modelHandle);

	//for (int i = 0; i < m_tomatos.size(); i++)
	//{
	//	if (!m_tomatos[i])
	//	{
	//		delete(m_tomatos[i]);
	//	}
	//	m_tomatos.erase(std::cbegin(m_tomatos) + i);
	//	m_tomatos.shrink_to_fit();
	//}
}

void Enemy::Start()
{
	// 3D���f���̓ǂݍ���
	auto tag = m_pParent->GetComponent<Tag>();
	if (tag->tag == ObjectTag::Team1) { m_modelHandle = MV1LoadModel("data/character/man1.mv1"); }
	if (tag->tag == ObjectTag::Team2) { m_modelHandle = MV1LoadModel("data/character/man3.mv1"); }
	if (tag->tag == ObjectTag::Team3) { m_modelHandle = MV1LoadModel("data/character/woman2.mv1"); }
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));
	m_position = m_pParent->GetComponent<Transform>()->position;
	MV1SetPosition(m_modelHandle, m_position);

	m_icon = new Icon(tag);
	m_icon->Init(m_position);
}

void Enemy::Update()
{
	// �G�l�~�[�̍s���p�^�[���𒲂ׂ�
	CheckMovePattern();

	// �A�j���[�V�����̏���
	Animation();

	// �g�}�g�̏���
	ProcessTomato();

	// 3D���f���̉�]�ݒ�
	MV1SetRotationXYZ(m_modelHandle, m_dir);

	// 3D���f���̃|�W�V�����ݒ�
	auto pos = m_pParent->GetComponent<Transform>();
	pos->position = m_position;
	MV1SetPosition(m_modelHandle, m_position);

	m_icon->Update(m_position);
}

void Enemy::Draw()
{
	SetUseLighting(false);
	// 3D���f���̕`��
	MV1DrawModel(m_modelHandle);
	m_icon->Draw();
	//// �g�}�g�`��
	//for (int i = 0; i < m_tomatos.size(); i++)
	//{
	//	m_tomatos[i]->Draw();
	//}
	SetUseLighting(true);

	//DrawFormatString(500, 0, GetColor(255, 255, 255), "EnemyBulletNum:%d", m_bulletNum);
}

void Enemy::SetPlayerPtr(class Object* player)
{
	m_player.push_back(player);
}

void Enemy::SetTomatoWallPtr(TomatoWall* tomatoWall)
{
	m_tomatoWall.push_back(tomatoWall);
}

// @detail �g�}�g�̏����֘A���܂Ƃ߂�����
void Enemy::ProcessTomato()
{
	// �g�}�g�𓊂���
	m_shotTime++;
	// �G���߂Â��Ă�����A����Ă����瓊����̂��L�����Z������
	if (m_shotTime > m_shotPhaseTime && m_moveType == Type::AimTarget && m_bulletNum > 0 && !m_absolutelyMoveFlag)
	{
		//m_tomatos.push_back(new Tomato(m_position, m_tomatoDir));
		m_animType = Anim::Throw;
		m_moveFlag = false;
		if (m_animTime == 0.0f)
		{
			m_pParent->GetComponent<Collider>()->Shot(m_position, m_tomatoDir, m_pParent->GetComponent<Tag>());
			m_bulletNum--;
			m_shotTime = 0.0f;
		}
	}

	// �g�}�g����
	//for (int i = 0; i < m_tomatos.size(); i++)
	//{
	//	m_tomatos[i]->Update();
	//}
	//for (int i = 0; i < m_tomatos.size(); i++)
	//{
	//	// �g�}�g�̐������Ԃ�5.0f�𒴂���ƍ폜
	//	if (m_tomatos[i]->GetTime() > 1.0f)
	//	{
	//		delete(m_tomatos[i]);
	//		m_tomatos.erase(std::cbegin(m_tomatos) + i);
	//		m_tomatos.shrink_to_fit();
	//	}
	//}
}

// @detail �W�I����������ɐ��ʂ�������
// @param aimTargetPos
void Enemy::RotateTowardTarget(VECTOR& aimTargetPos)
{
	VECTOR subVector = VSub(aimTargetPos, m_position);
	double angle = atan2(subVector.x, subVector.z);
	m_dir = VGet(0.0f, angle + DX_PI_F, 0.0f);
	// �g�}�g�������̌����ɍ��킹�Ĕ���
	m_tomatoDir = VAdd(VGet(0.0f, 0.0f, 0.0f), VGet(sin(angle), 0, cos(angle)));
}

void Enemy::Animation()
{
	// �A�j���[�V��������
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

	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);
}

// @detail �A�j���[�V������ύX����֐�
void Enemy::ChangeAnimation()
{
	// �ړ��ł���A�j���[�V�����Ȃ�
	// �������Ă���̂��A�~�܂��Ă���̂��𔻒f
	if (m_moveFlag)
	{
		VECTOR nowPosition = MV1GetPosition(m_modelHandle);
		if (nowPosition.x == m_position.x &&
			nowPosition.y == m_position.y &&
			nowPosition.z == m_position.z)
		{
			m_animType = Anim::Idle;
		}
		else
		{
			m_animType = Anim::Run;
		}
	}

	// �A�j���[�V��������
	if (m_animType != m_beforeAnimType)
	{
		MV1DetachAnim(m_modelHandle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
		m_animTime = 0.0f;
		m_beforeAnimType = m_animType;
	}
}

// @detail �s���p�^�[�����`�F�b�N���Ď��s����
void Enemy::CheckMovePattern()
{
	m_absolutelyMoveFlag = false;
	// �����Ȃ�������A�W�߂ɍs��
	if (m_bulletNum <= 0 && m_moveType != Type::EscapeTarget)
	{
		m_moveType = Type::TomatoCollect;
	}

	// �G��T���Ă��邩�A�_���Ă���Ƃ�
	if (m_moveType == Type::SearchTarget || m_moveType == Type::AimTarget ||
		m_moveType == Type::EscapeTarget)
	{
		CheckTargetMovePattern();
	}
	// �g�}�g�̕Ǐ���
	CheckTomatoWall();
}

// @detail �^�[�Q�b�g�ɑ΂���s���p�^�[���̏���
void Enemy::CheckTargetMovePattern()
{
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	int i = 0;
	for (auto player : m_player)
	{
		// �ǂ̃L�����N�^�[����ԋ߂����𒲂ׂ�
		VECTOR gPos = player->GetComponent<Transform>()->position;
		tmp = GetDistance(gPos, m_position);

		// tmp�����̒l�Ȃ琳�̒l�ɕς���
		if (tmp < 0.0f)
		{
			tmp = tmp * -1.0f;
		}

		// ��������ԋ߂��I�u�W�F�N�g�ԍ���ۑ�����
		if (distance > tmp || distance == 0.0f)
		{
			distance = tmp;
			objectNum = i;

			if (distance < m_targetRangeMax && m_moveType != Type::EscapeTarget)
			{
				m_moveType = Type::AimTarget;
			}

			// tmp��0���������ԋ߂��̂�for���𔲂���
			if (tmp == 0.0f)
			{
				break;
			}
		}
		i++;
	}
	if (m_moveType != Type::EscapeTarget)
	{
		// �^�[�Q�b�g�ɍ��킹�čs������
		Move1Target(m_player[objectNum]);
		if (m_moveType == Type::SearchTarget)
		{
			Move2Target(m_player[objectNum]);
		}
	}
	else  // �^�[�Q�b�g���瓦���鏈��
	{
		Move3Target(m_player[objectNum]);
	}
}

// @detail �^�[�Q�b�g�ɍ��킹�ē�������
// @param object �^�[�Q�b�g�̃Q�[���I�u�W�F�N�g
void Enemy::Move1Target(class Object* player)
{
	VECTOR gPos = player->GetComponent<Transform>()->position;
	double distance = GetDistance(gPos, m_position);

	if (distance >= m_targetRangeMin && distance < m_targetRangeMax)  // ���͈̔͂ɕW�I��������s��
	{
		if (distance > m_targetMoveRangeMax)  // �W�I������Ă�����߂Â�
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

			m_absolutelyMoveFlag = true;
		}
		else if (distance < m_targetMoveRangeMin)  // �W�I���߂Â��Ă����痣���
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
			m_absolutelyMoveFlag = true;
		}

		// �W�I�̕����ɉ�]
		RotateTowardTarget(gPos);
		// �W�I�𔭌�
		m_moveType = Type::AimTarget;
		m_aimTargetFlag = false;
		m_moveTime = 0;
	}
	else
	{
		m_moveType = Type::SearchTarget;
	}
}

// @detail �^�[�Q�b�g��������Ȃ��Ƃ��̏���
// @param object �^�[�Q�b�g�̃Q�[���I�u�W�F�N�g
void Enemy::Move2Target(class Object* player)
{
	// �W�I�̕����Ɉړ����邩��������
	if (!m_aimTargetFlag && m_moveTime == 0)
	{
		srand(rand() % 100);
		int tmp = rand() % 2;

		switch (tmp)
		{
		case 0:  // �W�I�̕����Ɉړ�
			m_aimTargetFlag = true;
			break;
		default:  // �����_���Ɉړ�
			m_moveValue.x = rand() % 3 - 1;
			m_moveValue.z = rand() % 3 - 1;
			break;
		}
	}

	// �W�I�ɋ߂Â�
	if (m_aimTargetFlag)
	{
		VECTOR gPos = player->GetComponent<Transform>()->position;
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

		// �i��ł������������
		RotateTowardTarget(moveVector);
		m_position = moveVector;

		// ���Ԍo�߂Ŏ��̍s���t�F�[�Y��
		m_moveTime++;
		if (m_moveTime > m_movePhaseTime)
		{
			m_aimTargetFlag = false;
			m_moveTime = 0;
		}
	}
	else  // �����_���Ɉړ�
	{
		VECTOR moveVector = VGet(m_position.x + m_moveValue.x, m_position.y, m_position.z + m_moveValue.z);

		// �i��ł������������
		if (moveVector.x != 0.0f && moveVector.z != 0.0f)
		{
			RotateTowardTarget(moveVector);
		}

		m_position = moveVector;

		// ���Ԍo�߂Ŏ��̍s���t�F�[�Y��
		m_moveTime++;
		if (m_moveTime > m_movePhaseTime)
		{
			m_moveTime = 0;
		}
	}
}

// @detail �^�[�Q�b�g���瓦���鏈��
void Enemy::Move3Target(class Object* player)
{
	VECTOR gPos = player->GetComponent<Transform>()->position;
	
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	// �g�}�g�̕ǂ��Ȃ��̂��T��
	for (int i = 0; i < m_tomatoWall.size(); i++)
	{
		// ���̃g�}�g�̕ǂɃg�}�g�͂���̂�
		if (m_tomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// �ǂ̃g�}�g�̕ǂ���ԋ߂����𒲂ׂ�
			VECTOR gPos = m_tomatoWall[i]->GetPosition();
			tmp = GetDistance(gPos, m_position);

			// tmp�����̒l�Ȃ琳�̒l�ɕς���
			if (tmp < 0.0f)
			{
				tmp = tmp * -1.0f;
			}

			
			// ��������ԋ߂��I�u�W�F�N�g�ԍ���ۑ�����
			if (distance > tmp || distance == 0.0f)
			{
				distance = tmp;
				objectNum = i;

				// �g�}�g�̕ǂ���������s���p�^�[����ς���
				m_moveType = Type::TomatoCollect;

				// tmp��0���������ԋ߂��̂�for���𔲂���
				if (tmp == 0.0f)
				{
					break;
				}
			}
		}
	}
	if (m_moveType == Type::TomatoCollect)  // �g�}�g��������ɍs��
	{
		CollectTomato(m_tomatoWall[objectNum]);
	}
	else  // �g�}�g�̕ǂ��Ȃ��Ԃ͓�����
	{
		VECTOR moveVector = VGet(m_position.x, m_position.y, m_position.z);
		double distance = GetDistance(gPos, m_position);

		// �w��͈̔͂܂œ����؂�
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

			// �i��ł������������
			RotateTowardTarget(moveVector);
			m_position = moveVector;
		}
		else  // �^�[�Q�b�g���瓦����͈͂��o����^�[�Q�b�g�̂ق�������
		{
			RotateTowardTarget(gPos);
		}
	}
}

// @detail �g�}�g���������s���p�^�[�������s����
void Enemy::CheckTomatoWall()
{
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	for (int i = 0; i < m_tomatoWall.size(); i++)
	{
		// ���̃g�}�g�̕ǂɃg�}�g�͂���̂�
		if (m_tomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// �ǂ̃g�}�g�̕ǂ���ԋ߂����𒲂ׂ�
			VECTOR gPos = m_tomatoWall[i]->GetPosition();
			tmp = GetDistance(gPos, m_position);

			// tmp�����̒l�Ȃ琳�̒l�ɕς���
			if (tmp < 0.0f)
			{
				tmp = tmp * -1.0f;
			}

			// ��������ԋ߂��I�u�W�F�N�g�ԍ���ۑ�����
			if (distance > tmp || distance == 0.0f)
			{
				distance = tmp;
				objectNum = i;

				// tmp��0���������ԋ߂��̂�for���𔲂���
				if (tmp == 0.0f)
				{
					break;
				}
			}
		}
	}
	// ���ׂẴg�}�g�̕ǂ��Ȃ�������G���瓦���鏈���ɕς���
	if (m_tomatoWall[objectNum]->GetAllTomatoNum() == 0)
	{
		m_moveType = Type::EscapeTarget;
	}
	else if(m_moveType == Type::TomatoCollect)
	{
		CollectTomato(m_tomatoWall[objectNum]);
	}

	AvoidTomatoWall(m_tomatoWall[objectNum]);
}

// @detail �g�}�g��������ɍs������
// @param object ��ԋ߂��g�}�g�̕ǃI�u�W�F�N�g
void Enemy::CollectTomato(TomatoWall* object)
{
	VECTOR gPos = object->GetPosition();
	double distance = GetDistance(gPos, m_position);

	if ((float)distance > object->GetWidthDistance() + 1)  // �W�I������Ă�����߂Â�
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

		// �W�I�̕����ɉ�]
		RotateTowardTarget(gPos);
	}
	else
	{
		if (m_bulletNum == m_bulletCapacity)
		{
			m_moveType = Type::SearchTarget;
		}
		else if(m_bulletNum < m_bulletCapacity)
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

// @detail �g�}�g�̕ǂ�����鏈��
void Enemy::AvoidTomatoWall(TomatoWall* object)
{
	VECTOR mPos = m_position;
	VECTOR gPos = object->GetPosition();

	double distance = GetDistance(gPos, m_position);

	if ((float)distance < object->GetWidthDistance() && m_moveType == Type::TomatoCollect)  // �ǂɋ߂Â��������e�ɏ���
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
	else if((float)distance <= object->GetWidthDistance() &&
		m_moveType != Type::TomatoCollect && !m_avoidWallFlag)  // �ǂƂ̋������߂Â���������
	{
		m_avoidWallFlag = true;

		// �ǂ�����鋗�������������ɔ�����
		if (GetSize(gPos.x, m_position.x) < GetSize(gPos.z, m_position.z))
		{
			if (gPos.x - m_position.x >= 0.0f)
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
			if (gPos.z - m_position.z >= 0.0f)
			{
				m_avoidVelocity = VAdd(m_avoidVelocity, VGet(0.0f, 0.0f, -1.0f));
			}
			else
			{
				m_avoidVelocity = VAdd(m_avoidVelocity, VGet(0.0f, 0.0f, 1.0f));
			}
		}
	}

	// ������t���O����������A������
	if (m_avoidWallFlag)
	{
		m_position = VAdd(m_position, m_avoidVelocity);
		distance = GetDistance(gPos, m_position);

		// ���̋������󂢂��������̂���߂�
		if ((float)distance > object->GetWidthDistance() + 15)
		{
			m_avoidWallFlag = false;
			m_avoidVelocity = VGet(0.0f,0.0f,0.0f);
		}
	}
}

// @detail ���g�Ƒ��̃I�u�W�F�N�g�̋������o��
double Enemy::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}

float Enemy::GetSize(float v1, float v2)
{
	float value = v1 - v2;
	if (value < 0)
	{
		value = value * -1.0f;
	}
	return value;
}
