#pragma once
#include "TomatoWall.h"

class TomatoWallTwo : public TomatoWall
{
public:
    TomatoWallTwo();
    ~TomatoWallTwo();

    // 必ず呼ぶこと
    void Draw() override;
};

