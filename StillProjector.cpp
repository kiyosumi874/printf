#include "pch.h"
#include "StillProjector.h"
#include "Transform.h"
#include "Input.h"

StillProjector::StillProjector()
{
	m_pPlayerTransform = nullptr;

	VECTOR vec = VGet(0.0f, 4.0f, 0.0f);
	m_position = VGet(0.0f, 15.0f, -50.0f);
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
	SetCameraPositionAndTarget_UpVecY(m_position, m_targetViewPoint);
}

