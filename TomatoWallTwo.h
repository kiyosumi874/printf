#pragma once
#include "TomatoWall.h"

class TomatoWallTwo : public TomatoWall
{
public:
    TomatoWallTwo(ObjectTag tag);
    ~TomatoWallTwo();

    // 必ず呼ぶこと
    void Draw() override;
};

