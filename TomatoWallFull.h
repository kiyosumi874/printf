#pragma once
#include "TomatoWall.h"

class TomatoWallFull : public TomatoWall
{
public:
    TomatoWallFull(ObjectTag tag);
    ~TomatoWallFull();

    // •K‚¸ŒÄ‚Ô‚±‚Æ
    void Draw() override;
};

