#include "pch.h"
#include "TomatoWallOne.h"

TomatoWallOne::TomatoWallOne(ObjectTag tag)
    : TomatoWall(m_tag)
{
    m_modelName = AssetManager::ModelName::TomatoWallOne;
}

TomatoWallOne::~TomatoWallOne()
{
}

void TomatoWallOne::Draw()
{
    MV1DrawModel(m_var.handle);
}
