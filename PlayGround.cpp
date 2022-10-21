#include "pch.h"
#include "ModelBase.h"
#include "Component.h"
#include "Tag.h"
#include "GroundCollider.h"

PlayGround::PlayGround()
	: m_Pos(VGet(0.0f, -1.0f, 0.0f))
	, m_Scale(VGet(1.0f, 1.0f, 1.0f))
{
	// 初期化（使うモデル、ポジション、回転率、拡大率）
	m_var.Init(AssetManager::UseModel(AssetManager::ModelName::Ground), m_Pos, VGet(0.0f, 0.0f, 0.0f), m_Scale);
	MV1SetScale(m_var.handle, m_var.scale);         // 拡大率
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);  // 回転率
	MV1SetPosition(m_var.handle, m_var.pos);        // ポジション
}

PlayGround::~PlayGround()
{
	// 処理無し
}

void PlayGround::Start()
{
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if (m_pGround == nullptr)
	{
		m_pGround = m_pParent->GetCollider<GroundCollider>();
		m_pGround->Init(m_var.pos, this, m_pTag, CollisionInfo::CollisionType::Ground);
		m_pGround->SetOnCollisionFlag(true);
	}
}

void PlayGround::Update()
{
	m_pGround->UpdatePosition(m_var.pos);
}

void PlayGround::Draw()
{
	// 床の描画
	MV1DrawModel(m_var.handle);
}

void PlayGround::OnCollisionEnter(ColliderComponent* ownColl, ColliderComponent* otherColl)
{
}
