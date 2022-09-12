#include "pch.h"
#include "StillProjector.h"
#include "Transform.h"
#include "Input.h"

const float r = -34.0f;
StillProjector::StillProjector()
{
	m_pPlayerTransform = nullptr;

	VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
	m_position = VGet(0.0f, 8.0f, -50.0f);
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
	// プレイヤーの座標を目標視点に代入
	m_targetViewPoint = playerPos;
	auto angle = m_pPlayerTransform->rotate.y;

	//m_position.x = m_targetViewPoint.x + sinf(angle) * r;
	//m_position.z = m_targetViewPoint.z + cosf(angle) * r;

	m_targetViewPoint.x = m_targetViewPoint.x + 2.5f;
	m_targetViewPoint.y = m_targetViewPoint.y + 4.0f;

	//// カメラ位置から目標点に向かうベクトルを計算
	//VECTOR L_lookMoveDir = VSub(m_targetViewPoint, m_targetViewPoint);

	// 前後左右
	VECTOR front = { 0.0f,0.0f,1.0f };
	VECTOR rear = { 0.0f,0.0f,-1.0f };
	VECTOR left = { 1.0f,0.0f,0.0f };
	VECTOR right = { -1.0f,0.0f,0.0f };

	// 前に進む
	if (Input::IsPress1P(BUTTON_ID_UP))
	{
		m_position = VAdd(front, m_position);
	}

	// 後ろに進む
	if (Input::IsPress1P(BUTTON_ID_DOWN))
	{
		m_position = VAdd(rear, m_position);
	}

	// 右に進む
	if (Input::IsPress1P(BUTTON_ID_LEFT))
	{
		m_position = VAdd(right, m_position);
	}

	// 左に進む
	if (Input::IsPress1P(BUTTON_ID_RIGHT))
	{
		m_position = VAdd(left, m_position);
	}

	SetCameraPositionAndTarget_UpVecY(m_position, m_targetViewPoint);
}

void StillProjector::SetPlayerptr(Transform* ptr)
{
	m_pPlayerTransform = ptr;
}
