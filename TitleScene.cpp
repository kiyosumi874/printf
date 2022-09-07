#include "pch.h"

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
{
	/*m_skyDoomHandle = MV1LoadModel("");
	MV1SetScale(m_skyDoomHandle, VGet(1.0f, 1.0f, 1.0f));
	MV1SetPosition(m_skyDoomHandle, VGet(0.0f, 0.0f, 0.0f));*/
}

TitleScene::~TitleScene()
{
	//MV1DeleteModel(m_skyDoomHandle);
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
	//MV1DrawModel(m_skyDoomHandle);
}