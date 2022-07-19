#include "pch.h"
#include <math.h>
#include "Tomato.h"

// @detail �R���X�g���N�^
// @param position �g�}�g�𓊂���l�̈ʒu
// @param dir ������l�̌���
Tomato::Tomato(VECTOR& position, VECTOR& dir)
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);  // �����͂܂�0
	m_startVelocity = VGet(1.0f, 1.0f, 1.0f);
	m_modelHandle = MV1LoadModel("data/Tomato/Tomato.mv1");
	m_position = position;
	m_position = VAdd(m_position, VGet(0.0f, 10.0f, 0.0f));

	m_time = 0.0f;
	m_gravity = 9.80665f;  // ���Ϗd�͒l�ŏ�����
	m_deg = 20.0f;
	m_rad = m_deg * (DX_PI_F / 180.0f);
	m_dir = dir;

	// �T�C�Y����
	MV1SetScale(m_modelHandle, VGet(0.02f,0.02f,0.02f));
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
	m_position = VAdd(m_position, m_velocity);
	MV1SetPosition(m_modelHandle, m_position);
}

// @detail �`�揈��
void Tomato::Draw()
{
	int result = MV1DrawModel(m_modelHandle);
}

// @detail�g�}�g�𓊂��Ă���̎��Ԃ�Ԃ�
// @return m_time �g�}�g�𓊂��Ă���̎���
float Tomato::GetTime()
{
	return m_time;
}

// @detail ������ꂽ��̏���
void Tomato::Move()
{
	m_time += 0.01f;

	m_velocity.y = m_startVelocity.y * cos(m_rad) * m_time;
	m_velocity.z = m_startVelocity.z * sin(m_rad) * m_time - (0.5f * m_gravity * m_time * m_time);
}
