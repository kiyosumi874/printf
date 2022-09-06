#include "pch.h"
#include "Human.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"
#include "Collider.h"
#include "ModelManager.h"
#include "Tomato.h"

Human::Human()
	: m_rotateNow(false)
	, m_moveFlag(false)
{
	m_pTransform = nullptr;
	m_pTag = nullptr;

	m_modelHandle = MV1LoadModel("data/character/man1.mv1");
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3D���f���̓ǂݍ���
	//ModelManager* model = new ModelManager();
	//srand(rand() % 100);
	//int modelNum = rand() % MODEL_NUM;
	//m_modelHandle = model->GetModelData(modelNum);
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;

	// �A�j���[�V��������
	m_animType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
	m_animTime = 0.0f;
}

Human::~Human()
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

void Human::Start()
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
	m_pTransform->position;
	m_pTransform->position = VAdd(m_pTransform->position, m_velocity);

	// 3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_pTransform->position);

	// �����ɍ��킹�ă��f������]
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_dir, rotYMat);

	// ���f���ɉ�]���Z�b�g����
	MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// �A�j���[�V��������
	ChangeAnimation();
	m_animTime += 0.3f;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}
	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);

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

void Human::Draw()
{
	// 3D���f���̕`��
	SetUseLighting(false);
	MV1DrawModel(m_modelHandle);
	// �g�}�g�`��
	//for (int i = 0; i < m_tomatos.size(); i++)
	//{
	//	m_tomatos[i]->Draw();
	//}
	SetUseLighting(true);
	auto pos = m_pTransform->position;
	int t = 0;
	auto collider = m_pParent->GetComponent<Collider>();
	if (collider->Getflag()) 
	{ 
		if (collider->tag == ObjectTag::Enemy) { t = 1; }
		if (collider->tag == ObjectTag::tomato) { t = 2; }
		if (collider->tag == ObjectTag::Player2) { t = 3; }
	}
	printfDx("x:%f y:%f z:%f flag:%d\n", pos.x, pos.y, pos.z, t);
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

	m_moveFlag = false;

	// 1P�̑���
	if (m_pTag->tag == ObjectTag::Player1)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD2, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_pTransform->rotate.y += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_pTransform->rotate.y -= 0.01f;
		}

		// �O�ɐi��
		if (Input::IsPress2P(BUTTON_ID_UP))
		{
			front.x = sinf(m_pTransform->rotate.y);
			front.z = cosf(m_pTransform->rotate.y);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress2P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_pTransform->rotate.y) * -1.0f;
			rear.z = cosf(m_pTransform->rotate.y) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// �E�ɐi��
		if (Input::IsPress2P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_pTransform->rotate.y - addRad);
			right.z = cosf(m_pTransform->rotate.y - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress2P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_pTransform->rotate.y + addRad);
			left.z = cosf(m_pTransform->rotate.y + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}

		// �g�}�g����(Player�̉�]�������I������㐶��(�ゾ�ƃv���C���[�̌����ɂȂ炸���������))
		if (Input::IsDown2P(BUTTON_ID_R)/* && m_bulletNum > 0*/)
		{
			//m_bulletNum--;
			auto pos = m_pParent->GetComponent<Transform>()->position;
			m_pParent->GetComponent<Collider>()->Shot(pos, m_dir, m_pParent->GetComponent<Tag>());
			//m_effect->PlayEffect(m_position);
		}
	}

	// 2P�̑���
	if (m_pTag->tag == ObjectTag::Player2)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD1, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_pTransform->rotate.y += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_pTransform->rotate.y -= 0.01f;
		}

		// �O�ɐi��
		if (Input::IsPress1P(BUTTON_ID_UP))
		{
			front.x = sinf(m_pTransform->rotate.y);
			front.z = cosf(m_pTransform->rotate.y);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress1P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_pTransform->rotate.y) * -1.0f;
			rear.z = cosf(m_pTransform->rotate.y) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// �E�ɐi��
		if (Input::IsPress1P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_pTransform->rotate.y - addRad);
			right.z = cosf(m_pTransform->rotate.y - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress1P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_pTransform->rotate.y + addRad);
			left.z = cosf(m_pTransform->rotate.y + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}

		// �g�}�g����(Player�̉�]�������I������㐶��(�ゾ�ƃv���C���[�̌����ɂȂ炸���������))
		if (Input::IsDown1P(BUTTON_ID_R)/* && m_bulletNum > 0*/)
		{
			//m_bulletNum--;
			auto pos = m_pParent->GetComponent<Transform>()->position;
			m_pParent->GetComponent<Collider>()->Shot(pos, m_dir, m_pParent->GetComponent<Tag>());
			//m_effect->PlayEffect(m_position);
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
		m_moveFlag = true;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}

	if (m_pParent->GetComponent<Collider>()->flag)
	{
		m_pTransform->position = VSub(m_pTransform->position, VScale(inputVec, 2.5f));
		m_velocity = VGet(0.0f, 0.0f, 0.0f);
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

void Human::ChangeAnimation()
{
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
