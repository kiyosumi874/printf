#pragma once
#include "TomatoWall.h"

class TomatoWallThree : public TomatoWall
{
public:
    TomatoWallThree(ObjectTag tag);
    ~TomatoWallThree();

    // 必ず呼ぶこと
    void Draw() override;
};

