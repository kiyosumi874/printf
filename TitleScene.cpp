#include "pch.h"

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
{
}

TitleScene::~TitleScene()
{
}

TAG_SCENE TitleScene::Update()
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_PLAY;
	}

	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}


	return TAG_SCENE::TAG_NONE;
}

void TitleScene::Draw()
{
#ifdef _DEBUG
	printfDx("TitleScene\n");
#endif // _DEBUG
}