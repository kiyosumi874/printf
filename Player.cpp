#include "pch.h"
#include "Player.h"
#include "Tomato.h"

Player::Player(ObjectTag tag, VECTOR position)
	: m_angle(0.0f)
	, m_rotateNow(false)
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3D���f���̓ǂݍ���
	m_modelHandle = MV1LoadModel("data/player/hackadoll.pmx");

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;
}

Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
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

	// �g�}�g����
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Update();
	}
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		// �g�}�g�̐������Ԃ�5.0f�𒴂���ƍ폜
		if (m_tomatos[i]->GetTime() > 5.0f)
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
	MV1DrawModel(m_modelHandle);
	// �g�}�g�`��
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Draw();
	}
#ifdef _DEBUG
	printfDx("angle:%f\n", m_angle);
	XINPUT_STATE input;
	// ���͏�Ԃ��擾
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	printfDx("X = %d\n", input.ThumbRX);
	printfDx("Y = %d\n", input.ThumbRY);
#endif // _DEBUG

}

void Player::Input()
{
	// �g�}�g����
	if (Input::IsDown1P(BUTTON_ID_R))
	{
		m_tomatos.push_back(new Tomato(m_position, m_dir));
	}

	// �O�㍶�E
	VECTOR front = { 0.0f,0.0f,1.0f };
	VECTOR rear = { 0.0f,0.0f,-1.0f };
	VECTOR left = { 1.0f,0.0f,0.0f };
	VECTOR right = { -1.0f,0.0f,0.0f };

	VECTOR inputVec = VGet(0.0f, 0.0f, 0.0f);	// ���������v���W�擾�p�ϐ�

	float addRad = 1.58f;	// ���Z����p�x
	bool input = false;		// ���͂���������p

	XINPUT_STATE inputState;
	// ���͏�Ԃ��擾
	GetJoypadXInputState(DX_INPUT_PAD1, &inputState);
	if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
	{
		m_angle += 0.02f;
	}
	if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
	{
		m_angle -= 0.02f;
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
