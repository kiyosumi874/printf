﻿#include "pch.h"
#include "TomatoWallFour.h"

TomatoWallFour::TomatoWallFour(ObjectTag tag)
    : TomatoWall(tag)
{
    m_modelName = AssetManager::ModelName::TomatoWallFour;
}

TomatoWallFour::~TomatoWallFour()
{
}

void TomatoWallFour::Draw()
{
    MV1DrawModel(m_var.handle);
}
