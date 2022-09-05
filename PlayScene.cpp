#include "pch.h"
#include "TomatoWall.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"
#include "DebugDraw.h"
#include "Object.h"
#include "Human.h"
#include "Collider.h"
#include "Projector.h"
#include "Transform.h"
#include "Tag.h"
#include "TimeCount.h"
#include "Image.h"
#include "TimeUIController.h"


// いたっんおいてる定数.いつの日かまとめる
const int timerUIY = SCREEN_HEIGHT / 2 + 200;

PlayScene::PlayScene(const MODE& mode)
	: Scene(mode)
	, m_transition(Transition::START)
	, m_tagScene(TAG_SCENE::TAG_NONE)
	, m_timeCount(nullptr)
	, m_isStartBlendAdd(false)
	, m_startBlendAdd(0.0f)
	, m_graphHandleWhite(-1)
{
	for (int i = 0; i < 2; i++)
	{
		m_transitionImage[i] = nullptr;
	}

	m_map = new Map();

	// このシーンで使うjsonファイルが読み込めたら
	if (m_map->OpenFile())
	{
		m_map->GroundCreate();  // 床を生成
		//m_map->PlayerCreate();  // プレイヤーを生成
	}
  
	m_pTomatoWall[0] = new TomatoWall(ObjectTag::TomatoWall, VGet(50.0f, 0.0f, 50.0f));
	m_pTomatoWall[1] = new TomatoWall(ObjectTag::TomatoWall, VGet(150.0f, 0.0f, 150.0f));

	for (int i = 0; i < m_tomatoWallNum; i++)
	{
		m_pGameObjects.push_back(m_pTomatoWall[i]);
	}

	// 以前の初期化
	{
	//m_pEnemy1 = new Enemy(ObjectTag::Enemy, VGet(50.0f, 0.0f, -50.0f));
	//m_pEnemy2 = new Enemy(ObjectTag::Enemy, VGet(-50.0f, 0.0f, 50.0f));

	// プレイヤー
	//for (int i = 0; i < m_tomatoWallNum; i++)
	//{
	//	m_pPlayer1P->SetTomatoWallPtr(m_pTomatoWall[i]);
	//	m_pPlayer2P->SetTomatoWallPtr(m_pTomatoWall[i]);
	//}
	// エネミー1
	//m_pEnemy1->SetPlayerPtr(m_pPlayer2P);
	//m_pEnemy1->SetPlayerPtr(m_pPlayer2P);
	//for (int i = 0; i < m_tomatoWallNum; i++)
	//{
	//	m_pEnemy1->SetTomatoWallPtr(m_pTomatoWall[i]);
	//}
	// エネミー2
	//m_pEnemy2->SetPlayerPtr(m_pPlayer2P);
	//m_pEnemy2->SetPlayerPtr(m_pPlayer2P);
	//for (int i = 0; i < m_tomatoWallNum; i++)
	//{
	//	m_pEnemy2->SetTomatoWallPtr(m_pTomatoWall[i]);
	//}	
	//m_pGameObjects.push_back(m_pEnemy1);
	//m_pGameObjects.push_back(m_pEnemy2);
	//m_pGameObjects.push_back(m_pPlayer1P);
	//m_pGameObjects.push_back(m_pPlayer2P);
	//m_pGameObjects.push_back(m_pCamera1P);
	//m_pGameObjects.push_back(m_pCamera2P);
	}


	// iguchi
	// playerを2つ生成
	{
		{
			Object* obj = new Object;
			auto trs = obj->AddComponent<Transform>();
			trs->position = VGet(0.0f, 0.0f, 0.0f);
			auto tag = obj->AddComponent<Tag>();
			tag->tag = ObjectTag::Player1;
			obj->AddComponent<Collider>()->Init(&m_pObjectLists);
			auto p1 = obj->AddComponent<Human>();
			m_pObjectLists.push_back(obj);
		}
		{
			Object* obj = new Object;
			auto trs = obj->AddComponent<Transform>();
			trs->position = VGet(20.0f, 0.0f, 20.0f);
			auto tag = obj->AddComponent<Tag>();
			tag->tag = ObjectTag::Player2;
			obj->AddComponent<Collider>()->Init(&m_pObjectLists);
			auto p1 = obj->AddComponent<Human>();
			m_pObjectLists.push_back(obj);
		}
	}
	// enemyを生成
	{
		for (int i = 0; i < 2; i++)
		{
			int num = 0;
			Object* obj = new Object;
			auto enemy = obj->AddComponent<Enemy>();
			obj->AddComponent<Collider>()->Init(&m_pObjectLists);
			obj->AddComponent<Transform>();
			obj->AddComponent<Tag>()->tag = ObjectTag::Enemy;
			for (auto ob : m_pObjectLists)
			{
				enemy->SetPlayerPtr(ob);
				num++;
				if (num > 1) { break; }
			}
			for (int i = 0; i < m_tomatoWallNum; i++)
			{
				enemy->SetTomatoWallPtr(m_pTomatoWall[i]);
			}
			m_pObjectLists.push_back(obj);
		}
	}
	//	cameraを2つ生成
	{
		int num = 0;
		for (auto ob : m_pObjectLists)
		{
			Object* obj = new Object;
			auto proj = obj->AddComponent<Projector>();
			auto tag = obj->AddComponent<Tag>();
			if (num == 0) { tag->tag = ObjectTag::Camera1; }
			if (num == 1) { tag->tag = ObjectTag::Camera2; }
			proj->SetPlayerptr(ob->GetComponent<Transform>());
			m_pObjectLists.push_back(obj);
			num++;
			if (num > 1) { break; }
		}
	}


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
				img->Init(VGet(SCREEN_WIDTH / 2 + x, SCREEN_HEIGHT, 1.0f), VGet(1.0f, 1.0f, 1.0f), 0.0, str.c_str());
				img->IsDraw(false);


				object->AddComponent<TimeUIController>()->Init(i, j);
				m_pObjectLists.push_back(object);
			}
		}
	}
	// 最初のカウントダウン
	{
		Object* object = nullptr;
		for (int i = 0; i < 4; i++)
		{
			std::string str = "data/Number/";
			str += std::to_string(i);
			str += ".png";
			auto object = new Object;
			m_startNumber[i] = object->AddComponent<Image>();
			m_startNumber[i]->Init(VGet(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0f), VGet(1.0f, 1.0f, 1.0f), 0.0, str.c_str());
			m_startNumber[i]->IsDraw(false);
			m_pObjectLists.push_back(object);
		}
	}
	{
		Object* object = new Object;
		m_timeCount = object->AddComponent<TimeCount>();
		m_timeCount->StartCount();
		m_pObjectLists.push_back(object);
	}
	m_graphHandleWhite = LoadGraph("data/white.png");
}

