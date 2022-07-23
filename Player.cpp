#include "pch.h"
#include "Player.h"
#include "Tomato.h"

Player::Player(ObjectTag tag, VECTOR position)
	: m_rotateNow(false)
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3D���f���̓ǂݍ���
	m_modelHandle = MV1LoadModel("data/player/hackadoll.pmx");

	m_dir = VGet(1.0f, 0.0f, 0.0f);
	m_aimDir = m_dir;
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
	MV1DrawModel(m_modelHandle);

	// �g�}�g�`��
	for(int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Draw();
	}
}

void Player::Input()
{
	// �O�㍶�E
	VECTOR L_front = { 0.0f,0.0f,1.0f };
	VECTOR L_rear = { 0.0f,0.0f,-1.0f };
	VECTOR L_left = { -1.0f,0.0f,0.0f };
	VECTOR L_right = { 1.0f,0.0f,0.0f };

	VECTOR L_inputVec = VGet(0.0f, 0.0f, 0.0f);	// ���������v���W�擾�p�ϐ�

	bool L_input = false;	// ���͂���������p

	// �O�ɐi��
	if (CheckHitKey(KEY_INPUT_UP))
	{
		L_inputVec = VAdd(L_front, L_inputVec);
		L_input = true;
	}

	// ���ɐi��
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		L_inputVec = VAdd(L_rear, L_inputVec);
		L_input = true;
	}

	// �E�ɐi��
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		L_inputVec = VAdd(L_right, L_inputVec);
		L_input = true;
	}

	// ���ɐi��
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		L_inputVec = VAdd(L_left, L_inputVec);
		L_input = true;
	}

	// ���͗L�i�����j�E���͖��i�����j
	if (L_input)
	{
		// ���E�E�O�㓯�������Ȃǂœ��̓x�N�g����0�̎��͖���
		if (VSquareSize(L_inputVec) < 0.5f)
		{
			return;
		}

		// �����𐳋K��
		L_inputVec = VNorm(L_inputVec);

		// ���͕����͌��݌����Ă�������ƈقȂ邩
		if (IsNearAngle(L_inputVec, m_dir))
		{
			m_dir = L_inputVec;
		}
		else
		{
			m_rotateNow = true;
			m_aimDir = L_inputVec;
		}

		m_velocity = L_inputVec;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}

	// �g�}�g����
	if (Input::IsDown1P(BUTTON_ID_B))
	{
		m_tomatos.push_back(new Tomato(m_position, m_dir));
	}
}

void Player::Rotate()
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
