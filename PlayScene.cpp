#include "pch.h"
#include "TomatoWall.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "DebugDraw.h"

PlayScene::PlayScene(const MODE& mode)
	: Scene(mode)
{
	//m_map = new Map();

	//// このシーンで使うjsonファイルが読み込めたら
	//if (m_map->OpenFile())
	//{
	//	m_map->GroundCreate();  // 床を生成
	//	//m_map->PlayerCreate();  // プレイヤーを生成
	//}
  
	m_pGround = new Ground(ObjectTag::Ground, VGet(0.0f, -5.0f, 0.0f));
	m_pTomatoWall[0] = new TomatoWall(ObjectTag::TomatoWall, VGet(50.0f, 0.0f, 50.0f));
	m_pTomatoWall[1] = new TomatoWall(ObjectTag::TomatoWall, VGet(150.0f, 0.0f, 150.0f));
	m_pPlayer1P = new Player(ObjectTag::Player1, VGet(0.0f, 0.0f, 0.0f));
	m_pCamera1P = new Camera(ObjectTag::Camera1, VGet(0.0f, 20.0f, 0.0f));
	m_pPlayer2P = new Player(ObjectTag::Player2, VGet(50.0f, 0.0f, 50.0f));
	m_pCamera2P = new Camera(ObjectTag::Camera2, VGet(0.0f, 20.0f, 0.0f));
	m_pEnemy1 = new Enemy(ObjectTag::Enemy, VGet(50.0f, 0.0f, -50.0f));
	m_pEnemy2 = new Enemy(ObjectTag::Enemy, VGet(-50.0f, 0.0f, 50.0f));

	// カメラ
	m_pCamera1P->SetPlayerptr(m_pPlayer1P);
	m_pCamera2P->SetPlayerptr(m_pPlayer2P);

	// プレイヤー
	for (int i = 0; i < m_tomatoWallNum; i++)
	{
		m_pPlayer1P->SetTomatoWallPtr(m_pTomatoWall[i]);
		m_pPlayer2P->SetTomatoWallPtr(m_pTomatoWall[i]);
	}
	// エネミー1
	m_pEnemy1->SetPlayerPtr(m_pPlayer1P);
	m_pEnemy1->SetPlayerPtr(m_pPlayer2P);
	for (int i = 0; i < m_tomatoWallNum; i++)
	{
		m_pEnemy1->SetTomatoWallPtr(m_pTomatoWall[i]);
	}
	// エネミー2
	m_pEnemy2->SetPlayerPtr(m_pPlayer1P);
	m_pEnemy2->SetPlayerPtr(m_pPlayer2P);
	for (int i = 0; i < m_tomatoWallNum; i++)
	{
		m_pEnemy2->SetTomatoWallPtr(m_pTomatoWall[i]);
	}

	for (int i = 0; i < m_tomatoWallNum; i++)
	{
		m_pGameObjects.push_back(m_pTomatoWall[i]);
	}
	m_pGameObjects.push_back(m_pGround);
	m_pGameObjects.push_back(m_pEnemy1);
	m_pGameObjects.push_back(m_pEnemy2);
	m_pGameObjects.push_back(m_pPlayer1P);
	m_pGameObjects.push_back(m_pPlayer2P);
	m_pGameObjects.push_back(m_pCamera1P);
	m_pGameObjects.push_back(m_pCamera2P);

}

PlayScene::~PlayScene()
{
	delete m_pPlayer1P;
	delete m_pCamera1P;
	delete m_pPlayer2P;
	delete m_pCamera2P;
	delete m_pEnemy1;
	delete m_pEnemy2;
	delete m_pGround;
	for (int i = 0; i < m_tomatoWallNum; i++)
	{
		delete m_pTomatoWall[i];
	}
	//delete m_map;
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
	//DrawGrid(1000.0f, 30);
#endif // _DEBUG
	SetDrawArea(0, 0, 640, 960);
	SetCameraScreenCenter(320.0f, 480.0f);
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		if(m_pGameObjects[i]->GetTag() != ObjectTag::Camera2){ m_pGameObjects[i]->Draw(); }
	}
	SetDrawArea(640, 0, 1280, 960);
	SetCameraScreenCenter(960.0f, 480.0f);
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		if (m_pGameObjects[i]->GetTag() != ObjectTag::Camera1) { m_pGameObjects[i]->Draw(); }
	}
	// 描画可能領域を描画対象画面全体にする
	SetDrawAreaFull();
}