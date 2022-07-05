#include "GameOverScene.h"
#include "DxLib.h"
#include "Input.h"

GameOverScene::GameOverScene(const MODE& mode)
	: Scene(mode)

{
}

GameOverScene::~GameOverScene()
{
}

TAG_SCENE GameOverScene::Update()
{
	if (Input::IsDown(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_TITLE;
	}
	if (Input::IsDown(BUTTON_ID_BACK))
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
}
