#pragma once
#include "TomatoWall.h"

class TomatoWallThree : public TomatoWall
{
public:
    TomatoWallThree();
    ~TomatoWallThree();

    // 必ず呼ぶこと
    void Draw() override;
};

