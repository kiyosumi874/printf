#include "pch.h"
#include "TomatoWallThree.h"

TomatoWallThree::TomatoWallThree(ObjectTag tag)
    : TomatoWall(tag)
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
