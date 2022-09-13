#include "pch.h"

Ground::Ground(ObjectTag tag, VECTOR position)
{
	m_position = position;

	// 床のモデル
	m_modelHandle = MV1LoadModel("data/Ground/Ground.mv1");

	// 床のサイズを設定
	MV1SetScale(m_modelHandle, VGet(3.0f, 0.4f, 3.0f));
	// 床のポジションを設定
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
