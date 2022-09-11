#include "pch.h"
#include "ResultScene.h"
#include "Object.h"
#include "Image.h"
#include "Projector.h"
#include "Transform.h"

ResultScene::ResultScene(const MODE& mode)
	: m_transition(Transition::START)
	, m_tagScene(TAG_SCENE::TAG_NONE)
{
	// skyDome¶¬
	m_skyDomeHandle = MV1LoadModel("data/Skydome_T2/Dome_T201.pmx");
	// ƒgƒ‰ƒ“ƒWƒVƒ‡ƒ“‚Ìˆ—
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

}

ResultScene::~ResultScene()
{
	MV1DeleteModel(m_skyDomeHandle);
	for (auto obj : m_pObjectLists)
	{
		delete obj;
	}
	m_pObjectLists.clear();
}

TAG_SCENE ResultScene::Update()
{
	switch (m_transition)
	{
	case ResultScene::Transition::START:
		UpdateTransitionStart();
		break;
	case ResultScene::Transition::PLAY:
		UpdateTransitionPlay();
		break;
	case ResultScene::Transition::OVER:
		UpdateTransitionOver();
		break;
	case ResultScene::Transition::END:
		UpdateTransitionEnd();
		break;
	default:
		break;
	}
	return m_tagScene;
}

void ResultScene::Draw()
{
	switch (m_transition)
	{
	case ResultScene::Transition::START:
		DrawTransitionStart();
		break;
	case ResultScene::Transition::PLAY:
		DrawTransitionPlay();
		break;
	case ResultScene::Transition::OVER:
		DrawTransitionOver();
		break;
	case ResultScene::Transition::END:
		DrawTransitionEnd();
		break;
	default:
		break;
	}
}

void ResultScene::UpdateTransitionStart()
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

void ResultScene::UpdateTransitionPlay()
{
}

void ResultScene::UpdateTransitionOver()
{
}

void ResultScene::UpdateTransitionEnd()
{
}

void ResultScene::DrawTransitionStart()
{
	MV1DrawModel(m_skyDomeHandle);
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
}

void ResultScene::DrawTransitionPlay()
{
	MV1DrawModel(m_skyDomeHandle);
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
}

void ResultScene::DrawTransitionOver()
{
	MV1DrawModel(m_skyDomeHandle);
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
}

void ResultScene::DrawTransitionEnd()
{
	MV1DrawModel(m_skyDomeHandle);
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
}
