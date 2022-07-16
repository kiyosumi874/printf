#include "pch.h"
#include "Tomato.h"

// @detail �R���X�g���N�^
// @param tag �I�u�W�F�N�g�̎��
// @param position �I�u�W�F�N�g�̈ʒu
Tomato::Tomato(ObjectTag tag, VECTOR position)
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);  // �����͂܂�0
	m_modelHandle = MV1LoadModel("data/Tomato/Tomato.mv1");

	m_time = 0.0f;
	m_gravity = 9.80665f;  // ���Ϗd�͒l�ŏ�����
}

// @detail �f�X�g���N�^
Tomato::~Tomato()
{
	MV1DeleteModel(m_modelHandle);
}

// @detail �X�V����
void Tomato::Update()
{
	Move();
	VAdd(m_position, m_velocity);
	MV1SetPosition(m_modelHandle, m_position);
}

// @detail �`�揈��
void Tomato::Draw()
{
	MV1DrawModel(m_modelHandle);
}

// @detail ������ꂽ��̏���
void Tomato::Move()
{
	// GameObject�}�[�W��ǉ�
}
