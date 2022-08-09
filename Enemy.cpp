#include "pch.h"
#include "Enemy.h"
#include "Tomato.h"
#include "ModelManager.h"

Enemy::Enemy(ObjectTag tag, VECTOR position)
	: m_movePhaseTime(50)
{
	// 3D���f���̓ǂݍ���
	ModelManager* model = new ModelManager();
	srand(rand() % 100);
	int modelNum = rand() % MODEL_NUM;
	m_modelHandle = model->GetModelData(modelNum);
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));

	m_velocity = VGet(1.0f, 1.0f, 1.0f);
	m_dir = VGet(0.0f, 0.0f, 0.0f);
	m_tomatoDir = VGet(0.0f, 0.0f, 0.0f);
	m_moveValue = VGet(0.0f, 0.0f, 0.0f);

	m_moveType = Type::Target;
	m_targetFoundFlag = false;
	m_aimTargetFlag = false;
	m_moveTime = 0;

	// �A�j���[�V��������
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

	// �A�j���[�V��������
	ChangeAnimation();
	m_animTime += 0.3f;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}
	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);

	// �g�}�g�̏���
	ProcessTomato();

	// 3D���f���̉�]�ݒ�
	MV1SetRotationXYZ(m_modelHandle, m_dir);

	// 3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_position);
}

void Enemy::Draw()
{
	SetUseLighting(false);
	// 3D���f���̕`��
	MV1DrawModel(m_modelHandle);

	// �g�}�g�`��
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

// @detail �g�}�g�̏����֘A���܂Ƃ߂�����
void Enemy::ProcessTomato()
{
	// �g�}�g�𓊂���
	m_shotTime++;
	if (m_shotTime > 100.0f && m_targetFoundFlag)
	{
		m_tomatos.push_back(new Tomato(m_position, m_tomatoDir));
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

void Enemy::ChangeAnimation()
{
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

	// �A�j���[�V��������
	if (!m_moveFlag && m_animType != Anim::Idle)  // �~�܂�A�j���[�V����
	{
		m_animTime = 0.0f;
		m_animType = Anim::Idle;
		MV1DetachAnim(m_modelHandle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
		m_animTime = 0.0f;
	}
	else if (m_moveFlag && m_animType != Anim::Run)  // ����A�j���[�V����
	{
		m_animTime = 0.0f;
		m_animType = Anim::Run;
		MV1DetachAnim(m_modelHandle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
		m_animTime = 0.0f;
	}
}


void Enemy::CheckMovePattern()
{
	if (m_moveType == Type::Target)
	{
		CheckTargetMovePattern();
	}
}

void Enemy::CheckTargetMovePattern()
{
	int objectNum = 0;
	float distance = 0;
	float tmp = 0;
	for (int i = 0; i < m_objects.size(); i++)
	{
		// �^�[�Q�b�g����I�u�W�F�N�g��������
		if (m_objects[i]->GetTag() == ObjectTag::Player1 ||
			m_objects[i]->GetTag() == ObjectTag::Player2)
		{
			// �ǂ̃L�����N�^�[����ԋ߂����𒲂ׂ�
			VECTOR gPos = m_objects[i]->GetPosition();
			tmp = GetDistance(gPos, m_position);

			// tmp�����̒l�Ȃ琳�̒l�ɕς���
			if (tmp < 0.0f)
			{
				tmp = tmp * -1.0f;
			}

			// tmp��0���������ԋ߂��̂�for���𔲂���
			if (tmp == 0.0f)
			{
				objectNum = i;
				break;
			}

			// ��������ԋ߂��I�u�W�F�N�g�ԍ���ۑ�����
			if (distance > tmp || distance == 0.0f)
			{
				distance = tmp;
				objectNum = i;

				if (distance < m_targetRangeMax)
				{
					m_targetFoundFlag = true;
				}
			}
		}
	}
	// �I�u�W�F�N�g�ɍ��킹�čs������
	if (m_targetFoundFlag)
	{
		TargetMove1(m_objects[objectNum]);
	}
	else
	{
		TargetMove2(m_objects[objectNum]);
	}
}

// @detail �^�[�Q�b�g�ɍ��킹�ē�������
// @param object �^�[�Q�b�g�̃Q�[���I�u�W�F�N�g
void Enemy::TargetMove1(GameObject* object)
{
	VECTOR gPos = object->GetPosition();
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
		}

		// �W�I�̕����ɉ�]
		RotateTowardTarget(gPos);
		// �W�I�𔭌�
		m_targetFoundFlag = true;
		m_aimTargetFlag = false;
		m_moveTime = 0;
	}
	else
	{
		m_targetFoundFlag = false;
	}
}

// @detail �^�[�Q�b�g��������Ȃ��Ƃ��̏���
// @param object �^�[�Q�b�g�̃Q�[���I�u�W�F�N�g
void Enemy::TargetMove2(GameObject* object)
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