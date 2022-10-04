#include "pch.h"
#include "TomatoWallManager.h"
#include "TomatoWall.h"
#include "TomatoWallFull.h"
#include "TomatoWallOne.h"
#include "TomatoWallTwo.h"
#include "TomatoWallThree.h"
#include "TomatoWallFour.h"

TomatoWallManager::TomatoWallManager(ObjectTag tag)
	: m_allTomatoNum(100)
	, m_revivalTime(2000)
	, m_time(0)
	, m_modelPatternIndex(0)
	, m_modelChangeNum{ 99, 50, 30, 10 }
{
	m_tag = tag;
	for (int i = 0; i < m_modelPattern; i++)
	{
		m_tomatoWall[i] = nullptr;
	}
}

TomatoWallManager::~TomatoWallManager()
{
	for (int i = 0; i < m_modelPattern; i++)
	{
		delete m_tomatoWall[i];
	}
}

void TomatoWallManager::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
	m_tomatoWall[0] = new TomatoWallFull(m_tag);
	m_tomatoWall[1] = new TomatoWallOne(m_tag);
	m_tomatoWall[2] = new TomatoWallTwo(m_tag);
	m_tomatoWall[3] = new TomatoWallThree(m_tag);
	m_tomatoWall[4] = new TomatoWallFour(m_tag);

	for (int i = 0; i < m_modelPattern; i++)
	{
		m_tomatoWall[i]->Init(pos, rotate, scale);
	}

	m_position = pos;
	m_rotate = rotate;
	m_scale = scale;
}

void TomatoWallManager::Update()
{
	// 個数がMAXか0ではなく、モデルが最終段階じゃなかったら
	// 指定の個数に来た時モデルを変える
	if (m_allTomatoNum != 100 && m_allTomatoNum != 0 && m_modelPatternIndex < 4 &&
		m_allTomatoNum <= m_modelChangeNum[m_modelPatternIndex])
	{
		m_modelPatternIndex++;
	}

	// すべてのトマトがなくなったら、時間が来たら復元
	if (m_allTomatoNum == 0)
	{
		m_time++;
		if (m_time > m_revivalTime)
		{
			m_allTomatoNum = 100;
			m_modelPatternIndex = 0;
			m_time = 0;
		}
	}
}

void TomatoWallManager::Draw()
{
	// 全部なくなったら描画しない
	if (m_allTomatoNum != 0)
	{
		m_tomatoWall[m_modelPatternIndex]->Draw();
	}
}
