#include "pch.h"
#include "Object.h"
#include "Transform.h"

Ground::Ground(/*ObjectTag tag, VECTOR position*/)
{
	//m_position = position;

	// ���̃��f��
	m_modelHandle = MV1LoadModel("data/Ground/Ground.mv1");

	// ���̃T�C�Y��ݒ�
	MV1SetScale(m_modelHandle, VGet(5.0f, 0.4f, 5.0f));
	//// ���̃|�W�V������ݒ�
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
