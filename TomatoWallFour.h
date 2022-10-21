#pragma once
#include "TomatoWall.h"

class TomatoWallFour : public TomatoWall
{
public:
    TomatoWallFour();
    ~TomatoWallFour();

    // 必ず呼ぶこと
    void Draw() override;
};

