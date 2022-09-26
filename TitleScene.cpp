#include "pch.h"
#include"SkyDome.h"

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
{
	m_logoGraph = LoadGraph("data/logo.png");
	m_enterGraph = LoadGraph("data/TransitionTitleUI.png");
	m_postUIGraph = LoadGraph("data/postUI.png");
	m_groundHandle = MV1LoadModel("data/Ground/Ground.mv1");
	MV1SetScale(m_groundHandle, VGet(3.0f, 0.4f, 3.0f));
	MV1SetPosition(m_groundHandle, VGet(0.0f, -100.0f, 560.0f));
	m_tomatoHandle = MV1LoadModel("data/Tomato/FullTomatoWall.mv1");
	m_tomatoHandle2 = MV1DuplicateModel(m_tomatoHandle);
	m_tomatoHandle3 = MV1DuplicateModel(m_tomatoHandle);
	MV1SetScale(m_tomatoHandle, VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(m_tomatoHandle, VGet(0.0f, -96.0f, 630.0f));
	MV1SetScale(m_tomatoHandle2, VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(m_tomatoHandle2, VGet(100.0f, -96.0f, 380.0f));
	MV1SetScale(m_tomatoHandle3, VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(m_tomatoHandle3, VGet(-100.0f, -96.0f, 380.0f));
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f));
}

TitleScene::~TitleScene()
{
	DeleteGraph(m_logoGraph);
	DeleteGraph(m_enterGraph);
	DeleteGraph(m_postUIGraph);
	MV1DeleteModel(m_groundHandle);
	MV1DeleteModel(m_tomatoHandle);
}

TAG_SCENE TitleScene::Update()
{
	RotateSkyDome();
	static float rot = 0;
	rot += 0.1;
	MV1SetRotationXYZ(m_groundHandle, VGet(0.0f, rot * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(m_tomatoHandle, VGet(0.0f, -rot * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(m_tomatoHandle2, VGet(0.0f, -rot * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(m_tomatoHandle3, VGet(0.0f, -rot * DX_PI_F / 180.0f, 0.0f));

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
	MV1DrawModel(m_groundHandle);
	MV1DrawModel(m_tomatoHandle);
	MV1DrawModel(m_tomatoHandle2);
	MV1DrawModel(m_tomatoHandle3);
	DrawGraph(0, 0, m_postUIGraph, TRUE);
	/*int posX = 250;
	int posY = 130;*/
	int posX = -100;
	int posY = -100;
	int sizeX = 1200 * 2 / 3;
	int sizeY = 844 * 2 / 3;
	DrawExtendGraph(posX+40, posY+ 40, posX + sizeX- 40, posY + sizeY- 40, m_logoGraph, TRUE);
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