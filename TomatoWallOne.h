#pragma once
#include "TomatoWall.h"

class TomatoWallOne : public TomatoWall
{
public:
    TomatoWallOne(ObjectTag tag);
    ~TomatoWallOne();

    // 必ず呼ぶこと
    void Draw() override;
};

