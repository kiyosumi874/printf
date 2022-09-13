#include "pch.h"
#include "Player.h"
#include "Tomato.h"
#include "TomatoWall.h"
#include "ModelManager.h"

Player::Player(ObjectTag tag, VECTOR position)
	: m_angle(0.0f)
	, m_rotateNow(false)
	, m_bulletNum(10)
	, m_bulletCapacity(10)
{
	m_position = position;
	m_tag = tag;

	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3D���f���̓ǂݍ���
	ModelManager* model = new ModelManager();
	srand(rand() % 100);
	int modelNum = rand() % MODEL_NUM;
	m_modelHandle = model->GetModelData(modelNum);
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;

	// �A�j���[�V��������
	m_animType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
	m_animTime = 0.0f;

	// ?G?t?F?N?g?????
	m_effect = new Effect("data/effect/hit/ToonHit.efkefc");
}

Player::~Player()
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

void Player::Update()
{
	Rotate();
	Input();

	// �ړ�����
	m_position = VAdd(m_position, m_velocity);

	// 3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_position);

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

void Player::Draw()
{
	// 3D���f���̕`��
	SetUseLighting(false);
	MV1DrawModel(m_modelHandle);
	// �g�}�g�`��
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Draw();
	}
	SetUseLighting(true);
	DrawFormatString(200, 0, GetColor(255, 255, 255), "PlayerBulletNum:%d", m_bulletNum);
#ifdef _DEBUG

#endif // _DEBUG

}

void Player::Input()
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
	if (m_tag == ObjectTag::Team1)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD2, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_angle += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_angle -= 0.01f;
		}

		// �O�ɐi��
		if (Input::IsPress2P(BUTTON_ID_UP))
		{
			front.x = sinf(m_angle);
			front.z = cosf(m_angle);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress2P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_angle) * -1.0f;
			rear.z = cosf(m_angle) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// �E�ɐi��
		if (Input::IsPress2P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_angle - addRad);
			right.z = cosf(m_angle - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress2P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_angle + addRad);
			left.z = cosf(m_angle + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}
	}

	// 2P�̑���
	if (m_tag == ObjectTag::Team2)
	{
		// ���͏�Ԃ��擾
		GetJoypadXInputState(DX_INPUT_PAD1, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_angle += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_angle -= 0.01f;
		}

		// �O�ɐi��
		if (Input::IsPress1P(BUTTON_ID_UP))
		{
			front.x = sinf(m_angle);
			front.z = cosf(m_angle);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress1P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_angle) * -1.0f;
			rear.z = cosf(m_angle) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// �E�ɐi��
		if (Input::IsPress1P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_angle - addRad);
			right.z = cosf(m_angle - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// ���ɐi��
		if (Input::IsPress1P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_angle + addRad);
			left.z = cosf(m_angle + addRad);
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
		m_moveFlag = true;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}

	// �g�}�g����(Player�̉�]�������I������㐶��(�ゾ�ƃv���C���[�̌����ɂȂ炸���������))
	if (Input::IsDown1P(BUTTON_ID_R) && m_bulletNum > 0)
	{
		m_bulletNum--;
		//m_tomatos.push_back(new Tomato(m_position, m_dir));
		
    
		m_effect->PlayEffect(m_position);
	}

	// �g�}�g�����E�܂Ŏ����Ă��Ȃ��Ƃ��A�g�}�g�̕ǂ���g�}�g�����
	if (Input::IsDown1P(BUTTON_ID_B) && m_bulletNum < m_bulletCapacity)
	{
		TomatoCollect();
	}
}

void Player::Rotate()
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

// @detail �g�}�g�������
void Player::TomatoCollect()
{
	int objectNum = 0;
	float distance = 0;
	for (int i = 0; i < m_tomatoWall.size(); i++)
	{
		// ���̃g�}�g�̕ǂɃg�}�g�͂���̂�
		if (m_tomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// �ǂ̃g�}�g�̕ǂ��𒲂ׂ�
			VECTOR gPos = m_tomatoWall[i]->GetPosition();
			distance = GetDistance(gPos, m_position);

			// ���������̒l�Ȃ琳�̒l�ɕς���
			if (distance < 0.0f)
			{
				distance = distance * -1.0f;
			}

			// �͈͂ɓ����Ă���g�}�g�̕ǂ���g�}�g�����
			if (distance < m_tomatoWall[i]->GetWidthDistance())
			{
				m_bulletNum++;
				m_tomatoWall[i]->DecreaseAllTomatoNum();
				break;
			}
		}
	}
}

void Player::ChangeAnimation()
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

// @detail ���g�Ƒ��̃I�u�W�F�N�g�̋������o��
double Player::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}