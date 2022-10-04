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
	// ����MAX��0�ł͂Ȃ��A���f�����ŏI�i�K����Ȃ�������
	// �w��̌��ɗ��������f����ς���
	if (m_allTomatoNum != 100 && m_allTomatoNum != 0 && m_modelPatternIndex < 4 &&
		m_allTomatoNum <= m_modelChangeNum[m_modelPatternIndex])
	{
		m_modelPatternIndex++;
	}

	// ���ׂẴg�}�g���Ȃ��Ȃ�����A���Ԃ������畜��
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
	// �S���Ȃ��Ȃ�����`�悵�Ȃ�
	if (m_allTomatoNum != 0)
	{
		m_tomatoWall[m_modelPatternIndex]->Draw();
	}
}
