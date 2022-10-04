#include "pch.h"

TitleTomatoWall::TitleTomatoWall()
	: m_rotate(0.0f)
{
	// 処理無し
}

TitleTomatoWall::~TitleTomatoWall()
{
	// 処理無し
}

void TitleTomatoWall::Start()
{
	// 処理無し
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
	// 複数生成するモデルはDuplicateする
	m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::TomatoWallFull)), pos, rotate, scale);
	MV1SetScale(m_var.handle, m_var.scale);
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);
}
