#pragma once
#include "TomatoWall.h"

class TomatoWallFour : public TomatoWall
{
public:
    TomatoWallFour(ObjectTag tag);
    ~TomatoWallFour();

    // �K���ĂԂ���
    void Draw() override;
};

