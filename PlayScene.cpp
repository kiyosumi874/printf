#include "PlayScene.h"
#include "DxLib.h"
#include "Input.h"

PlayScene::PlayScene(const MODE& mode)
	: Scene(mode)
{
}

PlayScene::~PlayScene()
{
}

TAG_SCENE PlayScene::Update()
{
	if (Input::IsDown(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_OVER;
	}

	if (Input::IsDown(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	return TAG_SCENE::TAG_NONE;
}

void PlayScene::Draw()
{
#ifdef _DEBUG
	printfDx("PlayScene\n");
#endif // _DEBUG
}