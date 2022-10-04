#include "pch.h"

GameClearScene::GameClearScene(const MODE& mode)
	: Scene(mode)
{
}

GameClearScene::~GameClearScene()
{
}

TAG_SCENE GameClearScene::Update()
{
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

void GameClearScene::Draw()
{
#ifdef _DEBUG
	printfDx("GameClearScene\n");
#endif // _DEBUG
}
