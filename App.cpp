#include "pch.h"

App::App()
{
	SetMainWindowText("BarrageStudy");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT_DEPTH);
	ChangeWindowMode(FALSE);
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
	AssetManager::LoadModel(AssetManager::ModelName::SkyDome, "data/Skydome_T2/Dome_T201.pmx");
	AssetManager::LoadModel(AssetManager::ModelName::Team1, "data/character/man1.mv1");             // �l���f��(�j1)
	AssetManager::LoadModel(AssetManager::ModelName::Team2, "data/character/man3.mv1");             // �l���f��(�j3)
	AssetManager::LoadModel(AssetManager::ModelName::Team3, "data/character/woman2.mv1");           // �l���f��(��2)
	AssetManager::LoadModel(AssetManager::ModelName::Tomato, "data/Tomato/Tomato.mv1");             // �g�}�g���f��
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallFull, "data/Tomato/FullTomatoWall.mv1");    // �g�}�g�̎R���f��(���^��)
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallOne,"data/Tomato/TomatoWall_one.mv1");      // �g�}�g�̎R���f��(��i�K��)
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallTwo,"data/Tomato/TomatoWall_two.mv1");      // �g�}�g�̎R���f��(��i�K��)
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallThree,"data/Tomato/TomatoWall_three.mv1");  // �g�}�g�̎R���f��(�O�i�K��)
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallFour,"data/Tomato/TomatoWall_four.mv1");    // �g�}�g�̎R���f��(�l�i�K��)
	AssetManager::LoadModel(AssetManager::ModelName::Icon1, "data/Icon/Red.mv1");     // �A�C�R�����f��(�ԐF)
	AssetManager::LoadModel(AssetManager::ModelName::Icon2, "data/Icon/Blue.mv1");    // �A�C�R�����f��(�F)
	AssetManager::LoadModel(AssetManager::ModelName::Icon3, "data/Icon/Green.mv1");   // �A�C�R�����f��(�ΐF)

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

