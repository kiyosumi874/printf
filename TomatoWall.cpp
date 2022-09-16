#include "pch.h"
#include "TomatoWall.h"

TomatoWall::TomatoWall(ObjectTag tag, VECTOR position)
	: m_allTomatoNum(100)
	, m_revivalTime(2000)
	, m_time(0)
	, m_modelPatternIndex(0)
	, m_modelChangeNum{99, 50, 30, 10}
{
	m_modelPatternHandle[0] = "data/Tomato/FullTomatoWall.mv1";
	m_modelPatternHandle[1] = "data/Tomato/TomatoWall_one.mv1";
	m_modelPatternHandle[2] = "data/Tomato/TomatoWall_two.mv1";
	m_modelPatternHandle[3] = "data/Tomato/TomatoWall_three.mv1";
	m_modelPatternHandle[4] = "data/Tomato/TomatoWall_four.mv1";

	m_tag = tag;
	m_position = position;
	m_size = VGet(0.035f, 0.035f, 0.035f);

	m_modelHandle = MV1LoadModel(m_modelPatternHandle[0].c_str());
	MV1SetPosition(m_modelHandle, m_position);
	MV1SetScale(m_modelHandle, m_size);
}

TomatoWall::~TomatoWall()
{
	MV1DeleteModel(m_modelHandle);
}

void TomatoWall::Update()
{
	// 個数がMAXか0ではなく、モデルが最終段階じゃなかったら
	// 指定の個数に来た時モデルを変える
	if (m_allTomatoNum != 100 && m_allTomatoNum != 0 && m_modelPatternIndex < 4 &&
		m_allTomatoNum <= m_modelChangeNum[m_modelPatternIndex])
	{
		m_modelPatternIndex++;
		MV1DeleteModel(m_modelHandle);
		m_modelHandle = MV1LoadModel(m_modelPatternHandle[m_modelPatternIndex].c_str());
		MV1SetPosition(m_modelHandle, m_position);
		MV1SetScale(m_modelHandle, m_size);
	}

	// すべてのトマトがなくなったら、時間が来たら復元
	if (m_allTomatoNum == 0)
	{
		m_time++;
		if (m_time > m_revivalTime)
		{
			m_allTomatoNum = 100;
			m_modelPatternIndex = 0;
			m_modelHandle = MV1LoadModel(m_modelPatternHandle[m_modelPatternIndex].c_str());
			MV1SetPosition(m_modelHandle, m_position);
			MV1SetScale(m_modelHandle, m_size);
			m_time = 0;
		}
	}
}

void TomatoWall::Draw()
{
	// 全部なくなったら描画しない
	if (m_allTomatoNum != 0)
	{
		MV1DrawModel(m_modelHandle);
	}
	//DrawFormatString(800, 0, GetColor(255, 255, 255), "TomatoWallNum:%d", m_allTomatoNum);
}
