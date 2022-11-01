#include "pch.h"
#include "Tomato.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"
#include "SphereCollider.h"
#include "Score.h"
#include "HitEffect.h"
#include "HitTomatoEffect.h"

// @detail コンストラクタ
// @param position トマトを投げる人の位置
// @param dir 投げる人の向き
Tomato::Tomato()
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);  // 速さはまだ0
	m_startVelocity = VGet(20.0f, 1.0f, 20.0f);

	m_time = 0.0f;
	m_gravity = 9.80665f;  // 平均重力
	m_deg = 30.0f;
	m_rad = m_deg * (DX_PI_F / 180.0f);

	m_dir = VGet(0.0f, 0.0f, 0.0f);
}

// @detail デストラクタ
Tomato::~Tomato()
{
}

void Tomato::Start()
{
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if (m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	if (m_pSphere == nullptr)
	{
		m_pSphere = m_pParent->GetCollider<SphereCollider>();
		m_pSphere->Init(m_pTransform->position, this, m_pTag, CollisionInfo::CollisionType::Sphere);
	}
	if (m_phitEffect == nullptr)
	{
		m_phitEffect = m_pParent->GetComponent<HitEffect>();
		m_phitEffect->Init("data/effect/hit/ToonHit.efkefc", m_pTransform->position, VGet(0.5f, 0.5f, 0.5f), VGet(0.0f, 0.0f, 0.0f));
	}
	if (m_phitTomatoEffect == nullptr)
	{
		m_phitTomatoEffect = m_pParent->GetComponent<HitTomatoEffect>();
		m_phitTomatoEffect->Init("data/effect/hit/tomato.efkefc", m_pTransform->position, VGet(0.5f, 0.5f, 0.5f), VGet(0.0f, 0.0f, 0.0f));
	}
}

// @detail 更新処理
void Tomato::Update()
{
	if (m_isActive)
	{
		Move();
		m_pTransform->position = VAdd(m_pTransform->position, m_velocity);
		m_var.pos = m_pTransform->position;
		MV1SetPosition(m_var.handle, m_var.pos);
		m_pSphere->UpdatePosition(m_var.pos);
	}
}

// @detail 描画処理
void Tomato::Draw()
{
	if (m_isActive)
	{
		MV1DrawModel(m_var.handle);
	}
}

void Tomato::OnCollisionEnter(ColliderComponent* ownColl, ColliderComponent* otherColl)
{
	// 背景や壁だったらだったら
	if (otherColl->GetTag()->tag == ObjectTag::Ground ||
		otherColl->GetTag()->tag == ObjectTag::TomatoWall ||
		otherColl->GetTag()->tag == ObjectTag::World)
	{
		m_isActive = false;
		ownColl->SetOnCollisionFlag(false);
		m_velocity = VGet(0.0f, 0.0f, 0.0f);
		m_time = 0.0f;
		
		return;
	}

	if (otherColl->GetTag()->tag == ObjectTag::Team1 && otherColl->GetCollisionType() == CollisionInfo::CollisionType::Box ||
		otherColl->GetTag()->tag == ObjectTag::Team2 && otherColl->GetCollisionType() == CollisionInfo::CollisionType::Box ||
		otherColl->GetTag()->tag == ObjectTag::Team3 && otherColl->GetCollisionType() == CollisionInfo::CollisionType::Box)
	{
		bool flag = false;
		// 自分を生成したオブジェクトと同じタグ名なら処理を行わない
		if (otherColl->GetTag()->tag == ownColl->GetParentTag()->tag)
		{
			return;
		}
		if (ownColl->GetParentTag()->tag == ObjectTag::Team1) { Score::AddTeam1Score(); }
		if (ownColl->GetParentTag()->tag == ObjectTag::Team2) { Score::AddTeam2Score(); }
		if (ownColl->GetParentTag()->tag == ObjectTag::Team3) { Score::AddTeam3Score(); }

		m_phitTomatoEffect->PlayEffect();
		m_phitTomatoEffect->UpdateState(m_pTransform->position, VGet(7.0f, 7.0f, 7.0f), VGet(0.0f, 0.0f, 0.0f));
		m_phitEffect->PlayEffect();
		m_phitEffect->UpdateState(m_pTransform->position, VGet(1.5f, 1.5f, 1.5f), m_dir);
		m_isActive = false;
		ownColl->SetOnCollisionFlag(false);
		m_velocity = VGet(0.0f, 0.0f, 0.0f);
		m_time = 0.0f;
	}
}

void Tomato::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
	VECTOR tmp = VAdd(pos, VGet(0.0f, 15.0f, 0.0f));
	m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Tomato)), tmp, rotate, scale);

	// 3Dモデル設定
	MV1SetScale(m_var.handle, m_var.scale);
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);

	m_pTransform->position = m_var.pos;
	m_pTransform->rotate = m_var.rotate;
	m_pTransform->scale = m_var.scale;
}

void Tomato::ShotTomato(const VECTOR& pos, const VECTOR& dir, Tag* tag)
{
	VECTOR tmp = VGet(0.0f, pos.y + 15.0f, 0.0f);
	m_pTransform->position = VAdd(pos, tmp);
	m_dir = dir;
	m_pSphere->SetParentTag(tag);
	m_isActive = true;
	m_pSphere->SetOnCollisionFlag(true);

	m_var.pos = m_pTransform->position;
	MV1SetPosition(m_var.handle, m_var.pos);
	m_pSphere->UpdatePosition(m_var.pos);
}

// @detailトマトを投げてからの時間を返す
// @return m_time トマトを投げてからの時間
float Tomato::GetTime()
{
	return m_time;
}

// @detail 投げられた後の処理
void Tomato::Move()
{
	m_time += 0.01f;

	m_velocity.x = m_dir.x * (m_startVelocity.x * cos(m_rad) * m_time);
	m_velocity.y = m_startVelocity.y * sin(m_rad) * m_time - (0.5f * m_gravity * m_time * m_time);
	m_velocity.z = m_dir.z * (m_startVelocity.z * cos(m_rad) * m_time);
}
