#include "pch.h"
#include "TitleConfetti.h"

TitleConfetti::TitleConfetti()
{
}

TitleConfetti::~TitleConfetti()
{
    DeleteGraph(m_movieHandle);
}

void TitleConfetti::Start()
{
    m_movieHandle = LoadGraph("data/animation/confetti-40.gif");
    PlayMovieToGraph(m_movieHandle, DX_PLAYTYPE_LOOP);
}

void TitleConfetti::Update()
{
}

void TitleConfetti::Draw()
{
    // Blend�̉��Z�������s��
    SetDrawBlendMode(DX_BLENDMODE_ADD_X4, 255);
    // �摜���g��\��
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,m_movieHandle, false);
    // �f�t�H���g�ɖ߂�
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}
