#include "pch.h"

App::App()
{
	SetMainWindowText("BarrageStudy");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT_DEPTH);
	ChangeWindowMode(FALSE);
	SetWaitVSyncFlag(FALSE);
	SetOutApplicationLogValidFlag(FALSE); // Log.txtを書き出さないようにする
	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(FALSE);
	Sound::Load(Sound::Kind::Throw, "SE/Throw/Throw_0.mp3");
	Sound::Load(Sound::Kind::CountDown, "SE/count.mp3");
	AssetManager::LoadImage(AssetManager::ImageName::Logo, "data/logo.png");
	AssetManager::LoadImage(AssetManager::ImageName::Gradation, "data/postUI.png");
	AssetManager::LoadImage(AssetManager::ImageName::TransitionButton, "data/TransitionTitleUI.png");
	AssetManager::LoadModel(AssetManager::ModelName::Ground, "data/Ground/Ground.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::SkyDome, "data/Skydome_T2/Dome_T201.pmx");
	AssetManager::LoadModel(AssetManager::ModelName::Team1, "data/character/man1.mv1");             // 人モデル(男1)
	AssetManager::LoadModel(AssetManager::ModelName::Team2, "data/character/man3.mv1");             // 人モデル(男3)
	AssetManager::LoadModel(AssetManager::ModelName::Team3, "data/character/woman2.mv1");           // 人モデル(女2)
	AssetManager::LoadModel(AssetManager::ModelName::Tomato, "data/Tomato/Tomato.mv1");             // トマトモデル
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallFull, "data/Tomato/FullTomatoWall.mv1");    // トマトの山モデル(満タン)
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallOne,"data/Tomato/TomatoWall_one.mv1");      // トマトの山モデル(一段階目)
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallTwo,"data/Tomato/TomatoWall_two.mv1");      // トマトの山モデル(二段階目)
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallThree,"data/Tomato/TomatoWall_three.mv1");  // トマトの山モデル(三段階目)
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallFour,"data/Tomato/TomatoWall_four.mv1");    // トマトの山モデル(四段階目)
	AssetManager::LoadModel(AssetManager::ModelName::Icon1, "data/Icon/Red.mv1");     // アイコンモデル(赤色)
	AssetManager::LoadModel(AssetManager::ModelName::Icon2, "data/Icon/Blue.mv1");    // アイコンモデル(青色)
	AssetManager::LoadModel(AssetManager::ModelName::Icon3, "data/Icon/Green.mv1");   // アイコンモデル(緑色)

	m_sceneManager = new SceneManager();
	m_sceneManager->SetNowScene(TAG_SCENE::TAG_TITLE);

	// Effekseerの初期化
	if (Effekseer_Init(8000) == -1)
	{
		printf("Effekseer初期化に失敗！\n");	// エラーが起きたら直ちに終了
	}
}

App::~App()
{
	Sound::InitSound();
	AssetManager::Terminate();
	delete m_sceneManager;
	m_sceneManager = 0;

	// Effekseerの終了
	Effkseer_End();

	DxLib_End();
}

void App::GameLoop()
{
	m_sceneManager->GameLoop();
}

