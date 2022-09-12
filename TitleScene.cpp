#include "pch.h"
#include"SkyDome.h"

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
{
	m_logoGraph = LoadGraph("data/logo.png");
	m_enterGraph = LoadGraph("data/TransitionTitleUI.png");
	m_postUIGraph = LoadGraph("data/postUI.png");
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f));
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_logoGraph);
	DeleteGraph(m_enterGraph);
	DeleteGraph(m_postUIGraph);
}

TAG_SCENE TitleScene::Update()
{
	RotateSkyDome();
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_PLAY;
	}

	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	return TAG_SCENE::TAG_NONE;
}

void TitleScene::Draw()
{
#ifdef _DEBUG
	printfDx("TitleScene\n");
#endif // _DEBUG
	DrawSkyDome();
	DrawGraph(0, 0, m_postUIGraph, TRUE);
	/*int posX = 250;
	int posY = 130;*/
	int posX = -100;
	int posY = -100;
	int sizeX = 1200 * 2 / 3;
	int sizeY = 844 * 2 / 3;
	DrawExtendGraph(posX, posY, posX + sizeX, posY + sizeY, m_logoGraph, TRUE);
	posX = 450;
	posY = 850;
	sizeX = 799;
	sizeY = 96;
	static float alpha = 100.0f;
	static bool flag = false;
	if (260.0f < alpha)
	{
		flag = true;
	}
	if (80.0f > alpha)
	{
		flag = false;
	}
	if (flag)
	{
		alpha -= 1.0f;
	}
	else
	{
		alpha += 1.0f;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawExtendGraph(posX, posY, posX + sizeX, posY + sizeY, m_enterGraph, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255.0f);
}