#include "pch.h"
#include"SkyDome.h"
#include "Object.h"
#include "Logo.h"
#include "TransitionButton.h"
#include "Gradation.h"

//-------------------------------------------
//- Public ----------------------------------
//-------------------------------------------

TitleScene::TitleScene(const MODE& mode)
	: Scene(mode)
{
	InitObject(); // �I�u�W�F�N�g�̏�����

	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f)); // �J�����̈ʒu�ƌ������Z�b�g
}

TitleScene::~TitleScene()
{
	//// 3D���f���̏I������
	//for (int i = 0; i < ModelName::TomatoWall2; i++)
	//{
	//	MV1DeleteModel(m_models[i]);
	//}
	//m_models.clear();

	TermObject(); // �I�u�W�F�N�g�̉��
}

TAG_SCENE TitleScene::Update()
{
	//UpdateModel(); // 3D���f���̍X�V
	UpdateObject(); // �I�u�W�F�N�g�̍X�V
	// ���̃V�[����
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_PLAY;
	}

	// �I��
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	// ���̃��[�v�����̃V�[�����p��
	return TAG_SCENE::TAG_NONE;
}

void TitleScene::Draw()
{
#ifdef _DEBUG
	printfDx("TitleScene\n");
#endif // _DEBUG
	//DrawModel(); // 3D���f���̕`��
	DrawObject(); // �I�u�W�F�N�g�̕`��
}

//-------------------------------------------
//- Private ---------------------------------
//-------------------------------------------

void TitleScene::InitObject()
{
	// Model
	InitGroundModel();
	InitTomatoWallModel();
	// UI
	InitGradationUI();
	InitLogoUI();
	InitTransitionButtonUI();
}

void TitleScene::InitGroundModel()
{
	Object* obj = new Object;
	obj->AddComponent<TitleGround>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::InitTomatoWallModel()
{
	{
		Object* obj = new Object;
		obj->AddComponent<TitleTomatoWall>()->Init(VGet(0.0f, -100.0f, 560.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.08f, 0.08f, 0.08f));
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		obj->AddComponent<TitleTomatoWall>()->Init(VGet(100.0f, -96.0f, 380.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.08f, 0.08f, 0.08f));
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		obj->AddComponent<TitleTomatoWall>()->Init(VGet(-100.0f, -96.0f, 380.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.08f, 0.08f, 0.08f));
		m_pObjectLists.push_back(obj);
	}
}

void TitleScene::InitLogoUI()
{
	Object* obj = new Object;
	obj->AddComponent<Logo>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::InitTransitionButtonUI()
{
	Object* obj = new Object;
	obj->AddComponent<TransitionButton>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::InitGradationUI()
{
	Object* obj = new Object;
	obj->AddComponent<Gradation>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::TermObject()
{
	// �I�u�W�F�N�g���X�g�̉��
	for (auto obj : m_pObjectLists)
	{
		delete obj;
	}
	m_pObjectLists.clear();
}

void TitleScene::UpdateObject()
{
	RotateSkyDome();
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
}

void TitleScene::DrawObject()
{
	DrawSkyDome();
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
}