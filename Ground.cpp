#include "pch.h"
#include "Object.h"
#include "Transform.h"

Ground::Ground(/*ObjectTag tag, VECTOR position*/)
{
	//m_position = position;

	// 床のモデル
	m_modelHandle = MV1LoadModel("data/Ground/Ground.mv1");

	// 床のサイズを設定
	MV1SetScale(m_modelHandle, VGet(5.0f, 0.4f, 5.0f));
	//// 床のポジションを設定
	//MV1SetPosition(m_modelHandle, m_position);
}

Ground::~Ground()
{
	MV1DeleteModel(m_modelHandle);
}

void Ground::Start()
{
	auto pos = m_pParent->GetComponent<Transform>();
	MV1SetPosition(m_modelHandle, pos->position);
}

void Ground::Update()
{
	printf("a");
}

void Ground::Draw()
{
	MV1DrawModel(m_modelHandle);
}
