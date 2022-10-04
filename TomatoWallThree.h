#pragma once
#include "TomatoWall.h"

class TomatoWallThree : public TomatoWall
{
public:
    TomatoWallThree(ObjectTag tag);
    ~TomatoWallThree();

    // •K‚¸ŒÄ‚Ô‚±‚Æ
    void Draw() override;
};

