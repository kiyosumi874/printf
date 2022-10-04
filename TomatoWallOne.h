#pragma once
#include "TomatoWall.h"

class TomatoWallOne : public TomatoWall
{
public:
    TomatoWallOne(ObjectTag tag);
    ~TomatoWallOne();

    // •K‚¸ŒÄ‚Ô‚±‚Æ
    void Draw() override;
};

