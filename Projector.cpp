#include "pch.h"
#include "Projector.h"
#include "Object.h"
#include "Transform.h"

const float r = -30.0f;
Projector::Projector()
{
}

Projector::~Projector()
{
}

void Projector::Update()
{
	if (m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	auto playerPos = m_pPlayerTransform->transform;
	// �v���C���[�̍��W��ڕW���_�ɑ��
	m_targetViewPoint = playerPos;
	auto angle = m_pPlayer->GetAngle();

	m_position.x = m_targetViewPoint.x + sinf(angle) * r;
	m_position.z = m_targetViewPoint.z + cosf(angle) * r;

	// �J�����̒����_���Z�b�g
	m_targetViewPoint.y = m_targetViewPoint.y + 8.0f;
	m_targetCameraPosition = VAdd(m_targetViewPoint, m_cameraOffSet);

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
