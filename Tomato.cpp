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

	m_time = 0.0f;
	m_gravity = 9.80665f;  // ���Ϗd��
	m_deg = 30.0f;
	m_rad = m_deg * (DX_PI_F / 180.0f);

	m_dir = VGet(0.0f, 0.0f, 0.0f);
}

// @detail �f�X�g���N�^
Tomato::~Tomato()
{
}

void Tomato::Start()
{
	if (m_tag == nullptr)
	{
		m_tag = m_pParent->GetComponent<Tag>();
	}
	if (m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
}

// @detail �X�V����
void Tomato::Update()
{
	Move();
	m_pTransform->position = VAdd(m_pTransform->position, m_velocity);
	m_var.pos = m_pTransform->position;
	MV1SetPosition(m_var.handle, m_var.pos);
}

// @detail �`�揈��
void Tomato::Draw()
{
	MV1DrawModel(m_var.handle);
}

void Tomato::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
	VECTOR tmp = VAdd(pos, VGet(0.0f, 15.0f, 0.0f));
	m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Tomato)), tmp, rotate, scale);

	// 3D���f���ݒ�
	MV1SetScale(m_var.handle, m_var.scale);
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);

	m_pTransform->position = m_var.pos;
	m_pTransform->rotate = m_var.rotate;
	m_pTransform->scale = m_var.scale;
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

	m_velocity.x = m_dir.x * (m_startVelocity.x * cos(m_rad) * m_time);
	m_velocity.y = m_startVelocity.y * sin(m_rad) * m_time - (0.5f * m_gravity * m_time * m_time);
	m_velocity.z = m_dir.z * (m_startVelocity.z * cos(m_rad) * m_time);
}
