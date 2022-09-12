#include "pch.h"
#include "StillProjector.h"
#include "Transform.h"

const float r = -34.0f;
StillProjector::StillProjector()
{
	m_pPlayerTransform = nullptr;

	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	m_position = VGet(0.0f, 16.0f, 0.0f);
	m_targetViewPoint = vec;
	m_viewPoint = vec;
	SetCameraNearFar(1.0f, 3000.0f);
}

StillProjector::~StillProjector()
{
}

void StillProjector::Start()
{
}

void StillProjector::Update()
{
}

void StillProjector::Draw()
{
	auto& playerPos = m_pPlayerTransform->position;
	// �v���C���[�̍��W��ڕW���_�ɑ��
	m_targetViewPoint = playerPos;
	auto angle = m_pPlayerTransform->rotate.y;

	m_position.x = m_targetViewPoint.x + sinf(angle) * r;
	m_position.z = m_targetViewPoint.z + cosf(angle) * r;

	m_targetViewPoint.x = m_targetViewPoint.x + 2.5f;
	m_targetViewPoint.y = m_targetViewPoint.y + 4.0f;

	// �J�����ʒu����ڕW�_�Ɍ������x�N�g�����v�Z
	VECTOR L_lookMoveDir = VSub(m_targetViewPoint, m_viewPoint);

	// �����_�ƃJ�����ʒu�����X�ɖڕW�_�ɋ߂Â���
	m_viewPoint = VAdd(m_viewPoint, L_lookMoveDir);

	SetCameraPositionAndTarget_UpVecY(m_position, m_viewPoint);
}

void StillProjector::SetPlayerptr(Transform* ptr)
{
	m_pPlayerTransform = ptr;
}
