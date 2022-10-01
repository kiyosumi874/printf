#include "pch.h"

SkyDome::SkyDome()
	: m_rotate(0.0f)
{
	// èàóùñ≥Çµ
}

SkyDome::~SkyDome()
{
	// èàóùñ≥Çµ
}

void SkyDome::Start()
{
	m_var.Init(AssetManager::UseModel(AssetManager::ModelName::SkyDome), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f));
	MV1SetScale(m_var.handle, m_var.scale);
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);
}

void SkyDome::Update()
{
	m_rotate += 0.0025f;
	m_var.rotate.y = m_rotate * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
}

void SkyDome::Draw()
{
	MV1DrawModel(m_var.handle);
}
