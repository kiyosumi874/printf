#pragma once
#include "Component.h"

class TitleConfetti : public Component
{
public:
    TitleConfetti();
    ~TitleConfetti();

    void Start() override;
    void Update() override;
    void Draw() override;

private:
    int m_movieHandle;
    int m_screenHandle;

    int m_sizeX;
    int m_sizeY;

    int m_imageCounter = 0;
    char m_filePath[256];
};

