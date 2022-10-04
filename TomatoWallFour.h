#pragma once
#include "TomatoWall.h"

class TomatoWallFour : public TomatoWall
{
public:
    TomatoWallFour(ObjectTag tag);
    ~TomatoWallFour();

    // •K‚¸ŒÄ‚Ô‚±‚Æ
    void Draw() override;
};

