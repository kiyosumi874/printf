#include "pch.h"
#include "Tag.h"
#include "TomatoWall.h"

TomatoWall::TomatoWall()
{
}

TomatoWall::~TomatoWall()
{
}

void TomatoWall::Update()
{
}

void TomatoWall::Draw()
{
}

void TomatoWall::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
    m_var.Init(MV1DuplicateModel(AssetManager::UseModel(m_modelName)), pos, rotate, scale);
    MV1SetScale(m_var.handle, m_var.scale);
    MV1SetPosition(m_var.handle, m_var.pos);
}
