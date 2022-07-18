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
}

void Player::Update()
{
	Rotate();
	Input();

	// �ړ�����
	m_position = VAdd(m_position, m_velocity);

	// 3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_position);

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
	for(int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Draw();
	}
}

void Player::Input()
{
	// �g�}�g����
	if (Input::IsDown1P(BUTTON_ID_B))
	{
		m_tomatos.push_back(new Tomato(m_position, m_dir));
	}

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

		m_velocity = VAdd(m_velocity, L_inputVec);
		if (m_velocity.x > 2.0f) { m_velocity.x = 2.0f; }
		if (m_velocity.x < -2.0f) { m_velocity.x = -2.0f; }
		if (m_velocity.z > 2.0f) { m_velocity.z = 2.0f; }
		if (m_velocity.z < -2.0f) { m_velocity.z = -2.0f; }
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}
}

void Player::Rotate()
{
}
