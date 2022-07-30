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

