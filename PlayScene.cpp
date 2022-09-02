#include "pch.h"
#include "TomatoWall.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "DebugDraw.h"
#include "Object.h"
#include "Human.h"
#include "Transform.h"
#include "Tag.h"
#include "TimeCount.h"
#include "Image.h"
#include "TimeUIController.h"

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
	m_pGameObjects.push_back(m_pEnemy1);
	m_pGameObjects.push_back(m_pEnemy2);
	m_pGameObjects.push_back(m_pPlayer1P);
	m_pGameObjects.push_back(m_pPlayer2P);
	m_pGameObjects.push_back(m_pCamera1P);
	m_pGameObjects.push_back(m_pCamera2P);

	Object* obj = new Object;
	auto trs = obj->AddComponent<Transform>();
	trs->position = VGet(5.0f, 0.0f, 0.0f);
	trs->rotate = VGet(0.0f, 0.0f, 0.0f);
	trs->scale = VGet(0.1f, 0.1f, 0.1f);
	auto tag = obj->AddComponent<Tag>();
	tag->tag = ObjectTag::Player1;
	obj->AddComponent<Human>();
	m_pObjectLists.push_back(obj);

	// kiyosumi
	{
		Object* object = nullptr;
		int x = 450;
		for (int i = 0; i < 4; i++)
		{
			x -= 200;
			for (int j = 0; j < 10; j++)
			{
				std::string str = "data/Number/";
				str += std::to_string(j);
				str += ".png";
				object = new Object;
				object->AddComponent<TimeCount>();
				auto img = object->AddComponent<Image>(); 
				img->Init(VGet(SCREEN_WIDTH / 2 + x, SCREEN_HEIGHT / 2 + 200, 1.0f), VGet(1.0f, 1.0f, 1.0f), 0.0, str.c_str());
				if (j != 0)
				{
					img->IsDraw(false);
				}

				object->AddComponent<TimeUIController>()->Init(i, j);
				m_pObjectLists.push_back(object);
			}
		}
	}
}

PlayScene::~PlayScene()
{
	delete m_pPlayer1P;
	delete m_pCamera1P;
	delete m_pPlayer2P;
	delete m_pCamera2P;
	delete m_pEnemy1;
	delete m_pEnemy2;
	for (int i = 0; i < m_tomatoWallNum; i++)
	{
		delete m_pTomatoWall[i];
	}
	delete m_map;
	for (auto obj : m_pObjectLists)
	{
		delete obj;
	}
	m_pObjectLists.clear();
	m_pGameObjects.clear();
}

TAG_SCENE PlayScene::Update()
{
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		m_pGameObjects[i]->Update();
	}
	for(auto obj : m_pObjectLists)
	{
		obj->Update();
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
#endif // _DEBUG
	SetDrawArea(0, 0, 640, 960);
	SetCameraScreenCenter(320.0f, 480.0f);
	DrawGrid(1000.0f, 30);
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		if(m_pGameObjects[i]->GetTag() != ObjectTag::Camera2){ m_pGameObjects[i]->Draw(); }
	}
	for (auto obj : m_pObjectLists)
	{
		//auto com = obj->
		//if(com->tag != ObjectTag::Camera2)
		obj->Draw();
	}
	SetDrawArea(640, 0, 1280, 960);
	SetCameraScreenCenter(960.0f, 480.0f);
	DrawGrid(1000.0f, 30);
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		if (m_pGameObjects[i]->GetTag() != ObjectTag::Camera1) { m_pGameObjects[i]->Draw(); }
	}
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
	// 描画可能領域を描画対象画面全体にする
	SetDrawAreaFull();
}