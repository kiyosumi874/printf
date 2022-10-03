#include "pch.h"

TitleTomatoWall::TitleTomatoWall()
	: m_rotate(0.0f)
{
	// ��������
}

TitleTomatoWall::~TitleTomatoWall()
{
	// ��������
}

void TitleTomatoWall::Start()
{
	// ��������
}

void TitleTomatoWall::Update()
{
	m_rotate -= 0.1f;
	m_var.rotate.y = m_rotate * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
}

void TitleTomatoWall::Draw()
{
	MV1DrawModel(m_var.handle);
}

void TitleTomatoWall::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
	// �����������郂�f����Duplicate����
	m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::TomatoWallFull)), pos, rotate, scale);
	MV1SetScale(m_var.handle, m_var.scale);
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);
}
