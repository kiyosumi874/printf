#include "pch.h"

Ground::Ground(ObjectTag tag, VECTOR position)
{
	m_position = position;

	// ���̃��f��
	m_modelHandle = MV1LoadModel("data/Ground/Ground.mv1");

	// ���̃T�C�Y��ݒ�
	MV1SetScale(m_modelHandle, VGet(3.0f, 0.4f, 3.0f));
	// ���̃|�W�V������ݒ�
	MV1SetPosition(m_modelHandle, m_position);
}

Ground::~Ground()
{
	MV1DeleteModel(m_modelHandle);
}

void Ground::Update()
{
}

void Ground::Draw()
{
	MV1DrawModel(m_modelHandle);
}
