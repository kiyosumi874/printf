#include "pch.h"
#include "TomatoWallThree.h"

TomatoWallThree::TomatoWallThree()
    : TomatoWall()
{
    m_modelName = AssetManager::ModelName::TomatoWallThree;
}

TomatoWallThree::~TomatoWallThree()
{
}

void TomatoWallThree::Draw()
{
    MV1DrawModel(m_var.handle);
}
