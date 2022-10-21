#include "pch.h"
#include "TomatoWallTwo.h"

TomatoWallTwo::TomatoWallTwo()
    : TomatoWall()
{
    m_modelName = AssetManager::ModelName::TomatoWallTwo;
}

TomatoWallTwo::~TomatoWallTwo()
{
}

void TomatoWallTwo::Draw()
{
    MV1DrawModel(m_var.handle);
}
