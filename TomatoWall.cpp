#include "pch.h"
#include "TomatoWall.h"

TomatoWall::TomatoWall(ObjectTag tag, VECTOR position)
	: m_tomatoNumLimit(10)
	, m_allTomatoNum(100)
{
	m_modelPatternHandle[0] = "data/Tomato/FullTomatoWall.mv1";
	m_modelPatternHandle[1] = "data/Tomato/TomatoWall_one.mv1";
	m_modelPatternHandle[2] = "data/Tomato/TomatoWall_two.mv1";
	m_modelPatternHandle[3] = "data/Tomato/TomatoWall_three.mv1";
	m_modelPatternHandle[4] = "data/Tomato/TomatoWall_four.mv1";

	m_tag = tag;
	m_position = position;

	m_modelHandle = MV1LoadModel(m_modelPatternHandle[0].c_str());
	MV1SetPosition(m_modelHandle, m_position);
	MV1SetScale(m_modelHandle, VGet(0.15f, 0.15f, 0.15f));
}

TomatoWall::~TomatoWall()
{
	MV1DeleteModel(m_modelHandle);
}

void TomatoWall::Update()
{
}

void TomatoWall::Draw()
{
	MV1DrawModel(m_modelHandle);
}
