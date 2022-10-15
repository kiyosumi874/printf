#include "pch.h"
#include "StaticHuman.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"
#include "Icon.h"

StaticHuman::StaticHuman()
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;

	// アニメーション準備
	m_animType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_var.handle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_var.handle, m_animType);
	m_animTime = 0.0f;
}

StaticHuman::~StaticHuman()
{
	MV1DeleteModel(m_var.handle);
}

void StaticHuman::Start()
{
	auto tag = m_pParent->GetComponent<Tag>();
	// 3Dモデルのポジションを取得
	auto pos = m_pParent->GetComponent<Transform>();

	// Transformの値に位置などの情報を代入
	m_var.pos = pos->position;
	m_var.rotate = pos->rotate;
	m_var.scale = pos->scale;

	// 3Dモデルの読み込み
	if (tag->tag == ObjectTag::Team1) { m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Team1)), m_var.pos, m_var.rotate, m_var.scale); }
	if (tag->tag == ObjectTag::Team2) { m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Team2)), m_var.pos, m_var.rotate, m_var.scale); }
	if (tag->tag == ObjectTag::Team3) { m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Team3)), m_var.pos, m_var.rotate, m_var.scale); }

	// 3Dモデル設定
	MV1SetScale(m_var.handle, VGet(0.1f, 0.1f, 0.1f));
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);

	// アイコンをセット
	auto m_pIcon = m_pParent->AddComponent<Icon>();
	m_pIcon->SetOwnerTag(tag);
	m_pIcon->SetOwnerPosition(pos->position);
	m_pIcon->Init(m_var.pos, VGet(0.0f, 0.0f, 0.0f), VGet(0.7f, 0.7f, 0.7f));
}

void StaticHuman::Update()
{
	// 3Dモデルのポジション設定
	auto pos = m_pParent->GetComponent<Transform>();
	MV1SetPosition(m_var.handle, pos->position);

	// アニメーション処理
	m_animTime += 0.3f;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}
	MV1SetAttachAnimTime(m_var.handle, m_animIndex, m_animTime);
}

void StaticHuman::Draw()
{
	// 3Dモデルの描画
	SetUseLighting(false);
	MV1DrawModel(m_var.handle);
	SetUseLighting(true);
}
