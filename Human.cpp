#include "pch.h"
#include "Human.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"

Human::Human()
	: m_rotateNow(false)
{
	m_pTransform = nullptr;
	m_pTag = nullptr;

	m_modelHandle = MV1LoadModel("data/character/man1.mv1");
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;
}

Human::~Human()
{
}

void Human::Update()
{
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if(m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	Rotate();	// ��]
	Input();	// ����

	// �ړ�����
	auto pos = m_pTransform->position;
	pos = VAdd(pos, m_velocity);

	// 3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, pos);
	
	// 3D���f���̑傫����ݒ�
	MV1SetScale(m_modelHandle, m_pTransform->scale);

	// �����ɍ��킹�ă��f������]
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_dir, rotYMat);

	// ���f���ɉ�]���Z�b�g����
	MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Human::Draw()
{
	MV1DrawModel(m_modelHandle);
	auto pos = m_pTransform->position;
	DrawSphere3D(pos, 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

void Human::Input()
{
	// �O�㍶�E
	VECTOR front = { 0.0f,0.0f,1.0f };
	VECTOR rear = { 0.0f,0.0f,-1.0f };
	VECTOR left = { 1.0f,0.0f,0.0f };
	VECTOR right = { -1.0f,0.0f,0.0f };

	VECTOR inputVec = VGet(0.0f, 0.0f, 0.0f);	// ���������v���W�擾�p�ϐ�

	float addRad = 1.58f;	// ���Z����p�x
	bool input = false;		// ���͂���������p

	XINPUT_STATE inputState;
	auto angle = m_pTransform->rotate.y;

	// 1P�̑���
	if (m_pTag->tag == ObjectTag::Player1)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD2, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			angle += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			angle -= 0.01f;
		}

		// �O�ɐi��
		if (Input::IsPress2P(BUTTON_ID_UP))
		{
			front.x = sinf(angle);
			front.z = cosf(angle);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress2P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(angle) * -1.0f;
			rear.z = cosf(angle) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// �E�ɐi��
		if (Input::IsPress2P(BUTTON_ID_LEFT))
		{
			right.x = sinf(angle - addRad);
			right.z = cosf(angle - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress2P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(angle + addRad);
			left.z = cosf(angle + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}
	}

	// 2P�̑���
	if (m_pTag->tag == ObjectTag::Player2)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD1, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			angle += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			angle -= 0.01f;
		}

		// �O�ɐi��
		if (Input::IsPress1P(BUTTON_ID_UP))
		{
			front.x = sinf(angle);
			front.z = cosf(angle);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress1P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(angle) * -1.0f;
			rear.z = cosf(angle) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// �E�ɐi��
		if (Input::IsPress1P(BUTTON_ID_LEFT))
		{
			right.x = sinf(angle - addRad);
			right.z = cosf(angle - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress1P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(angle + addRad);
			left.z = cosf(angle + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}
	}

	// ���͗L�i�����j�E���͖��i�����j
	if (input)
	{
		// ���E�E�O�㓯�������Ȃǂœ��̓x�N�g����0�̎��͖���
		if (VSquareSize(inputVec) < 0.5f)
		{
			return;
		}

		// �����𐳋K��
		inputVec = VNorm(inputVec);

		// ���͕����͌��݌����Ă�������ƈقȂ邩
		if (IsNearAngle(inputVec, m_dir))
		{
			m_dir = inputVec;
		}
		else
		{
			m_rotateNow = true;
			m_aimDir = inputVec;
		}

		m_velocity = inputVec;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}
}

void Human::Rotate()
{
	if (m_rotateNow)
	{
		// ��]���ڕW�p�x�ɓ��B����Ή�]���[�h�I��
		if (IsNearAngle(m_aimDir, m_dir))
		{
			m_dir = m_aimDir;
			m_rotateNow = false;
		}
		else
		{
			// ��]
			VECTOR interPolateDir;
			interPolateDir = RotateForAimVecYAxis(m_dir, m_aimDir, 10.0f);

			// ��]���ڕW�p�x�𒴂��Ă��Ȃ���
			VECTOR cross1, cross2;
			cross1 = VCross(m_dir, m_aimDir);
			cross2 = VCross(interPolateDir, m_aimDir);

			// �ڕW�p�x�𒴂�����I��
			if (cross1.y * cross2.y < 0.0f)
			{
				interPolateDir = m_aimDir;
				m_rotateNow = false;
			}
			// �ڕW�x�N�g����10�x�����߂Â����p�x
			m_dir = interPolateDir;
		}
	}
}

bool Human::IsNearAngle(const VECTOR& v1, const VECTOR& v2)
{
	float dot = VDot(v1, v2);
	if (dot < 0.99f)
	{
		return true;
	}
	return false;
}

float Human::CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
{
	VECTOR axis;
	axis = VCross(nowVec, dirVec);
	if (axis.y < 0.0f)
	{
		return -1.0f;
	}
	return 1.0f;
}

VECTOR Human::RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity)
{
	// �p���x�i�x���j�����W�A���p�ɕϊ��A�E��肩����肩�𒲂ׂ�
	float rotRadian = (DX_PI_F * degreeVelocity / 180.0f);
	rotRadian *= CalcRotationDirectionYAxis(nowVec, aimVec);

	// Y����]�s����쐬����
	MATRIX yRotMat = MGetRotY(rotRadian);

	// Y����]����
	VECTOR rotVec;
	rotVec = VTransform(nowVec, yRotMat);
	return rotVec;
}
