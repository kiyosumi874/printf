#pragma once
#include "TomatoWall.h"

class TomatoWallTwo : public TomatoWall
{
public:
    TomatoWallTwo(ObjectTag tag);
    ~TomatoWallTwo();

    // •K‚¸ŒÄ‚Ô‚±‚Æ
    void Draw() override;
};