PlayScene::~PlayScene()
{
	DeleteGraph(m_graphHandleWhite);
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
	switch (m_transition)
	{
	case PlayScene::Transition::START:
		UpdateTransitionStart();
		break;
	case PlayScene::Transition::PLAY:
		UpdateTransitionPlay();
		break;
	case PlayScene::Transition::OVER:
		UpdateTransitionOver();
		break;
	case PlayScene::Transition::END:
		UpdateTransitionEnd();
		break;
	default:
		break;
	}
	return m_tagScene;
}

void PlayScene::Draw()
{
#ifdef _DEBUG
	printfDx("PlayScene\n");
#endif // _DEBUG

	switch (m_transition)
	{
	case PlayScene::Transition::START:
		DrawTransitionStart();
		break;
	case PlayScene::Transition::PLAY:
		DrawTransitionPlay();
		break;
	case PlayScene::Transition::OVER:
		DrawTransitionOver();
		break;
	case PlayScene::Transition::END:
		DrawTransitionEnd();
		break;
	default:
		break;
	}
	
}

void PlayScene::UpdateTransitionStart()
{
	if (m_timeCount->CheckCount() > 3.0)
	{
		m_isStartBlendAdd = true;
	}
	if (m_isStartBlendAdd)
	{
		m_startBlendAdd += 1.5;
		if (m_startBlendAdd > 255.0f)
		{
			m_transition = Transition::PLAY;
			m_timeCount->RestCount();
			
		}
	}
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		m_pGameObjects[i]->Update();
	}
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
	//if (Input::IsDown1P(BUTTON_ID_START))
	//{
	//	// トランジションの処理
	//	m_transition = Transition::OVER;
	//	{
	//		Object* obj = new Object;
	//		m_transitionImage[0] = obj->AddComponent<Image>();
	//		m_transitionImage[0]->Init(VGet(SCREEN_WIDTH, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/transition.png");
	//		m_pObjectLists.push_back(obj);
	//	}
	//	{
	//		Object* obj = new Object;
	//		m_transitionImage[1] = obj->AddComponent<Image>();
	//		m_transitionImage[1]->Init(VGet(SCREEN_WIDTH * 1.5f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/black.png");
	//		m_pObjectLists.push_back(obj);
	//	}
	//}

	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		m_transition = Transition::END;
	}
}

