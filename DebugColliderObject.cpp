#include "pch.h"
#include "Tag.h"
#include "Transform.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "WallCollider.h"
#include "GroundCollider.h"
#include "WorldCollider.h"
#include "DebugColliderObject.h"

void DebugColliderObject::Start()
{
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if (m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	if (m_pColl == nullptr)
	{
		/*m_pColl = m_pParent->GetCollider<BoxCollider>();
		m_pColl->Init(m_pTransform->position, m_pColl->SetOwner(this), m_pTag, CollisionInfo::CollisionType::Box);*/

		m_pColl = m_pParent->GetCollider<SphereCollider>();
		m_pColl->Init(m_pTransform->position, m_pColl->SetOwner(this), m_pTag, CollisionInfo::CollisionType::Sphere);

		/*m_pColl = m_pParent->GetCollider<WallCollider>();
		m_pColl->Init(m_pTransform->position, m_pColl->SetOwner(this), m_pTag, CollisionInfo::CollisionType::Wall);*/

		/*m_pColl = m_pParent->GetCollider<GroundCollider>();
		m_pColl->Init(m_pTransform->position, m_pColl->SetOwner(this), m_pTag, CollisionInfo::CollisionType::Ground);*/

		/*m_pColl = m_pParent->GetCollider<WorldCollider>();
		m_pColl->Init(m_pTransform->position, m_pColl->SetOwner(this), m_pTag, CollisionInfo::CollisionType::World);*/

		m_pColl->SetOnCollisionFlag(true);
	}
}

void DebugColliderObject::Update()
{
	m_var.pos = m_pTransform->position;
	MV1SetPosition(m_var.handle, m_var.pos);
	m_pColl->UpdatePosition(m_var.pos);
}

void DebugColliderObject::Draw()
{
	// 3Dモデルの描画
	SetUseLighting(false);
	MV1DrawModel(m_var.handle);
	SetUseLighting(true);
}

void DebugColliderObject::OnCollisionEnter(ColliderComponent* ownColl, ColliderComponent* otherColl)
{
	// 壁にしたい場合はコメントアウト
	m_pTransform->position = VAdd(m_pTransform->position, ownColl->GetCollisionInfo().m_fixVec);
}

void DebugColliderObject::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
	m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Tomato)), pos, rotate, scale);
	// 3Dモデル設定
	MV1SetScale(m_var.handle, m_var.scale);
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);

	m_pTransform->position = m_var.pos;
	m_pTransform->rotate = m_var.rotate;
	m_pTransform->scale = m_var.scale;
}
