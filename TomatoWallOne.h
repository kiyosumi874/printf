#pragma once
#include "TomatoWall.h"

class TomatoWallOne : public TomatoWall
{
public:
    TomatoWallOne(ObjectTag tag);
    ~TomatoWallOne();

    // �K���ĂԂ���
    void Draw() override;
};

