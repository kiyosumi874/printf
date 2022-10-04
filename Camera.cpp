#include "pch.h"
#include "Camera.h"
#include "Player1.h"
#include <math.h>

const float r = -30.0f;

Camera::Camera(ObjectTag tag, VECTOR position)
	: m_viewPoint(VGet(0.0f, 0.0f, 0.0f))
	, m_targetCameraPosition(VGet(0.0f, 0.0f, 0.0f))
	, m_targetViewPoint(VGet(0.0f, 0.0f, 0.0f))
{
	m_pPlayer = nullptr;
	m_tag = tag;
	m_position = position;
	m_cameraOffSet = position;
	SetCameraNearFar(1.0f, 3000.0f);
}

Camera::~Camera()
{
}

void Camera::Update()
{
}

void Camera::Draw()
{
	// プレイヤーの座標を目標視点に代入
	/*m_targetViewPoint = m_pPlayer->GetPosition();*/
	/*auto angle = m_pPlayer->GetAngle();*/

	/*m_position.x = m_targetViewPoint.x + sinf(angle) * r;
	m_position.z = m_targetViewPoint.z + cosf(angle) * r;*/

	// カメラの注視点をセット
	m_targetViewPoint.y = m_targetViewPoint.y + 8.0f;
	m_targetCameraPosition = VAdd(m_targetViewPoint, m_cameraOffSet);

	// カメラ位置から目標点に向かうベクトルを計算
	VECTOR L_lookMoveDir = VSub(m_targetViewPoint, m_viewPoint);

	// 注視点とカメラ位置を徐々に目標点に近づける
	m_viewPoint = VAdd(m_viewPoint, L_lookMoveDir);

	SetCameraPositionAndTarget_UpVecY(m_position, m_viewPoint);
}

void Camera::SetPlayerptr(Player1* ptr)
{
	m_pPlayer = ptr;
}
