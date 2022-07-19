#include "pch.h"
#include "Player.h"
#include "Camera.h"
#include "DebugDraw.h"

PlayScene::PlayScene(const MODE& mode)
	: Scene(mode)
{
	m_map = new Map();

	// このシーンで使うjsonファイルが読み込めたら
	if (m_map->OpenFile())
	{
		m_map->GroundCreate();  // 床を生成
		//m_map->PlayerCreate();  // プレイヤーを生成
	}
  
	m_pPlayer = new Player(ObjectTag::Player1, VGet(0.0f, 0.0f, 0.0f));
	m_pGameObjects.push_back(m_pPlayer);
	m_pCamera = new Camera(ObjectTag::Camera, VGet(0.0f, 100.0f, -100.0f));
	m_pCamera->SetPlayerptr(m_pPlayer);
	m_pGameObjects.push_back(m_pCamera);
}

PlayScene::~PlayScene()
{
	delete m_pPlayer;
	delete m_pCamera;
	delete m_map;
	m_pGameObjects.clear();
}

TAG_SCENE PlayScene::Update()
{
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		m_pGameObjects[i]->Update();
	}

	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_OVER;
	}

	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	return TAG_SCENE::TAG_NONE;
}

void PlayScene::Draw()
{
#ifdef _DEBUG
	printfDx("PlayScene\n");
	DrawGrid(1000.0f, 30);
#endif // _DEBUG
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		m_pGameObjects[i]->Draw();
	}
}