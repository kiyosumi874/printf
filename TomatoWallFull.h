#pragma once
#include "TomatoWall.h"

class TomatoWallFull : public TomatoWall
{
public:
    TomatoWallFull(ObjectTag tag);
    ~TomatoWallFull();

    // �K���ĂԂ���
    void Draw() override;
};

