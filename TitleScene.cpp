#include "pch.h"
#include"SkyDome.h"
#include "UIRenderer.h"

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
	, m_images()
	, m_models()
	, m_uiRenderer(new UIRenderer)
{
	InitModel(); // 3Dモデルの初期化
	//InitImage(); // 画像の初期化
	m_uiRenderer->Insert<class Logo>();
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f)); // カメラの位置と向きをセット
}

TitleScene::~TitleScene()
{
	// 画像の終了処理
	for (const auto& it : m_images)
	{
		DeleteGraph(it.modelHandle);
	}
	m_images.clear();

	// 3Dモデルの終了処理
	for (int i = 0; i < ModelName::TomatoWall2; i++)
	{
		MV1DeleteModel(m_models[i]);
	}
	m_models.clear();

	m_uiRenderer->Terminate();

}

TAG_SCENE TitleScene::Update()
{
	UpdateModel(); // 3Dモデルの更新
	//UpdateImage(); // 画像の更新
	m_uiRenderer->Update();
	// 次のシーンへ
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_PLAY;
	}

	// 終了
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	// 次のループもこのシーンを継続
	return TAG_SCENE::TAG_NONE;
}

void TitleScene::Draw()
{
#ifdef _DEBUG
	printfDx("TitleScene\n");
#endif // _DEBUG

	DrawModel(); // 3Dモデルの描画
	//DrawImage(); // 画像の描画
	m_uiRenderer->Draw();
}

void TitleScene::InitImage()
{
	ImageVar var;
	var.InitImageVar(LoadGraph("data/logo.png"), -60, -60, 1200 * 2 / 3, 844 * 2 / 3, 255.0f);
	m_images.emplace_back(var);
	var.InitImageVar(LoadGraph("data/TransitionTitleUI.png"), 450, 850, 799, 96, 100.0f);
	m_images.emplace_back(var);
	var.InitImageVar(LoadGraph("data/postUI.png"), 0, 0, 1920, 1080, 255.0f);
	m_images.emplace_back(var);
}

void TitleScene::UpdateImage()
{
	static bool flag = false;
	if (260.0f < m_images[ImageName::TransitionButton].alpha)
	{
		flag = true;
	}
	if (80.0f > m_images[ImageName::TransitionButton].alpha)
	{
		flag = false;
	}
	if (flag)
	{
		m_images[ImageName::TransitionButton].alpha -= 1.0f;
	}
	else
	{
		m_images[ImageName::TransitionButton].alpha += 1.0f;
	}
}

void TitleScene::DrawImage()
{
	DrawGraph(m_images[ImageName::Gradation].x, m_images[ImageName::Gradation].y, m_images[ImageName::Gradation].modelHandle, TRUE);

	DrawExtendGraph(m_images[ImageName::Logo].x, m_images[ImageName::Logo].y, m_images[ImageName::Logo].x + m_images[ImageName::Logo].width, m_images[ImageName::Logo].y + m_images[ImageName::Logo].height, m_images[ImageName::Logo].modelHandle, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_images[ImageName::TransitionButton].alpha);
	DrawExtendGraph(m_images[ImageName::TransitionButton].x, m_images[ImageName::TransitionButton].y, m_images[ImageName::TransitionButton].x + m_images[ImageName::TransitionButton].width, m_images[ImageName::TransitionButton].y + m_images[ImageName::TransitionButton].height, m_images[ImageName::TransitionButton].modelHandle, TRUE);
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
