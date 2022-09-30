#include "pch.h"

TitleGround::TitleGround()
	: m_rotate(0.0f)
{
	// èàóùñ≥Çµ
}

TitleGround::~TitleGround()
{
	// èàóùñ≥Çµ
}

void TitleGround::Start()
{
	m_var.Init(AssetManager::UseModel(AssetManager::ModelName::Ground), VGet(0.0f, -100.0f, 560.0f), VGet(0.0f, 0.0f, 0.0f), VGet(3.0f, 0.4f, 3.0f));
	MV1SetScale(m_var.handle, m_var.scale);
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);
}

void TitleGround::Update()
{
	m_rotate += 0.1f;
	m_var.rotate.y = m_rotate * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
}

void TitleGround::Draw()
{
	MV1DrawModel(m_var.handle);
}
