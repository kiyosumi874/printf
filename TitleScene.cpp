#include "pch.h"
#include"SkyDome.h"
#include "Object.h"
#include "Logo.h"
#include "TransitionButton.h"
#include "Gradation.h"

//-------------------------------------------
//- Public ----------------------------------
//-------------------------------------------

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
{
	InitObject(); // オブジェクトの初期化

	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f)); // カメラの位置と向きをセット
}

TitleScene::~TitleScene()
{
	//// 3Dモデルの終了処理
	//for (int i = 0; i < ModelName::TomatoWall2; i++)
	//{
	//	MV1DeleteModel(m_models[i]);
	//}
	//m_models.clear();

	TermObject(); // オブジェクトの解放
}

TAG_SCENE TitleScene::Update()
{
	//UpdateModel(); // 3Dモデルの更新
	UpdateObject(); // オブジェクトの更新
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
#endif // _DEBUG
	//DrawModel(); // 3Dモデルの描画
	DrawObject(); // オブジェクトの描画
}

//-------------------------------------------
//- Private ---------------------------------
//-------------------------------------------

void TitleScene::InitObject()
{
	// Model
	InitGroundModel();
	InitTomatoWallModel();
	// UI
	InitGradationUI();
	InitLogoUI();
	InitTransitionButtonUI();
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
}

void TitleScene::UpdateObject()
{
	RotateSkyDome();
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
}

void TitleScene::DrawObject()
{
	DrawSkyDome();
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
}