void PlayScene::UpdateTransitionPlay()
{
	if (m_isStartBlendAdd)
	{
		m_startBlendAdd -= 3.0;
		if (m_startBlendAdd < 0.0f)
		{
			m_timeCount->StartCount();
			
			m_isStartBlendAdd = false;
		}
	}

	static bool isCount[3] = { false };
	static bool startCount = false;
	if (!startCount && !m_isStartBlendAdd)
	{
		if (m_timeCount->CheckCount() > 0.5 && !isCount[0])
		{
			isCount[0] = true;
			// 音を出す(3)
			m_startNumber[3]->IsDraw(true);
			MyOutputDebugString("3\n");
		}

		if (m_timeCount->CheckCount() > 1.5 && !isCount[1])
		{
			isCount[1] = true;
			// 音を出す(2)
			m_startNumber[3]->IsDraw(false);
			m_startNumber[2]->IsDraw(true);
			MyOutputDebugString("2\n");
		}

		if (m_timeCount->CheckCount() > 2.5 && !isCount[2])
		{
			isCount[2] = true;
			// 音を出す(1)
			m_startNumber[2]->IsDraw(false);
			m_startNumber[1]->IsDraw(true);
			MyOutputDebugString("1\n");
		}

		if (m_timeCount->CheckCount() > 3.5)
		{
			// 音を出す(start)
			
			m_startNumber[1]->IsDraw(false);
			m_startNumber[0]->IsDraw(true);
			MyOutputDebugString("Start\n");

			// 試合のタイマー開始
			for (const auto it : m_pObjectLists)
			{
				auto controller = it->GetComponent<TimeUIController>();
				if (controller != nullptr)
				{
					it->GetComponent<TimeCount>()->StartCount();
				}
			}
		}

		if (m_timeCount->CheckCount() > 4.5)
		{
			m_timeCount->RestCount();
			startCount = true;
			m_startNumber[0]->IsDraw(false);
		}
	}

	static bool moveTimerFlag = false;

	// 時計のUIを画面内に動かす
	if (!moveTimerFlag && startCount)
	{
		// オブジェクトリストをなめる
		for (const auto it : m_pObjectLists)
		{
			auto controller = it->GetComponent<TimeUIController>();
			// TimeUIControllerの時だけ
			if (controller != nullptr)
			{
				auto image = it->GetComponent<Image>();
				// UIを移動
				image->MovePos(VGet(0.0f,-10.0, 0.0f));
				//　目標座標に到達
				if (image->GetPos().y < timerUIY)
				{
					// UIの座標を調整
					for (const auto itr : m_pObjectLists)
					{
						auto controller = itr->GetComponent<TimeUIController>();
						if (controller != nullptr)
						{
							auto image2 = itr->GetComponent<Image>();
							float x = image2->GetPos().x;
							float z = image2->GetPos().z;
							image2->SetPos(VGet(x, timerUIY, z));
						}
					}
					moveTimerFlag = true;
					break;
				}
			}
		}
	}

	// タイムアップ終了処理
	// オブジェクトリストをなめる
	for (const auto it : m_pObjectLists)
	{
		if (it->GetComponent<TimeUIController>() != nullptr)
		{
			if (it->GetComponent<TimeCount>()->CheckCount() > 180.0)
			{
				m_transition = Transition::OVER;
				{
					Object* obj = new Object;
					m_transitionImage[0] = obj->AddComponent<Image>();
					m_transitionImage[0]->Init(VGet(SCREEN_WIDTH, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/transition.png");
					m_pObjectLists.push_back(obj);
				}
				{
					Object* obj = new Object;
					m_transitionImage[1] = obj->AddComponent<Image>();
					m_transitionImage[1]->Init(VGet(SCREEN_WIDTH * 1.5f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/black.png");
					m_pObjectLists.push_back(obj);
				}
			}
			break;
		}
	}

	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		m_pGameObjects[i]->Update();
	}
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
	if (Input::IsDown1P(BUTTON_ID_START))
	{

		// トランジションの処理
		m_transition = Transition::OVER;
		{
			Object* obj = new Object;
			m_transitionImage[0] = obj->AddComponent<Image>();
			m_transitionImage[0]->Init(VGet(SCREEN_WIDTH, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/transition.png");
			m_pObjectLists.push_back(obj);
		}
		{
			Object* obj = new Object;
			m_transitionImage[1] = obj->AddComponent<Image>();
			m_transitionImage[1]->Init(VGet(SCREEN_WIDTH * 1.5f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/black.png");
			m_pObjectLists.push_back(obj);
		}

	}

	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		m_transition = Transition::END;

	}
}

void PlayScene::UpdateTransitionOver()
{
	if (m_transitionImage[0] != nullptr)
	{
		m_transitionImage[0]->MovePos(VGet(-10.0f, 0.0f, 0.0f));
		m_transitionImage[1]->MovePos(VGet(-10.0f, 0.0f, 0.0f));
		if (m_transitionImage[0]->GetPos().x < -10.0f)
		{
			m_tagScene = TAG_SCENE::TAG_OVER;
		}
	}
	else
	{
		m_tagScene = TAG_SCENE::TAG_OVER;
	}
	
}

void PlayScene::UpdateTransitionEnd()
{
	m_tagScene = TAG_SCENE::TAG_END;
}

void PlayScene::DrawTransitionStart()
{
	DrawGrid(1000.0f, 30);
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		if (m_pGameObjects[i]->GetTag() != ObjectTag::Camera2 || m_pGameObjects[i]->GetTag() != ObjectTag::Camera1) { m_pGameObjects[i]->Draw(); }
	}
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
	static float x = 50.0f;
	x += 0.1;
	VECTOR pos = VGet(0.0f,20.0f,x);
	VECTOR target = VGet(0.0f, 0.0f, 0.0f);
	
	SetCameraPositionAndTarget_UpVecY(pos, target);

	SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(m_startBlendAdd));
	DrawGraph(0, 0, m_graphHandleWhite, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void PlayScene::DrawTransitionPlay()
{
	SetDrawArea(0, 0, 640, 960);
	SetCameraScreenCenter(320.0f, 480.0f);
	DrawGrid(1000.0f, 30);
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		if (m_pGameObjects[i]->GetTag() != ObjectTag::Camera2) { m_pGameObjects[i]->Draw(); }
	}
	for (auto obj : m_pObjectLists)
	{
		auto tag = obj->GetComponent<Tag>();
		if (tag == nullptr)
		{
			obj->Draw();
		}
		else
		{
			if (tag->tag != ObjectTag::Camera2) { obj->Draw(); }
		}
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
		auto tag = obj->GetComponent<Tag>();
		if (tag == nullptr) 
		{ 
			obj->Draw();
		}
		else
		{
			if (tag->tag != ObjectTag::Camera1) { obj->Draw(); }
		}
	}
	// 描画可能領域を描画対象画面全体にする
	SetDrawAreaFull();

	SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(m_startBlendAdd));
	DrawGraph(0, 0, m_graphHandleWhite, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void PlayScene::DrawTransitionOver()
{
	SetDrawArea(0, 0, 640, 960);
	SetCameraScreenCenter(320.0f, 480.0f);
	DrawGrid(1000.0f, 30);
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		if (m_pGameObjects[i]->GetTag() != ObjectTag::Camera2) { m_pGameObjects[i]->Draw(); }
	}
	for (auto obj : m_pObjectLists)
	{
		auto tag = obj->GetComponent<Tag>();
		if (tag == nullptr)
		{
			obj->Draw();
		}
		else
		{
			if (tag->tag != ObjectTag::Camera2) { obj->Draw(); }
		}
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
		auto tag = obj->GetComponent<Tag>();
		if (tag == nullptr)
		{
			obj->Draw();
		}
		else
		{
			if (tag->tag != ObjectTag::Camera1) { obj->Draw(); }
		}
	}
	// 描画可能領域を描画対象画面全体にする
	SetDrawAreaFull();
}

void PlayScene::DrawTransitionEnd()
{
	SetDrawArea(0, 0, 640, 960);
	SetCameraScreenCenter(320.0f, 480.0f);
	DrawGrid(1000.0f, 30);
	for (auto i = 0; i < m_pGameObjects.size(); i++)
	{
		if (m_pGameObjects[i]->GetTag() != ObjectTag::Camera2) { m_pGameObjects[i]->Draw(); }
	}
	for (auto obj : m_pObjectLists)
	{
		auto tag = obj->GetComponent<Tag>();
		if (tag == nullptr)
		{
			obj->Draw();
		}
		else
		{
			if (tag->tag != ObjectTag::Camera2) { obj->Draw(); }
		}
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
		auto tag = obj->GetComponent<Tag>();
		if (tag == nullptr)
		{
			obj->Draw();
		}
		else
		{
			if (tag->tag != ObjectTag::Camera1) { obj->Draw(); }
		}
	}
	// 描画可能領域を描画対象画面全体にする
	SetDrawAreaFull();
}
