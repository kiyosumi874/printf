#include "pch.h"
#include "Object.h"
#include "Image.h"
#include "StaticHuman.h"
#include "Transform.h"
#include "Projector.h"

GameOverScene::GameOverScene(const MODE& mode)
	: Scene(mode)
	, m_transition(Transition::START)
	, m_tagScene(TAG_SCENE::TAG_NONE)
{
	// skyDome¶¬
	m_skyDomeHandle = MV1LoadModel("data/Skydome_T2/Dome_T201.pmx");
	{
		Object* ob = new Object;
		auto cameraAimPos = ob->AddComponent<Transform>();
		{
			Object* obj = new Object;
			auto proj = obj->AddComponent<Projector>();
			proj->SetPlayerptr(ob->GetComponent<Transform>());
			m_pObjectLists.push_back(obj);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Object* obj = new Object;
			auto pos = obj->AddComponent<Transform>();
			pos->position = VGet(20.0f * i + j, 0.0f, 0.0f);
			obj->AddComponent<StaticHuman>();
			m_pObjectLists.push_back(obj);
		}
	}
	// ƒgƒ‰ƒ“ƒWƒVƒ‡ƒ“‚Ìˆ—
	{
		Object* obj = new Object;
		m_transitionImage[0] = obj->AddComponent<Image>();
		m_transitionImage[0]->Init(VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/black.png");
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		m_transitionImage[1] = obj->AddComponent<Image>();
		m_transitionImage[1]->Init(VGet(SCREEN_WIDTH, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/transition.png");
		m_pObjectLists.push_back(obj);
	}
}

GameOverScene::~GameOverScene()
{
	MV1DeleteModel(m_skyDomeHandle);
	for (auto obj : m_pObjectLists)
	{
		delete obj;
	}
	m_pObjectLists.clear();
}

TAG_SCENE GameOverScene::Update()
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

	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_TITLE;
	}
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}
	
	return TAG_SCENE::TAG_NONE;
}

void GameOverScene::Draw()
{
#ifdef _DEBUG
	printfDx("GameOverScene\n");
#endif // _DEBUG
	MV1DrawModel(m_skyDomeHandle);
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
}
