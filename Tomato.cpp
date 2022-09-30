#include "pch.h"
#include "Tomato.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"

// @detail �R���X�g���N�^
// @param position �g�}�g�𓊂���l�̈ʒu
// @param dir ������l�̌���
Tomato::Tomato()
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);  // �����͂܂�0
	m_startVelocity = VGet(20.0f, 1.0f, 20.0f);
	// AssetManager���烂�f���f�[�^��������Ă���
	m_modelHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Tomato));
	m_position = VGet(0.0f,0.0f,0.0f);

	m_time = 0.0f;
	m_gravity = 9.80665f;  // ���Ϗd��
	m_deg = 30.0f;
	m_rad = m_deg * (DX_PI_F / 180.0f);

	m_dir = VGet(0.0f, 0.0f, 0.0f);

	// �T�C�Y����
	MV1SetScale(m_modelHandle, VGet(0.02f,0.02f,0.02f));
}

// @detail �f�X�g���N�^
Tomato::~Tomato()
{
	MV1DeleteModel(m_modelHandle);
}

//void Tomato::Init(VECTOR position, VECTOR dir)
//{
//}

void Tomato::Init(VECTOR position, VECTOR dir, Tag* tag)
{
	m_position = position;
	m_position = VAdd(m_position, VGet(0.0f, 15.0f, 0.0f));
	m_dir = dir;
	m_tag = tag;
}

// @detail �X�V����
void Tomato::Update()
{
	Move();
	m_position = VAdd(m_position, m_velocity);
	MV1SetPosition(m_modelHandle, m_position);
	auto pos = m_pParent->GetComponent<Transform>();
	pos->position = m_position;
}

// @detail �`�揈��
void Tomato::Draw()
{
	MV1DrawModel(m_modelHandle);
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

	// �Ε����ˌ����ɂ��ړ��v�Z
	m_velocity.x = m_dir.x * (m_startVelocity.x * cos(m_rad) * m_time);
	m_velocity.y = m_startVelocity.y * sin(m_rad) * m_time - (0.5f * m_gravity * m_time * m_time);
	m_velocity.z = m_dir.z * (m_startVelocity.z * cos(m_rad) * m_time);
}
