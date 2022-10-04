#include "pch.h"
#include "ModelBase.h"
#include "Component.h"

PlayGround::PlayGround()
	: m_Pos(VGet(0.0f, -10.0f, 0.0f))
	, m_Scale(VGet(5.0f, 1.0f, 5.0f))
{
	// �������i�g�����f���A�|�W�V�����A��]���A�g�嗦�j
	m_var.Init(AssetManager::UseModel(AssetManager::ModelName::Ground), m_Pos, VGet(0.0f, 0.0f, 0.0f), m_Scale);
	MV1SetScale(m_var.handle, m_var.scale);         // �g�嗦
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);  // ��]��
	MV1SetPosition(m_var.handle, m_var.pos);        // �|�W�V����
}

PlayGround::~PlayGround()
{
	// ��������
}

void PlayGround::Start()
{
	// ��������
}

void PlayGround::Update()
{
	// ��������
}

void PlayGround::Draw()
{
	// ���̕`��
	MV1DrawModel(m_var.handle);
}
