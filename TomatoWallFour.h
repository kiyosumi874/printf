#pragma once
#include "TomatoWall.h"

class TomatoWallFour : public TomatoWall
{
public:
    TomatoWallFour(ObjectTag tag);
    ~TomatoWallFour();

    // 必ず呼ぶこと
    void Draw() override;
};

