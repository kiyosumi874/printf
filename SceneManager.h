#pragma once
#include "Scene.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void GameLoop();

	void SetNowScene(const TAG_SCENE& tag);
private:
	void ClearScene();
	Scene* m_nowScene;
};
