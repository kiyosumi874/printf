#include "pch.h"
#include "Human.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"
#include "Collider.h"
#include "ModelManager.h"
#include "Tomato.h"
#include "TomatoWall.h"
#include "Score.h"
#include "Icon.h"

Human::Human()
	: m_rotateNow(false)
	, m_moveFlag(false)
	, m_bulletNum(10)
	, m_bulletCapacity(10)
{
	m_pTransform = nullptr;
	m_pTag = nullptr;

	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;

	// �A�j���[�V��������
	m_animType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
	m_animTime = 0.0f;
	m_animSpeed = 0.3f;
	m_throwSpeed = 1.2f;
	m_pickSpeed = 1.2f;
	m_moveFlag = true;
	m_throwFlag = false;
	m_pickFlag = false;
}

Human::~Human()
{
	MV1DeleteModel(m_modelHandle);
}

void Human::Start()
{
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if (m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	// 3D���f���̓ǂݍ���
	if (m_pTag->tag == ObjectTag::Team1) { m_modelHandle = MV1LoadModel("data/character/man1.mv1"); }
	if (m_pTag->tag == ObjectTag::Team2) { m_modelHandle = MV1LoadModel("data/character/man3.mv1"); }
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));
	// 3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_pTransform->position);

	// �A�C�R�����Z�b�g
	m_icon = new Icon(m_pTag);
	m_icon->Init(m_pTransform->position);
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
	// �A�j���[�V��������
	Animation();

	// �ړ�����
	if (m_moveFlag)
	{
		m_pTransform->position;
		m_pTransform->position = VAdd(m_pTransform->position, m_velocity);

		// 3D���f���̃|�W�V�����ݒ�
		MV1SetPosition(m_modelHandle, m_pTransform->position);
	}
	
	// �����ɍ��킹�ă��f������]
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_dir, rotYMat);

	// ���f���ɉ�]���Z�b�g����
	MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	m_icon->Update(m_pTransform->position);
}

void Human::Draw()
{
	// 3D���f���̕`��
	SetUseLighting(false);
	MV1DrawModel(m_modelHandle);
	m_icon->Draw();
	SetUseLighting(true);
}

void Human::SetTomatoWallPtr(std::vector<TomatoWall*>* tomatoWall)
{
	m_tomatoWall = tomatoWall;
}

