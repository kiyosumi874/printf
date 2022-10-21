#include "pch.h"
#include "Tag.h"
#include "WorldCollider.h"

SkyDome::SkyDome()
	: m_rotate(0.0f)
{
	// 処理無し
}

SkyDome::~SkyDome()
{
	// 処理無し
}

void SkyDome::Start()
{
	m_var.Init(AssetManager::UseModel(AssetManager::ModelName::SkyDome), VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f));
	MV1SetScale(m_var.handle, m_var.scale);
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);

	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if (m_pWorld == nullptr)
	{
		m_pWorld = m_pParent->GetCollider<WorldCollider>();

		if (m_pTag != nullptr)
		{
			m_pWorld->Init(m_var.pos, this, m_pTag, CollisionInfo::CollisionType::World);
			m_pWorld->SetOnCollisionFlag(true);
		}
		else
		{
			if (m_pWorld != nullptr)
			{
				m_pWorld->Init(m_var.pos, this, nullptr, CollisionInfo::CollisionType::World);
			}
		}
	}
}

void SkyDome::Update()
{
	m_rotate += 0.0025f;
	m_var.rotate.y = m_rotate * DX_PI_F / 180.0f;
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
}

void SkyDome::Draw()
{
	MV1DrawModel(m_var.handle);
}
