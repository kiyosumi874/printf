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
    // Blendの加算処理を行う
    SetDrawBlendMode(DX_BLENDMODE_ADD_X4, 255);
    // 画像を拡大表示
    DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,m_movieHandle, false);
    // デフォルトに戻す
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}
