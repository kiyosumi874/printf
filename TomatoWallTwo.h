#pragma once
#include "TomatoWall.h"

class TomatoWallTwo : public TomatoWall
{
public:
    TomatoWallTwo(ObjectTag tag);
    ~TomatoWallTwo();

    // �K���ĂԂ���
    void Draw() override;
};

