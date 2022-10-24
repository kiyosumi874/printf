#include "pch.h"
#include "TomatoWallManager.h"
#include "Player1.h"
#include "Player2.h"
#include "PlayerCPU.h"
#include "Enemy.h"
#include "Camera.h"
#include "Icon.h"
#include "DebugDraw.h"
#include "Object.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "WallCollider.h"
#include "GroundCollider.h"
#include "WorldCollider.h"
#include "Projector.h"
#include "Transform.h"
#include "Tag.h"
#include "TimeCount.h"
#include "Image.h"
#include "TimeUIController.h"
#include "Score.h"
#include "TomatoUIContoroller.h"
#include "ScoreUIController.h"
#include "DebugColliderObject.h"


// いたっんおいてる定数.いつの日かまとめる
const int timerUIY = SCREEN_HEIGHT / 2 + 200;

PlayScene::PlayScene(const MODE& mode)
	: Scene(mode)
	, m_transition(Transition::START)
	, m_tagScene(TAG_SCENE::TAG_NONE)
	, m_timeCount(nullptr)
	, m_playOnFlag(false)
	, m_isStartBlendAdd(false)
	, m_startBlendAdd(0.0f)
	, m_graphHandleWhite(-1)
{
	// トランジション用の画像初期化
	for (int i = 0; i < 2; i++)
	{
		m_transitionImage[i] = nullptr;
	}
	
	// トマトの山生成
	for (int i = 0; i < m_tomatoWallNum; i++)
	{
		Object* obj = new Object;
		obj->AddComponent<Transform>();
		obj->AddComponent<Tag>()->tag = ObjectTag::TomatoWall;
		auto wall = obj->AddCollider<WallCollider>();
		wall->SetCollider(new Wall(new Box(VGet( 0.0f, 0.0f, 0.0f), VGet(20, 20, 20))));
		auto tomato = obj->AddComponent<TomatoWallManager>();
		tomato->Init(VGet(-300 + 100.0f * i, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.035f, 0.035f, 0.035f));
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);
		m_pTomatoWallObjectLists.push_back(obj);
	}

	{
		/*Object* obj = new Object;
		obj->AddComponent<Transform>();
		obj->AddComponent<Tag>()->tag = ObjectTag::Debug;
		auto sphere = obj->AddCollider<SphereCollider>();
		sphere->SetCollider(new Sphere(VGet(0.0f, 0.0f, 0.0f), 5.0f));
		auto debug = obj->AddComponent<DebugColliderObject>();
		debug->Init(VGet(20, 0.0f, 20), VGet(0.0f, 0.0f, 0.0f), VGet(0.05f, 0.05f, 0.05f));
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);*/
	}

	// iguchi
	// playerを2つ生成
	{
		{
			Object* obj = new Object;
			obj->AddComponent<Transform>();
			auto tag = obj->AddComponent<Tag>();
			tag->tag = ObjectTag::Team1;
			obj->AddComponent<Icon>();
			auto box = obj->AddCollider<BoxCollider>();
			box->SetCollider(new Box(VGet(0.0f, 0.0f, 0.0f), VGet(6, 17, 6)));
			auto sphere = obj->AddCollider<SphereCollider>();
			sphere->SetCollider(new Sphere(VGet(0.0f, 0.0f, 0.0f), 30.0f));
			auto p1 = obj->AddComponent<Player1>();
			p1->Init(VGet(50.0f, 0.0f, -50.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.1f, 0.1f, 0.1f));
			p1->SetTomatoWallPtr(m_pTomatoWallObjectLists);
			m_pColliderLists.push_back(obj);
			m_pObjectLists.push_back(obj);
		}
		{
			Object* obj = new Object;
			obj->AddComponent<Transform>();
			auto tag = obj->AddComponent<Tag>();
			tag->tag = ObjectTag::Team2;
			obj->AddComponent<Icon>();
			auto box = obj->AddCollider<BoxCollider>();
			box->SetCollider(new Box(VGet(0.0f, 0.0f, 0.0f), VGet(6, 17, 6)));
			auto sphere = obj->AddCollider<SphereCollider>();
			sphere->SetCollider(new Sphere(VGet(0.0f, 0.0f, 0.0f), 30.0f));
			auto p2 = obj->AddComponent<Player2>();
			p2->Init(VGet(-50.0f, 0.0f, -50.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.1f, 0.1f, 0.1f));
			p2->SetTomatoWallPtr(m_pTomatoWallObjectLists);
			m_pColliderLists.push_back(obj);
			m_pObjectLists.push_back(obj);
		}
	}

	// playerCPU&enemyを生成
	{
		// PlayerCPU
		Object* obj = new Object;
		obj->AddComponent<Transform>();
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<Icon>();
		auto box = obj->AddCollider<BoxCollider>();
		box->SetCollider(new Box(VGet(0.0f, 0.0f, 0.0f), VGet(6, 17, 6)));
		auto sphere = obj->AddCollider<SphereCollider>();
		sphere->SetCollider(new Sphere(VGet(0.0f, 0.0f, 0.0f), 30.0f));
		auto playerCPU1 = obj->AddComponent<PlayerCPU>();
		playerCPU1->Init(VGet(60.0f, 0.0f, -50.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.1f, 0.1f, 0.1f));
		playerCPU1->SetTomatoWallPtr(m_pTomatoWallObjectLists);
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);

		obj = new Object;
		obj->AddComponent<Transform>();
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<Icon>();
		box = obj->AddCollider<BoxCollider>();
		box->SetCollider(new Box(VGet(0.0f, 0.0f, 0.0f), VGet(6, 17, 6)));
		sphere = obj->AddCollider<SphereCollider>();
		sphere->SetCollider(new Sphere(VGet(0.0f, 0.0f, 0.0f), 30.0f));
		auto playerCPU2 = obj->AddComponent<PlayerCPU>();
		playerCPU2->Init(VGet(-60.0f, 0.0f, -50.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.1f, 0.1f, 0.1f));
		playerCPU2->SetTomatoWallPtr(m_pTomatoWallObjectLists);
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);

		// Enemy
		obj = new Object;
		obj->AddComponent<Transform>();
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<Icon>();
		box = obj->AddCollider<BoxCollider>();
		box->SetCollider(new Box(VGet(0.0f, 0.0f, 0.0f), VGet(6, 17, 6)));
		sphere = obj->AddCollider<SphereCollider>();
		sphere->SetCollider(new Sphere(VGet(0.0f, 0.0f, 0.0f), 30.0f));
		auto enemy1 = obj->AddComponent<Enemy>();
		enemy1->Init(VGet(-10.0f, 0.0f, 50.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.1f, 0.1f, 0.1f));
		enemy1->SetTomatoWallPtr(m_pTomatoWallObjectLists);
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);

		obj = new Object;
		obj->AddComponent<Transform>();
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<Icon>();
		box = obj->AddCollider<BoxCollider>();
		box->SetCollider(new Box(VGet(0.0f, 0.0f, 0.0f), VGet(6, 17, 6)));
		sphere = obj->AddCollider<SphereCollider>();
		sphere->SetCollider(new Sphere(VGet(0.0f, 0.0f, 0.0f), 30.0f));
		auto enemy2 = obj->AddComponent<Enemy>();
		enemy2->Init(VGet(10.0f, 0.0f, 50.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.1f, 0.1f, 0.1f));
		enemy2->SetTomatoWallPtr(m_pTomatoWallObjectLists);
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);

		// 自身と同じチーム以外の人物を狙う対象に
		for (auto ob : m_pObjectLists)
		{
			auto tag = ob->GetComponent<Tag>();
			if (tag->tag == ObjectTag::TomatoWall || tag->tag == ObjectTag::Tomato) { continue; }
			if (tag->tag != ObjectTag::Team1) { playerCPU1->SetAimTargetPtr(ob); }
			if (tag->tag != ObjectTag::Team2) { playerCPU2->SetAimTargetPtr(ob); }
			if (tag->tag != ObjectTag::Team3) { enemy1->SetAimTargetPtr(ob); enemy2->SetAimTargetPtr(ob); }
		}
	}

	// skyDome
	{
		Object* obj = new Object;
		obj->AddComponent<Tag>()->tag = ObjectTag::World;
		auto world = obj->AddCollider<WorldCollider>();
		world->SetCollider(new World(new Sphere(VGet(0.0f, 0.0f, 0.0f), 340.0f)));
		obj->AddComponent<SkyDome>();
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);
	}

	// saito 床を生成
	{
		Object* obj = new Object;
		obj->AddComponent<Tag>()->tag = ObjectTag::Ground;
		auto ground = obj->AddCollider<GroundCollider>();
		ground->SetCollider(new Ground(VGet(0.0f, 0.0f, 0.0f), -3.0f, 5.0f, 500.0f));
		obj->AddComponent<PlayGround>();
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);
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
			for (auto com : ob->m_pComponentLists)
			{
				if (num == 0 && com->m_pParent->GetComponent<Player1>() != nullptr ||
					num == 1 && com->m_pParent->GetComponent<Player2>() != nullptr)
				{
					proj->SetPlayerptr(ob->GetComponent<Transform>());
					m_pObjectLists.push_back(obj);
					num++;
					break;
				}
			}
			if (num > 1) { break; }
		}
	}

	// kiyosumi
	{
		Object* object = nullptr;
		int x = 745;
		float exX = 1.0f;
		float exY = 1.0f;
		{
			object = new Object;
			m_timerBack = object->AddComponent<Image>();
			m_timerBack->Init(VGet(x - 290, 0, 1.0f), VGet(1.3 * exX, 0.6 * exY, 1.0f), 0.0, "data/ink_blot4.png");
			m_timerBack->IsDraw(false);
			m_pObjectLists.push_back(object);
		}
		for (int i = 0; i < 4; i++)
		{
			x -= 50;
			if (i == 2)
			{
				x += 25;
				object = new Object;
				m_timerKoron = object->AddComponent<Image>();
				m_timerKoron->Init(VGet( x, 60, 1.0f), VGet(0.4f * exX, 0.4f * exY, 1.0f), 0.0, "data/DigitalNumber/koron.png");
				m_timerKoron->IsDraw(false);
				m_pObjectLists.push_back(object);

				x -= 25;

			}
			for (int j = 0; j < 10; j++)
			{
				std::string str = "data/DigitalNumber/";
				str += std::to_string(j);
				str += ".png";
				object = new Object;
				object->AddComponent<TimeCount>();
				auto img = object->AddComponent<Image>();
				img->Init(VGet( x, 60, 1.0f), VGet(0.4f *exX, 0.4f *exY, 1.0f), 0.0, str.c_str());
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
			int num = 0;
			if (i == 0)
			{
				str += "Go";
				num = -201 + 67;
			}
			else
			{
				str += std::to_string(i);
			}
			str += ".png";
			auto object = new Object;
			m_startNumber[i] = object->AddComponent<Image>();
			m_startNumber[i]->Init(VGet(SCREEN_WIDTH / 2 - 67 + num, SCREEN_HEIGHT / 2, 1.0f), VGet(1.0f, 1.0f, 1.0f), 0.0, str.c_str());
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
	// トマトUI(残段数)
	{
		Object* object = nullptr;
		for (int i = 0; i < 2; i++)
		{
			object = new Object;
			object->AddComponent<Transform>()->position = VGet((SCREEN_WIDTH + 50.0f) * i - 50.0f, 900.0f, 0.0f);
			m_tomatoUICon[i] = object->AddComponent<TomatoUIController>();
			m_pObjectLists.push_back(object);
		}
		
	}

	// ScoreUI
	{
		Object* object = nullptr;
		for (int i = 0; i < 3; i++)
		{
			object = new Object;
			object->AddComponent<Transform>()->position = VGet(110 * i + 570, 180.0f, 0.0f);
			m_scoreUICon[i] = object->AddComponent<ScoreUIController>();
			m_pObjectLists.push_back(object);
		}
	}
	m_graphHandleWhite = LoadGraph("data/white.png");

}

PlayScene::~PlayScene()
{
	DeleteGraph(m_graphHandleWhite);

	for (auto obj : m_pObjectLists)
	{
		delete obj;
	}
	m_pObjectLists.clear();
	m_pColliderLists.clear();
	m_pTomatoWallObjectLists.clear();
	SetCameraScreenCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
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
	printfDx("T1:%d T2:%d T3:%d\n", Score::GetTeam1Score(), Score::GetTeam2Score(), Score::GetTeam3Score());
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
	for (auto obj : m_pObjectLists)
	{
		if (m_playOnFlag)
		{
			obj->Update();
		}
		else
		{
			auto tag = obj->GetComponent<Tag>();
			if (tag == nullptr)
			{
				obj->Update();
			}
			else
			{
				if (tag->tag == ObjectTag::Camera1 || tag->tag == ObjectTag::Camera2 /*|| tag->tag== ObjectTag::Ground*/) { obj->Update(); }
			}
		}
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
			Sound::Play(Sound::Kind::CountDown);
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
			m_playOnFlag = true;
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
					it->GetComponent<Image>()->SetAlpha(0.0f);
				}
			}
		}

		if (m_timeCount->CheckCount() > 4.5)
		{
			m_timeCount->RestCount();
			startCount = true;
			m_startNumber[0]->IsDraw(false);
			// トマトUI開始
			m_tomatoUICon[0]->CheckIsStart(0);
			m_tomatoUICon[1]->CheckIsStart(1);
			// scoreUI開始
			m_scoreUICon[0]->CheckIsStart(0);
			m_scoreUICon[1]->CheckIsStart(1);
			m_scoreUICon[2]->CheckIsStart(2);

			m_timerKoron->IsDraw(true);
			m_timerBack->IsDraw(true);
		}
	}

	static bool moveTimerFlag = false;

	// 時計のUIを画面内に動かす
	if (!moveTimerFlag && startCount)
	{
		static float alpha = 0.0f;
		m_timerKoron->SetAlpha(alpha);
		m_timerBack->SetAlpha(alpha);
		// オブジェクトリストをなめる
		for (const auto it : m_pObjectLists)
		{
			auto controller = it->GetComponent<TimeUIController>();
			// TimeUIControllerの時だけ
			if (controller != nullptr)
			{
				auto image = it->GetComponent<Image>();
				// UIを移動
				image->SetAlpha(alpha);
				//　目標座標に到達
				if (alpha > 270)
				{
					//// UIの座標を調整
					//for (const auto itr : m_pObjectLists)
					//{
					//	auto controller = itr->GetComponent<TimeUIController>();
					//	if (controller != nullptr)
					//	{
					//		auto image2 = itr->GetComponent<Image>();
					//		float x = image2->GetPos().x;
					//		float z = image2->GetPos().z;
					//		image2->SetPos(VGet(x, timerUIY, z));
					//	}
					//}
					moveTimerFlag = true;
					break;
				}
			}
		}
		alpha += 8.0f;
	}

	// タイムアップ終了処理
	// オブジェクトリストをなめる
	for (const auto it : m_pObjectLists)
	{
		if (it->GetComponent<TimeUIController>() != nullptr)
		{
			if (it->GetComponent<TimeCount>()->CheckCount() > 900.0)
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

	for (auto obj : m_pObjectLists)
	{
		if (m_playOnFlag)
		{
			obj->Update();
		}
		else
		{
			auto tag = obj->GetComponent<Tag>();
			if (tag == nullptr)
			{
				obj->Update();
			}
			else
			{
				if (tag->tag == ObjectTag::Camera1 || tag->tag == ObjectTag::Camera2) { obj->Update(); }
			}
		}
	}

	for (auto obj : m_pColliderLists)
	{
		if (m_playOnFlag)
		{
			obj->OnCollision(m_pColliderLists);
		}
	}

#ifdef _DEBUG
	// debug上でののみ切り替え可能
	bool buttonFlag = false;
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_debugFlag = true;
	}
#endif

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
		if (m_transitionImage[0]->GetPos().x < -400.0f)
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
#ifdef _DEBUG
	DrawGrid(1000.0f, 30);
#endif // _DEBUG
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
	SetDrawArea(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
	SetCameraScreenCenter(480.0f, 540.0f);
	Effekseer_Sync3DSetting();

#ifdef _DEBUG
	DrawGrid(1000.0f, 30);
#endif // _DEBUG
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

	// 大きさ確認用(見た目位置はずれますが実際の位置はずれてません)
	if (m_debugFlag)
	{
		for (auto obj : m_pColliderLists)
		{
			obj->OnDrawCollider();
		}
	}
	DrawEffekseer3D();

	SetDrawArea(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	SetCameraScreenCenter(1440.0f, 540.0f);

	Effekseer_Sync3DSetting();
#ifdef _DEBUG
	//DrawGrid(1000.0f, 30);
#endif // _DEBUG

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

	// 大きさ確認用(見た目位置はずれますが実際の位置はずれてません)
	if (m_debugFlag)
	{
		for (auto obj : m_pColliderLists)
		{
			obj->OnDrawCollider();
		}
	}
	DrawEffekseer3D();


	// 描画可能領域を描画対象画面全体にする
	SetDrawAreaFull();

	SetDrawBlendMode(DX_BLENDMODE_ADD, static_cast<int>(m_startBlendAdd));
	DrawGraph(0, 0, m_graphHandleWhite, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void PlayScene::DrawTransitionOver()
{
	SetDrawArea(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
	SetCameraScreenCenter(480.0f, 540.0f);	
#ifdef _DEBUG
	DrawGrid(1000.0f, 30);
#endif // _DEBUG
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
	SetDrawArea(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	SetCameraScreenCenter(1440.0f, 540.0f);
#ifdef _DEBUG
	printfDx("PlayScene\n");
	
#endif // _DEBUG
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
	SetDrawArea(0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);
	SetCameraScreenCenter(480.0f, 540.0f);
#ifdef _DEBUG
	DrawGrid(1000.0f, 30);
#endif // _DEBUG
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
	SetDrawArea(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	SetCameraScreenCenter(1440.0f, 540.0f);
#ifdef _DEBUG
	DrawGrid(1000.0f, 30);
#endif // _DEBUG
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
