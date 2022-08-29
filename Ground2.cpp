#include "pch.h"

Ground2::Ground2(ObjectTag tag, VECTOR position)
{
	m_position = position;

	m_modelHandle = MV1LoadModel("Models/Ground/Ground.mv1");
	//m_modelHandle = MV1LoadModel("data/Tomato/Tomato.mv1");

	// ���̃T�C�Y��ݒ�
	MV1SetScale(m_modelHandle, VGet(500.0f, 5.0f, 500.0f));
	// ���̃|�W�V������ݒ�
	MV1SetPosition(m_modelHandle, m_position);
}

Ground2::~Ground2()
{
	MV1DeleteModel(m_modelHandle);
}

void Ground2::Update()
{
}

void Ground2::Draw()
{
	MV1DrawModel(m_modelHandle);
}
