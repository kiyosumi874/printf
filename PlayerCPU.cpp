#include "pch.h"
#include "PlayerCPU.h"
#include "Tomato.h"
#include "TomatoWallManager.h"
#include "Object.h"
#include "Transform.h"
#include "Collider.h"
#include "Icon.h"

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

	// �A�j���[�V��������
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
	// �G�l�~�[�̍s���p�^�[���𒲂ׂ�
	CheckMovePattern();

	// �A�j���[�V�����̏���
	Animation();

	// �g�}�g�̏���
	ProcessTomato();

	m_var.rotate = m_dir;
	// 3D���f���̉�]�ݒ�
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);

	// 3D���f���̃|�W�V�����ݒ�
	m_var.pos = m_pTransform->position;
	MV1SetPosition(m_var.handle, m_var.pos);

	m_pIcon->Update(m_var.pos);
}

void PlayerCPU::Draw()
{
	SetUseLighting(false);
	// 3D���f���̕`��
	MV1DrawModel(m_var.handle);
	m_pIcon->Draw();
	SetUseLighting(true);
}

void PlayerCPU::SetAimTargetPtr(class Object* target)
{
	m_target.push_back(target);
}

// @detail �g�}�g�̏����֘A���܂Ƃ߂�����
void PlayerCPU::ProcessTomato()
{
	// �g�}�g�𓊂���
	m_shotTime++;
	// �G���߂Â��Ă�����A����Ă����瓊����̂��L�����Z������
	if (m_shotTime > m_shotPhaseTime && m_moveType == Type::AimTarget && m_bulletNum > 0 && !m_absolutelyMoveFlag)
	{
		//m_tomatos.push_back(new Tomato(m_pTransform->position, m_tomatoDir));
		m_animType = Anim::Throw;
		m_moveFlag = false;
		if (m_animTime == 0.0f)
		{
			/*m_pParent->GetComponent<Collider>()->Shot(m_pTransform->position, m_tomatoDir, m_pTag);*/
			m_bulletNum--;
			m_shotTime = 0.0f;
		}
	}
}

// @detail �W�I����������ɐ��ʂ�������
// @param aimTargetPos
void PlayerCPU::RotateTowardTarget(VECTOR& aimTargetPos)
{
	VECTOR subVector = VSub(aimTargetPos, m_pTransform->position);
	double angle = atan2(subVector.x, subVector.z);
	m_dir = VGet(0.0f, angle + DX_PI_F, 0.0f);
	// �g�}�g�������̌����ɍ��킹�Ĕ���
	m_tomatoDir = VAdd(VGet(0.0f, 0.0f, 0.0f), VGet(sin(angle), 0, cos(angle)));
}

void PlayerCPU::Animation()
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

	MV1SetAttachAnimTime(m_var.handle, m_animIndex, m_animTime);
}

// @detail �A�j���[�V������ύX����֐�
void PlayerCPU::ChangeAnimation()
{
	// �ړ��ł���A�j���[�V�����Ȃ�
	// �������Ă���̂��A�~�܂��Ă���̂��𔻒f
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

	// �A�j���[�V��������
	if (m_animType != m_beforeAnimType)
	{
		MV1DetachAnim(m_var.handle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_var.handle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_var.handle, m_animType);
		m_animTime = 0.0f;
		m_beforeAnimType = m_animType;
	}
}

// @detail �s���p�^�[�����`�F�b�N���Ď��s����
void PlayerCPU::CheckMovePattern()
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
void PlayerCPU::CheckTargetMovePattern()
{
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	int i = 0;
	for (auto target : m_target)
	{
		// �ǂ̃L�����N�^�[����ԋ߂����𒲂ׂ�
		VECTOR gPos = target->GetComponent<Transform>()->position;
		tmp = GetDistance(gPos, m_pTransform->position);

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
		Move1Target(m_target[objectNum]);
		if (m_moveType == Type::SearchTarget)
		{
			Move2Target(m_target[objectNum]);
		}
	}
	else  // �^�[�Q�b�g���瓦���鏈��
	{
		Move3Target(m_target[objectNum]);
	}
}

