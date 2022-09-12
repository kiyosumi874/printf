#include "pch.h"

Ground2::Ground2(ObjectTag tag, VECTOR position)
{
	m_position = position;

	m_modelHandle = MV1LoadModel("Models/Ground/Ground.mv1");
	//m_modelHandle = MV1LoadModel("data/Tomato/Tomato.mv1");

	// 床のサイズを設定
	MV1SetScale(m_modelHandle, VGet(3.0f, 0.4f, 3.0f));
	// 床のポジションを設定
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
