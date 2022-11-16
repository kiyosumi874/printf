#include "pch.h"
#include "Object.h"
#include "Logo.h"
#include "TransitionButton.h"
#include "Gradation.h"
#include "TitleConfetti.h"

//-------------------------------------------
//- Public ----------------------------------
//-------------------------------------------

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
{
	InitObject(); // オブジェクトの初期化
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f)); // カメラの位置と向きをセット
	m_handle = LoadGraph("data/Icon/ReadyPlayerMe.png");
}

TitleScene::~TitleScene()
{
	TermObject(); // オブジェクトの解放
}

TAG_SCENE TitleScene::Update()
{
	UpdateObject(); // オブジェクトの更新

#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_Z))
	{
		stopWatch->StartCount();
	}
	if (CheckHitKey(KEY_INPUT_X))
	{
		stopWatch->StopCount();
	}
	if (CheckHitKey(KEY_INPUT_C))
	{
		stopWatch->ResetCount();
	}
#endif // _DEBUG

	// 次のシーンへ
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_PLAY;
	}

	// 終了
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	// 次のループもこのシーンを継続
	return TAG_SCENE::TAG_NONE;
}

void TitleScene::Draw()
{
#ifdef _DEBUG
	printfDx("TitleScene\n");
	printfDx("StopWatch\n");
	printfDx("Start : Z\n");
	printfDx("Stop  : X\n");
	printfDx("Reset : C\n");
	printfDx("time  : %f\n", stopWatch->GetSeconds());
#endif // _DEBUG
	DrawObject(); // オブジェクトの描画
}

//-------------------------------------------
//- Private ---------------------------------
//-------------------------------------------

void TitleScene::InitObject()
{
	// Model
	InitSkyDomeModel();
	InitGroundModel();
	InitTomatoWallModel();
	// UI
	InitGradationUI();
	InitLogoUI();
	InitTransitionButtonUI();

	Object* obj = new Object;
	obj->AddComponent<TitleConfetti>();
	m_pObjectLists.push_back(obj);

#ifdef _DEBUG
	{
		Object* obj2 = new Object;
		stopWatch = obj->AddComponent<StopWatch>();
		m_pObjectLists.push_back(obj2);
	}
#endif // _DEBUG

}

void TitleScene::InitSkyDomeModel()
{
	Object* obj = new Object;
	obj->AddComponent<SkyDome>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::InitGroundModel()
{
	Object* obj = new Object;
	obj->AddComponent<TitleGround>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::InitTomatoWallModel()
{
	{
		Object* obj = new Object;
		obj->AddComponent<TitleTomatoWall>()->Init(VGet(0.0f, -100.0f, 560.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.08f, 0.08f, 0.08f));
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		obj->AddComponent<TitleTomatoWall>()->Init(VGet(100.0f, -96.0f, 380.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.08f, 0.08f, 0.08f));
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		obj->AddComponent<TitleTomatoWall>()->Init(VGet(-100.0f, -96.0f, 380.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.08f, 0.08f, 0.08f));
		m_pObjectLists.push_back(obj);
	}
}

void TitleScene::InitLogoUI()
{
	Object* obj = new Object;
	obj->AddComponent<Logo>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::InitTransitionButtonUI()
{
	Object* obj = new Object;
	obj->AddComponent<TransitionButton>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::InitGradationUI()
{
	Object* obj = new Object;
	obj->AddComponent<Gradation>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::TermObject()
{
	// オブジェクトリストの解放
	for (auto obj : m_pObjectLists)
	{
		delete obj;
	}
	m_pObjectLists.clear();
	DeleteGraph(m_handle);
}

void TitleScene::UpdateObject()
{
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
}

void TitleScene::DrawObject()
{
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}

	DrawGraph(50, SCREEN_HEIGHT - 100, m_handle, TRUE);
}