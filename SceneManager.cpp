#include "pch.h"
#include "SkyDome.h"
#include "Score.h"


SceneManager::SceneManager()
	: m_nowScene(nullptr)
{
	Input::GetInstance();
	Fps::GetInstance();
	Score::GetInstance();
}

SceneManager::~SceneManager()
{
	ClearScene();
	Fps::Terminate();
	Input::Terminate();
	Score::Terminate();
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
		if (Input::IsDown1P(BUTTON_ID_BACK))
		{
			break;
		}
#endif // _DEBUG


		Input::Update();
		Fps::Update();
		UpdateEffekseer3D();

		auto tag = m_nowScene->Update();

		//if (Fps::GetFlag())
		{
			ClearDrawScreen();
			clsDx();
			m_nowScene->Draw();

			//Effekseer_Sync3DSetting();

			//DrawEffekseer3D();


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
	case TAG_SCENE::TAG_RESULT:
		m_nowScene = new ResultScene(MODE::MODE_1P);
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
