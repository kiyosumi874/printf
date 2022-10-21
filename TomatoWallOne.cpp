#include "pch.h"
#include "TomatoWallOne.h"

TomatoWallOne::TomatoWallOne()
    : TomatoWall()
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
