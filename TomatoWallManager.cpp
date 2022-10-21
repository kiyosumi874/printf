#include "pch.h"
#include "TomatoWallManager.h"
#include "Tag.h"
#include "Transform.h"
#include "TomatoWall.h"
#include "TomatoWallFull.h"
#include "TomatoWallOne.h"
#include "TomatoWallTwo.h"
#include "TomatoWallThree.h"
#include "TomatoWallFour.h"
#include "WallCollider.h"

TomatoWallManager::TomatoWallManager()
	: m_allTomatoNum(100)
	, m_revivalTime(2000)
	, m_time(0)
	, m_modelPatternIndex(0)
	, m_modelChangeNum{ 99, 50, 30, 10 }
{
	for (int i = 0; i < m_modelPattern; i++)
	{
		m_tomatoWall[i] = nullptr;
	}
}

TomatoWallManager::~TomatoWallManager()
{
}

void TomatoWallManager::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if (m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	if (m_pWall == nullptr)
	{
		m_pWall = m_pParent->GetCollider<WallCollider>();
		m_pWall->Init(pos, this, m_pTag, CollisionInfo::CollisionType::Wall);
		m_pWall->SetOnCollisionFlag(true);
	}

	m_tomatoWall[0] = m_pParent->AddComponent<TomatoWallFull>();
	m_tomatoWall[1] = m_pParent->AddComponent<TomatoWallOne>();
	m_tomatoWall[2] = m_pParent->AddComponent<TomatoWallTwo>();
	m_tomatoWall[3] = m_pParent->AddComponent<TomatoWallThree>();
	m_tomatoWall[4] = m_pParent->AddComponent<TomatoWallFour>();

	for (int i = 0; i < m_modelPattern; i++)
	{
		m_tomatoWall[i]->Init(pos, rotate, scale);
	}

	m_var.pos = pos;
	m_var.rotate = rotate;
	m_var.scale = scale;
	m_pTransform->position = m_var.pos;
	m_pWall->UpdatePosition(VGet(pos.x, pos.y + m_pWall->GetWorldWall()->m_pWallBox->m_scale.y / 2.0f, pos.z));
}

void TomatoWallManager::Update()
{
	m_var.pos = m_pTransform->position;

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
		m_pWall->SetOnCollisionFlag(false);
		if (m_time > m_revivalTime)
		{
			m_allTomatoNum = 100;
			m_modelPatternIndex = 0;
			m_time = 0;
			m_pWall->SetOnCollisionFlag(true);
		}
	}

	m_pWall->UpdatePosition(VGet(m_var.pos.x, m_var.pos.y + m_pWall->GetWorldWall()->m_pWallBox->m_scale.y / 2.0f, m_var.pos.z));
}

void TomatoWallManager::Draw()
{
	// 全部なくなったら描画しない
	if (m_allTomatoNum != 0)
	{
		m_tomatoWall[m_modelPatternIndex]->Draw();
	}
}

void TomatoWallManager::Start()
{
}

void TomatoWallManager::OnCollisionEnter(ColliderComponent* ownColl, ColliderComponent* otherColl)
{
	if (otherColl->GetTag()->tag == ObjectTag::Ground)
	{
		m_pTransform->position = VAdd(m_pTransform->position, ownColl->GetCollisionInfo().m_fixVec);
	}
}
