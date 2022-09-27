#include "pch.h"
#include"SkyDome.h"

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
	, m_images()
	, m_models()
{
	InitImage();
	InitModel();
	
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f));
}

TitleScene::~TitleScene()
{
	for (auto it : m_images)
	{
		DeleteGraph(it);
	}
	for (int i = 0; i < ModelName::TomatoWall2; i++)
	{
		MV1DeleteModel(m_models[i]);
	}
	m_images.clear();
	m_models.clear();
}

TAG_SCENE TitleScene::Update()
{
	UpdateModel();
	UpdateImage();
	

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

	DrawModel();
	DrawImage();

	
}

void TitleScene::InitImage()
{
	m_images.emplace_back(LoadGraph("data/logo.png"));
	m_images.emplace_back(LoadGraph("data/TransitionTitleUI.png"));
	m_images.emplace_back(LoadGraph("data/postUI.png"));
}

void TitleScene::UpdateImage()
{
}

void TitleScene::DrawImage()
{
	DrawGraph(0, 0, m_images[ImageName::Gradation], TRUE);
	int posX = -100;
	int posY = -100;
	int sizeX = 1200 * 2 / 3;
	int sizeY = 844 * 2 / 3;
	DrawExtendGraph(posX + 40, posY + 40, posX + sizeX - 40, posY + sizeY - 40, m_images[ImageName::Logo], TRUE);
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
	DrawExtendGraph(posX, posY, posX + sizeX, posY + sizeY, m_images[ImageName::TransitionButton], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255.0f);
}

void TitleScene::InitModel()
{
	m_models.emplace_back(MV1LoadModel("data/Ground/Ground.mv1"));
	MV1SetScale(m_models[ModelName::Ground], VGet(3.0f, 0.4f, 3.0f));
	MV1SetPosition(m_models[ModelName::Ground], VGet(0.0f, -100.0f, 560.0f));

	m_models.emplace_back(MV1LoadModel("data/Tomato/FullTomatoWall.mv1"));
	MV1SetScale(m_models[ModelName::TomatoWall1], VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(m_models[ModelName::TomatoWall1], VGet(0.0f, -96.0f, 630.0f));

	m_models.emplace_back(MV1DuplicateModel(m_models[ModelName::TomatoWall1]));
	MV1SetScale(m_models[ModelName::TomatoWall2], VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(m_models[ModelName::TomatoWall2], VGet(100.0f, -96.0f, 380.0f));

	m_models.emplace_back(MV1DuplicateModel(m_models[ModelName::TomatoWall1]));
	MV1SetScale(m_models[ModelName::TomatoWall3], VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(m_models[ModelName::TomatoWall3], VGet(-100.0f, -96.0f, 380.0f));
}

void TitleScene::UpdateModel()
{
	RotateSkyDome();
	static float rot = 0;
	rot += 0.1;
	MV1SetRotationXYZ(m_models[ModelName::Ground], VGet(0.0f, rot * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(m_models[ModelName::TomatoWall1], VGet(0.0f, -rot * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(m_models[ModelName::TomatoWall2], VGet(0.0f, -rot * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(m_models[ModelName::TomatoWall3], VGet(0.0f, -rot * DX_PI_F / 180.0f, 0.0f));
}

void TitleScene::DrawModel()
{
	DrawSkyDome();
	for (auto it : m_models)
	{
		MV1DrawModel(it);
	}
}
