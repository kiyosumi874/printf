#include "pch.h"
#include "Projector.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"

const float r = -30.0f;
Projector::Projector()
{
	m_pPlayerTransform = nullptr;

	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	m_position = VGet(0.0f, 20.0f, 0.0f);
	m_targetViewPoint = vec;
	m_viewPoint = vec;
	m_cameraOffset = VGet(50.0f, 30.0f, 50.0f);
	SetCameraNearFar(1.0f, 3000.0f);
}

Projector::~Projector()
{
}

void Projector::Start()
{
}

void Projector::Update()
{

}

void Projector::Draw()
{
#ifdef _DEBUG
	printfDx("ProjectorX:%f\n", m_pPlayerTransform->position.x);
	printfDx("ProjectorY:%f\n", m_pPlayerTransform->position.y);
	printfDx("ProjectorZ:%f\n", m_pPlayerTransform->position.z);
#endif // _DEBUG
	auto playerPos = m_pPlayerTransform->position;
	// プレイヤーの座標を目標視点に代入
	m_targetViewPoint = playerPos;
	VECTOR angle = m_pPlayerTransform->rotate;

	m_position.x = m_targetViewPoint.x + sinf(angle.y) * r;
	m_position.z = m_targetViewPoint.z + cosf(angle.y) * r;
	/*CalculatePosition(angle);*/
	printbDX("ProrotateY:%f", angle.y);

	// カメラの注視点をセット
	m_targetViewPoint.y = m_targetViewPoint.y + 8.0f;
	// カメラ位置から目標点に向かうベクトルを計算
	VECTOR L_lookMoveDir = VSub(m_targetViewPoint, m_position);

	// 注視点とカメラ位置を徐々に目標点に近づける
	m_viewPoint = VAdd(m_viewPoint, L_lookMoveDir);

	SetCameraPositionAndTarget_UpVecY(m_position, m_targetViewPoint);
}

void Projector::CalculatePosition(const VECTOR& angle)
{
	if (angle.x < 0.0f)
	{
		m_position.x = m_targetViewPoint.x + m_cameraOffset.x * angle.x;
	}
	else if(angle.x > 0.0f)
	{
		m_position.x = m_targetViewPoint.x + m_cameraOffset.x * angle.x;
	}

	m_position.y = m_targetViewPoint.y + m_cameraOffset.y;

	if (angle.z < 0.0f)
	{
		m_position.z = m_targetViewPoint.z + m_cameraOffset.z * angle.z;
	}
	else if(angle.z > 0.0f)
	{
		m_position.z = m_targetViewPoint.z + m_cameraOffset.z * angle.z;
	}
}

void Projector::SetPlayerptr(Transform* ptr)
{
	m_pPlayerTransform = ptr;
}
