#include "pch.h"

App::App()
{
	SetMainWindowText("BarrageStudy");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT_DEPTH);
	ChangeWindowMode(TRUE);
	SetWaitVSyncFlag(FALSE);
	// DirectX11を使用するようにする。(DirectX9も可、一部機能不可)
	// Effekseerを使用するには必ず設定する。
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	m_sceneManager = new SceneManager();
	m_sceneManager->SetNowScene(TAG_SCENE::TAG_TITLE);
}

App::~App()
{
	delete m_sceneManager;
	m_sceneManager = 0;

	DxLib_End();
}

void App::GameLoop()
{
	m_sceneManager->GameLoop();
}
