#include "pch.h"
#include "ResultGround.h"

ResultGround::ResultGround()
    : m_rotate(0.0f)
{
	// �����Ȃ�
}

ResultGround::~ResultGround()
{
	// �����Ȃ�
}

void ResultGround::Start()
{
	// �������i�g�����f���A�|�W�V�����A��]���A�g�嗦�j
	m_var.Init(AssetManager::UseModel(AssetManager::ModelName::Ground), VGet(0.0f, -1.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f));
	MV1SetScale(m_var.handle, m_var.scale);         // �g�嗦
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);  // ��]��
	MV1SetPosition(m_var.handle, m_var.pos);        // �|�W�V����
}

void ResultGround::Update()
{
	// �����Ȃ�
}

void ResultGround::Draw()
{
	// ���̕`��
	MV1DrawModel(m_var.handle);
}
