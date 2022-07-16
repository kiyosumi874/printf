#include "pch.h"
#include "Camera.h"
#include "Player.h"

Camera::Camera(ObjectTag tag, VECTOR position)
	: m_viewPoint(VGet(0.0f,0.0f,0.0f))
	, m_targetCameraPosition(VGet(0.0f,0.0f,0.0f))
	, m_targetViewPoint(VGet(0.0f,0.0f,0.0f))
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
	m_targetViewPoint = m_pPlayer->GetPosition();
	m_targetCameraPosition = VAdd(m_targetViewPoint, m_cameraOffSet);

	// カメラ位置から目標点に向かうベクトルを計算
	VECTOR L_lookMoveDir = VSub(m_targetViewPoint, m_viewPoint);
	VECTOR L_positionMoveDir = VSub(m_targetCameraPosition, m_position);

	// 注視点とカメラ位置を徐々に目標点に近づける
	m_viewPoint = VAdd(m_viewPoint, L_lookMoveDir);
	m_position = VAdd(m_position, L_positionMoveDir);

	SetCameraPositionAndTarget_UpVecY(m_position, m_viewPoint);
}

void Camera::Draw()
{
}

void Camera::SetPlayerptr(Player* ptr)
{
	m_pPlayer = ptr;
}
