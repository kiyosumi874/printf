#include "pch.h"
#include "TomatoWallFull.h"

TomatoWallFull::TomatoWallFull()
    : TomatoWall()
{
    m_modelName = AssetManager::ModelName::TomatoWallFull;
}

TomatoWallFull::~TomatoWallFull()
{
}

void TomatoWallFull::Draw()
{

    MV1DrawModel(m_var.handle);
}