// @detail �^�[�Q�b�g�ɍ��킹�ē�������
// @param object �^�[�Q�b�g�̃Q�[���I�u�W�F�N�g
void PlayerCPU::Move1Target(class Object* player)
{
	VECTOR gPos = player->GetComponent<Transform>()->position;
	double distance = GetDistance(gPos, m_pTransform->position);

	if (distance >= m_targetRangeMin && distance < m_targetRangeMax)  // ���͈̔͂ɕW�I��������s��
	{
		if (distance > m_targetMoveRangeMax)  // �W�I������Ă�����߂Â�
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
		else if (distance < m_targetMoveRangeMin)  // �W�I���߂Â��Ă����痣���
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
void PlayerCPU::Move2Target(class Object* player)
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

		// �i��ł������������
		RotateTowardTarget(moveVector);
		m_pTransform->position = moveVector;

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
		VECTOR moveVector = VGet(m_pTransform->position.x + m_moveValue.x, m_pTransform->position.y, m_pTransform->position.z + m_moveValue.z);

		// �i��ł������������
		if (moveVector.x != 0.0f && moveVector.z != 0.0f)
		{
			RotateTowardTarget(moveVector);
		}

		m_pTransform->position = moveVector;

		// ���Ԍo�߂Ŏ��̍s���t�F�[�Y��
		m_moveTime++;
		if (m_moveTime > m_movePhaseTime)
		{
			m_moveTime = 0;
		}
	}
}

// @detail �^�[�Q�b�g���瓦���鏈��
void PlayerCPU::Move3Target(class Object* player)
{
	VECTOR gPos = player->GetComponent<Transform>()->position;

	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	// �g�}�g�̕ǂ��Ȃ��̂��T��
	for (int i = 0; i < m_pTomatoWall.size(); i++)
	{
		// ���̃g�}�g�̕ǂɃg�}�g�͂���̂�
		if (m_pTomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// �ǂ̃g�}�g�̕ǂ���ԋ߂����𒲂ׂ�
			VECTOR gPos = m_pTomatoWall[i]->GetPosition();
			tmp = GetDistance(gPos, m_pTransform->position);

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
		CollectTomato(m_pTomatoWall[objectNum]);
	}
	else  // �g�}�g�̕ǂ��Ȃ��Ԃ͓�����
	{
		VECTOR moveVector = VGet(m_pTransform->position.x, m_pTransform->position.y, m_pTransform->position.z);
		double distance = GetDistance(gPos, m_pTransform->position);

		// �w��͈̔͂܂œ����؂�
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

			// �i��ł������������
			RotateTowardTarget(moveVector);
			m_pTransform->position = moveVector;
		}
		else  // �^�[�Q�b�g���瓦����͈͂��o����^�[�Q�b�g�̂ق�������
		{
			RotateTowardTarget(gPos);
		}
	}
}

// @detail �g�}�g���������s���p�^�[�������s����
void PlayerCPU::CheckTomatoWall()
{
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	for (int i = 0; i < m_pTomatoWall.size(); i++)
	{
		// ���̃g�}�g�̕ǂɃg�}�g�͂���̂�
		if (m_pTomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// �ǂ̃g�}�g�̕ǂ���ԋ߂����𒲂ׂ�
			VECTOR gPos = m_pTomatoWall[i]->GetPosition();
			tmp = GetDistance(gPos, m_pTransform->position);

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

// @detail �g�}�g��������ɍs������
// @param object ��ԋ߂��g�}�g�̕ǃI�u�W�F�N�g
void PlayerCPU::CollectTomato(TomatoWallManager* object)
{
	VECTOR gPos = object->GetPosition();
	double distance = GetDistance(gPos, m_pTransform->position);

	if ((float)distance > object->GetWidthDistance() + 1)  // �W�I������Ă�����߂Â�
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

		// �W�I�̕����ɉ�]
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

// @detail �g�}�g�̕ǂ�����鏈��
void PlayerCPU::AvoidTomatoWall(TomatoWallManager* object)
{
	VECTOR mPos = m_pTransform->position;
	VECTOR gPos = object->GetPosition();

	double distance = GetDistance(gPos, m_pTransform->position);

	if ((float)distance < object->GetWidthDistance() && m_moveType == Type::TomatoCollect)  // �ǂɋ߂Â��������e�ɏ���
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
		m_moveType != Type::TomatoCollect && !m_avoidWallFlag)  // �ǂƂ̋������߂Â���������
	{
		m_avoidWallFlag = true;

		// �ǂ�����鋗�������������ɔ�����
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

	// ������t���O����������A������
	if (m_avoidWallFlag)
	{
		m_pTransform->position = VAdd(m_pTransform->position, m_avoidVelocity);
		distance = GetDistance(gPos, m_pTransform->position);

		// ���̋������󂢂��������̂���߂�
		if ((float)distance > object->GetWidthDistance() + 15)
		{
			m_avoidWallFlag = false;
			m_avoidVelocity = VGet(0.0f, 0.0f, 0.0f);
		}
	}
}