void Human::Input()
{
	m_inputVector = VGet(0.0f, 0.0f, 0.0f); // ���������v���W�擾�p�ϐ�
	// �O�㍶�E
	VECTOR front = { 0.0f,0.0f,1.0f };
	VECTOR rear = { 0.0f,0.0f,-1.0f };
	VECTOR left = { 1.0f,0.0f,0.0f };
	VECTOR right = { -1.0f,0.0f,0.0f };

	float addRad = 1.58f;	// ���Z����p�x
	bool input = false;		// ���͂���������p

	XINPUT_STATE inputState;

	// 1P�̑���
	if (m_pTag->tag == ObjectTag::Team1)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD2, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_pTransform->rotate.y += 0.02f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_pTransform->rotate.y -= 0.02f;
		}

		// �O�ɐi��
		if (Input::IsPress2P(BUTTON_ID_UP))
		{
			front.x = sinf(m_pTransform->rotate.y);
			front.z = cosf(m_pTransform->rotate.y);
			m_inputVector = VAdd(front, m_inputVector);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress2P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_pTransform->rotate.y) * -1.0f;
			rear.z = cosf(m_pTransform->rotate.y) * -1.0f;
			m_inputVector = VAdd(rear, m_inputVector);
			input = true;
		}

		// �E�ɐi��
		if (Input::IsPress2P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_pTransform->rotate.y - addRad);
			right.z = cosf(m_pTransform->rotate.y - addRad);
			m_inputVector = VAdd(right, m_inputVector);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress2P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_pTransform->rotate.y + addRad);
			left.z = cosf(m_pTransform->rotate.y + addRad);
			m_inputVector = VAdd(left, m_inputVector);
			input = true;
		}

		// �g�}�g����(Player�̉�]�������I������㐶��(�ゾ�ƃv���C���[�̌����ɂȂ炸���������))
		if (Input::IsDown2P(BUTTON_ID_R) && m_bulletNum > 0 && !m_throwFlag)
		{
			m_throwFlag = true;
			m_animType = Anim::Throw;
			m_bulletNum--;
			auto pos = m_pParent->GetComponent<Transform>();
			VECTOR position = VGet(0.0f, 0.0f, 0.0f);
			position.x = pos->position.x + sinf(pos->rotate.y) * -30.0f;
			position.z = pos->position.z + cosf(pos->rotate.y) * -30.0f;
			position = VSub(pos->position, position);
			// �����𐳋K��
			position = VNorm(position);
			m_pParent->GetComponent<Collider>()->Shot(pos->position, position, m_pParent->GetComponent<Tag>());
			//m_effect->PlayEffect(m_position);
		}

		// �g�}�g�����E�܂Ŏ����Ă��Ȃ��Ƃ��A�g�}�g�̕ǂ���g�}�g�����
		if (Input::IsDown2P(BUTTON_ID_B) && m_bulletNum < m_bulletCapacity)
		{
			TomatoCollect();
		}

		Score::Set1PBulletNum(m_bulletNum);
	}

	// 2P�̑���
	if (m_pTag->tag == ObjectTag::Team2)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD1, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_pTransform->rotate.y += 0.02f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_pTransform->rotate.y -= 0.02f;
		}

		// �O�ɐi��
		if (Input::IsPress1P(BUTTON_ID_UP))
		{
			front.x = sinf(m_pTransform->rotate.y);
			front.z = cosf(m_pTransform->rotate.y);
			m_inputVector = VAdd(front, m_inputVector);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress1P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_pTransform->rotate.y) * -1.0f;
			rear.z = cosf(m_pTransform->rotate.y) * -1.0f;
			m_inputVector = VAdd(rear, m_inputVector);
			input = true;
		}

		// �E�ɐi��
		if (Input::IsPress1P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_pTransform->rotate.y - addRad);
			right.z = cosf(m_pTransform->rotate.y - addRad);
			m_inputVector = VAdd(right, m_inputVector);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress1P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_pTransform->rotate.y + addRad);
			left.z = cosf(m_pTransform->rotate.y + addRad);
			m_inputVector = VAdd(left, m_inputVector);
			input = true;
		}

		// �g�}�g����(Player�̉�]�������I������㐶��(�ゾ�ƃv���C���[�̌����ɂȂ炸���������))
		if (Input::IsDown1P(BUTTON_ID_R) && m_bulletNum > 0 && !m_throwFlag)
		{
			m_throwFlag = true;
			m_animType = Anim::Throw;
			m_moveFlag = false;
			m_bulletNum--;
			auto pos = m_pParent->GetComponent<Transform>();
			VECTOR position = VGet(0.0f, 0.0f, 0.0f);
			position.x = pos->position.x + sinf(pos->rotate.y) * -30.0f;
			position.z = pos->position.z + cosf(pos->rotate.y) * -30.0f;
			position = VSub(pos->position, position);
			// �����𐳋K��
			position = VNorm(position);
			m_pParent->GetComponent<Collider>()->Shot(pos->position, position, m_pParent->GetComponent<Tag>());
			//m_effect->PlayEffect(m_position);
		}

		// �g�}�g�����E�܂Ŏ����Ă��Ȃ��Ƃ��A�g�}�g�̕ǂ���g�}�g�����
		if (Input::IsDown1P(BUTTON_ID_B) && m_bulletNum < m_bulletCapacity)
		{
			TomatoCollect();
		}

		Score::Set2PBulletNum(m_bulletNum);
	}

	// ���͗L�i�����j�E���͖��i�����j
	if (input)
	{
		// ���E�E�O�㓯�������Ȃǂœ��̓x�N�g����0�̎��͖���
		if (VSquareSize(m_inputVector) < 0.5f)
		{
			return;
		}

		// �����𐳋K��
		m_inputVector = VNorm(m_inputVector);

		// ���͕����͌��݌����Ă�������ƈقȂ邩
		if (IsNearAngle(m_inputVector, m_dir))
		{
			m_dir = m_inputVector;
		}
		else
		{
			m_rotateNow = true;
			m_aimDir = m_inputVector;
		}

		m_velocity = m_inputVector;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}

	if (m_pParent->GetComponent<Collider>()->flag)
	{
		//m_pTransform->position = VSub(m_pTransform->position, VScale(inputVec, 2.5f));
		//m_velocity = VGet(0.0f, 0.0f, 0.0f);
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

void Human::Animation()
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
		if (m_pickFlag)
		{
			m_pickFlag = false;
			m_animType = Anim::None;
			m_moveFlag = true;
		}
		if (m_throwFlag)
		{
			m_throwFlag = false;
			m_animType = Anim::None;
			m_moveFlag = true;
		}
	}
	ChangeAnimation();

	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);
}

void Human::ChangeAnimation()
{
	// �ړ��ł���A�j���[�V�����Ȃ�
	// �������Ă���̂��A�~�܂��Ă���̂��𔻒f
	if (m_moveFlag)
	{
		VECTOR nowPosition = MV1GetPosition(m_modelHandle);
		if (m_inputVector.x == 0.0f &&
			m_inputVector.y == 0.0f &&
			m_inputVector.z == 0.0f)
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

void Human::TomatoCollect()
{
	int objectNum = 0;
	float distance = 0;
	int i = 0;
	auto pos = m_pParent->GetComponent<Transform>()->position;
	for (auto tomatowall : *m_tomatoWall)
	{
		// ���̕ǂɃg�}�g�͂���̂�
		if (tomatowall[i].GetAllTomatoNum() != 0)
		{
			// �ǂ̃g�}�g�̕ǂ��𒲂ׂ�
			VECTOR gPos = tomatowall[i].GetPosition();
			distance = GetDistance(gPos, pos);

			// ���������̒l�Ȃ琳�̒l�ɕς���
			if (distance < 0.0f)
			{
				distance = distance * -1.0f;
			}
		}

		// �͈͂ɓ����Ă���g�}�g�̕ǂ���g�}�g�����
		if (distance < tomatowall[i].GetWidthDistance() && !m_pickFlag)
		{
			m_pickFlag = true;
			m_moveFlag = false;
			m_animType = Anim::Pick;
			m_bulletNum++;
			tomatowall[i].DecreaseAllTomatoNum();
			break;
		}
	}
}

double Human::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
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
