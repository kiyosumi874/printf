#include "pch.h"

App::App()
{
	SetMainWindowText("BarrageStudy");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT_DEPTH);
	ChangeWindowMode(TRUE);
	SetWaitVSyncFlag(FALSE);
	SetOutApplicationLogValidFlag(FALSE); // Log.txt�������o���Ȃ��悤�ɂ���
	// DirectX11���g�p����悤�ɂ���B(DirectX9���A�ꕔ�@�\�s��)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
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
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallFull, "data/Tomato/FullTomatoWall.mv1");

	m_sceneManager = new SceneManager();
	m_sceneManager->SetNowScene(TAG_SCENE::TAG_TITLE);

	// Effekseer�̏�����
	if (Effekseer_Init(8000) == -1)
	{
		printf("Effekseer�������Ɏ��s�I\n");	// �G���[���N�����璼���ɏI��
	}
}

App::~App()
{
	Sound::InitSound();
	AssetManager::Terminate();
	delete m_sceneManager;
	m_sceneManager = 0;

	// Effekseer�̏I��
	Effkseer_End();

	DxLib_End();
}

void App::GameLoop()
{
	m_sceneManager->GameLoop();
}

