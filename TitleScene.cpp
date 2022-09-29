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
	, m_models()
{
	InitModel(); // 3D���f���̏�����
	InitObject(); // �I�u�W�F�N�g�̏�����

	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 1.0f)); // �J�����̈ʒu�ƌ������Z�b�g
}

TitleScene::~TitleScene()
{
	// 3D���f���̏I������
	for (int i = 0; i < ModelName::TomatoWall2; i++)
	{
		MV1DeleteModel(m_models[i]);
	}
	m_models.clear();

	TermObject(); // �I�u�W�F�N�g�̉��
}

TAG_SCENE TitleScene::Update()
{
	UpdateModel(); // 3D���f���̍X�V
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
	DrawModel(); // 3D���f���̕`��
	DrawObject(); // �I�u�W�F�N�g�̕`��
}

//-------------------------------------------
//- Private ---------------------------------
//-------------------------------------------

void TitleScene::InitObject()
{
	InitGradation();
	InitLogo();
	InitTransitionButton();
}

void TitleScene::InitLogo()
{
	Object* obj = new Object;
	obj->AddComponent<Logo>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::InitTransitionButton()
{
	Object* obj = new Object;
	obj->AddComponent<TransitionButton>();
	m_pObjectLists.push_back(obj);
}

void TitleScene::InitGradation()
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
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
}

void TitleScene::DrawObject()
{
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
}

void TitleScene::InitModel()
{
	m_models.emplace_back(MV1LoadModel("data/Ground/Ground.mv1"));
	MV1SetScale(m_models[ModelName::Ground], VGet(3.0f, 0.4f, 3.0f));
	MV1SetPosition(m_models[ModelName::Ground], VGet(0.0f, -100.0f, 560.0f));

	m_models.emplace_back(MV1LoadModel("data/Tomato/FullTomatoWall.mv1"));
	MV1SetScale(m_models[ModelName::TomatoWall1], VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(m_models[ModelName::TomatoWall1], VGet(0.0f, -96.0f, 630.0f));

	m_models.emplace_back(MV1DuplicateModel(m_models[ModelName::TomatoWall1]));
	MV1SetScale(m_models[ModelName::TomatoWall2], VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(m_models[ModelName::TomatoWall2], VGet(100.0f, -96.0f, 380.0f));

	m_models.emplace_back(MV1DuplicateModel(m_models[ModelName::TomatoWall1]));
	MV1SetScale(m_models[ModelName::TomatoWall3], VGet(0.08f, 0.08f, 0.08f));
	MV1SetPosition(m_models[ModelName::TomatoWall3], VGet(-100.0f, -96.0f, 380.0f));
}

void TitleScene::UpdateModel()
{
	RotateSkyDome();
	static float rot = 0;
	rot += 0.1;
	MV1SetRotationXYZ(m_models[ModelName::Ground], VGet(0.0f, rot * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(m_models[ModelName::TomatoWall1], VGet(0.0f, -rot * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(m_models[ModelName::TomatoWall2], VGet(0.0f, -rot * DX_PI_F / 180.0f, 0.0f));
	MV1SetRotationXYZ(m_models[ModelName::TomatoWall3], VGet(0.0f, -rot * DX_PI_F / 180.0f, 0.0f));
}

void TitleScene::DrawModel()
{
	DrawSkyDome();
	for (auto it : m_models)
	{
		MV1DrawModel(it);
	}
}
