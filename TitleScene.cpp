#include "pch.h"

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
{
	m_skyDomeHandle = MV1LoadModel("data/Skydome_T2/Dome_T201.pmx");
	MV1SetScale(m_skyDomeHandle, VGet(1.0f, 1.0f, 1.0f));
	MV1SetPosition(m_skyDomeHandle, VGet(0.0f, 0.0f, 0.0f));
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f));
}

TitleScene::~TitleScene()
{
	MV1DeleteModel(m_skyDomeHandle);
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
	MV1DrawModel(m_skyDomeHandle);
}