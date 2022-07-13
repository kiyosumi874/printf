#include "pch.h"
#include "Player.h"

Player::Player(ObjectTag tag, VECTOR position)
	: m_rotateNow(false)
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3D���f���̓ǂݍ���
	m_modelHandle = MV1LoadModel("data/Player/IronMan.mv1");

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
	VAdd(m_position, m_velocity);

	// 3D���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_position);
}

void Player::Draw()
{
	// 3D���f���̕`��
	MV1DrawModel(m_modelHandle);
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
	if (Input::IsPress(PAD_ID_UP))
	{
		L_inputVec = VAdd(L_front, L_inputVec);
		L_input = true;
	}

	// ���ɐi��
	if (Input::IsPress(PAD_ID_DOWN))
	{
		L_inputVec = VAdd(L_rear, L_inputVec);
		L_input = true;
	}

	// �E�ɐi��
	if (Input::IsPress(PAD_ID_RIGHT))
	{
		L_inputVec = VAdd(L_right, L_inputVec);
		L_input = true;
	}

	// ���ɐi��
	if (Input::IsPress(PAD_ID_LEFT))
	{
		L_inputVec = VAdd(L_left, L_inputVec);
		L_input = true;
	}

	// ���͗L�i�����j�E���͖��i�����j
	if (L_input)
	{

	}
}

void Player::Rotate()
{
}
