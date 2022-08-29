#include "pch.h"
#include "Projector.h"
#include "Object.h"
#include "Transform.h"

const float r = -30.0f;
Projector::Projector()
{
	m_pPlayerTransform = nullptr;

	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	m_position = vec;
	m_targetViewPoint = vec;
	m_viewPoint = vec;
}

Projector::~Projector()
{
}

void Projector::Update()
{
	auto& playerPos = m_pPlayerTransform->position;
	// �v���C���[�̍��W��ڕW���_�ɑ��
	m_targetViewPoint = playerPos;
	auto& angle = m_pPlayerTransform->rotate.y;

	m_position.x = m_targetViewPoint.x + sinf(angle) * r;
	m_position.z = m_targetViewPoint.z + cosf(angle) * r;

	// �J�����̒����_���Z�b�g
	m_targetViewPoint.y = m_targetViewPoint.y + 8.0f;

	// �J�����ʒu����ڕW�_�Ɍ������x�N�g�����v�Z
	VECTOR L_lookMoveDir = VSub(m_targetViewPoint, m_viewPoint);

	// �����_�ƃJ�����ʒu�����X�ɖڕW�_�ɋ߂Â���
	m_viewPoint = VAdd(m_viewPoint, L_lookMoveDir);

	SetCameraPositionAndTarget_UpVecY(m_position, m_viewPoint);
}

void Projector::SetPlayerptr(Transform* ptr)
{
	m_pPlayerTransform = ptr;
}