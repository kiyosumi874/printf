#include "pch.h"

App::App()
{
	SetMainWindowText("BarrageStudy");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT_DEPTH);
	ChangeWindowMode(TRUE);
	SetWaitVSyncFlag(FALSE);
	SetOutApplicationLogValidFlag(FALSE); // Log.txtを書き出さないようにする
	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(FALSE);
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

