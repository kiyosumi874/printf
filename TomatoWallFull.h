#pragma once
#include "TomatoWall.h"

class TomatoWallFull : public TomatoWall
{
public:
    TomatoWallFull();
    ~TomatoWallFull();

    // 必ず呼ぶこと
    void Draw() override;
};

