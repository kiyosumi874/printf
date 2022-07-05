#include "SceneManager.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "GameClearScene.h"
#include "GameOverScene.h"
#include "DxLib.h"
#include "Input.h"
#include "Fps.h"


SceneManager::SceneManager()
	: m_nowScene(nullptr)
{
	Input::GetInstance();
	Fps::GetInstance();
}

SceneManager::~SceneManager()
{
	ClearScene();
	Fps::Terminate();
	Input::Terminate();
}

void SceneManager::GameLoop()
{
	while (1)
	{
		if (ProcessMessage() == -1)
		{
			break;
		}
#ifdef _DEBUG
		if (Input::IsDown(BUTTON_ID_BACK))
		{
			break;
		}
#endif // _DEBUG


		Input::Update();
		Fps::Update();
		auto tag = m_nowScene->Update();

		//if (Fps::GetFlag())
		{
			ClearDrawScreen();
			clsDx();
			m_nowScene->Draw();
#ifdef _DEBUG
			Fps::Draw();
#endif // _DEBUG
			ScreenFlip();
		}

		if (tag == TAG_SCENE::TAG_NONE)
		{
			continue;
		}

		ClearScene();
		if (tag == TAG_SCENE::TAG_END)
		{
			break;
		}
		SetNowScene(tag);
	}
	
}

void SceneManager::SetNowScene(const TAG_SCENE& tag)
{
	switch (tag)
	{
	case TAG_SCENE::TAG_TITLE:
		m_nowScene = new TitleScene(MODE::MODE_1P);
		break;
	case TAG_SCENE::TAG_PLAY:
		m_nowScene = new PlayScene(MODE::MODE_1P);
		break;
	case TAG_SCENE::TAG_CLEAR:
		m_nowScene = new GameClearScene(MODE::MODE_1P);
		break;
	case TAG_SCENE::TAG_OVER:
		m_nowScene = new GameOverScene(MODE::MODE_1P);
		break;
	case TAG_SCENE::TAG_NONE:
		break;
	default:
		break;
	}
}

void SceneManager::ClearScene()
{
	if (m_nowScene != nullptr)
	{
		delete m_nowScene;
		m_nowScene = nullptr;
	}
	
}
