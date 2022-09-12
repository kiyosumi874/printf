#include "pch.h"
#include "Object.h"
#include "Image.h"
#include "StaticHuman.h"
#include "Transform.h"
#include "StillProjector.h"
#include "Rank.h"
#include "ScoreUIController.h"

GameOverScene::GameOverScene(const MODE& mode)
	: Scene(mode)
	, m_transition(Transition::START)
	, m_tagScene(TAG_SCENE::TAG_NONE)
{
	// skyDomeê∂ê¨
	m_skyDomeHandle = MV1LoadModel("data/Skydome_T2/Dome_T201.pmx");

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Object* obj = new Object;
			auto pos = obj->AddComponent<Transform>();
			pos->position = VGet(-50.0f + (i * 16.0f) + (j * 4), 0.0f, 0.0f);
			if (i == 0) { pos->position = VAdd(pos->position, VGet(0.0f, 0.0f, 5.0f)); }
			if (i == 2) { pos->position = VAdd(pos->position, VGet(0.0f, 0.0f, 10.0f)); }
			obj->AddComponent<StaticHuman>();
			m_pObjectLists.push_back(obj);

			if(i == 1 && j == 0)
			{
				Object* ob = new Object;
				auto proj = ob->AddComponent<StillProjector>();
				proj->SetPlayerptr(pos);
				m_pObjectLists.push_back(ob);
			}
		}
	}
	{
		Object* obj = new Object;
		auto image = obj->AddComponent<Image>();
		image->Init(VGet(450.0f, 400.0f, 0.0f), VGet(0.4f, 0.4f, 0.4f), 0.0f, "data/rank/ranking_1.png");
		obj->AddComponent<Rank>();
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		auto image = obj->AddComponent<Image>();
		image->Init(VGet(100.0f, 400.0f, 0.0f), VGet(0.38f, 0.38f, 0.38f), 0.0f, "data/rank/ranking_2.png");
		obj->AddComponent<Rank>();
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		auto image = obj->AddComponent<Image>();
		image->Init(VGet(800.0f, 400.0f, 0.0f), VGet(0.36f, 0.36f, 0.36f), 0.0f, "data/rank/ranking_3.png");
		obj->AddComponent<Rank>();
		m_pObjectLists.push_back(obj);
	}
	// ScoreUI
	{
		Object* object = nullptr;
		for (int i = 0; i < 3; i++)
		{
			object = new Object;
			object->AddComponent<Transform>()->position = VGet(450 * i, 700.0f, 0.0f);
			object->AddComponent<ScoreUIController>();
			m_pObjectLists.push_back(object);
		}
	}
	// ÉgÉâÉìÉWÉVÉáÉìÇÃèàóù
	{
		Object* obj = new Object;
		m_transitionImage[0] = obj->AddComponent<Image>();
		m_transitionImage[0]->Init(VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/black.png");
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		m_transitionImage[1] = obj->AddComponent<Image>();
		m_transitionImage[1]->Init(VGet(SCREEN_WIDTH / 2, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/transition.png");
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
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_TITLE;
	}
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}
	switch (m_transition)
	{
	case GameOverScene::Transition::START:
		UpdateTransitionStart();
		break;
	case GameOverScene::Transition::PLAY:
		UpdateTransitionPlay();
		break;
	case GameOverScene::Transition::OVER:
		break;
	case GameOverScene::Transition::END:
		UpdateTransitionEnd();
		break;
	default:
		break;
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

void GameOverScene::UpdateTransitionStart()
{
	if (m_transitionImage[0] != nullptr)
	{
		m_transitionImage[0]->MovePos(VGet(-10.0f, 0.0f, 0.0f));
		m_transitionImage[1]->MovePos(VGet(-10.0f, 0.0f, 0.0f));
		if (m_transitionImage[1]->GetPos().x < -2540.0f)
		{
			m_transition = Transition::PLAY;
		}
	}
	else
	{
		m_transition = Transition::PLAY;
	}
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
}

void GameOverScene::UpdateTransitionPlay()
{
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
}

void GameOverScene::UpdateTransitionEnd()
{
}
