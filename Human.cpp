#include "pch.h"
#include "Human.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"
#include "Tomato.h"
#include "TomatoWallManager.h"
#include "Score.h"
#include "Icon.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

Human::Human()
{
	m_pTransform = nullptr;
	m_pTag = nullptr;
	m_pIcon = nullptr;
}

void Human::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
	// 3Dモデルの読み込み
	if (m_pTag->tag == ObjectTag::Team1) { m_var.Init(MV1DuplicateModel(AssetManager::UseModel(m_modelName)), pos, rotate, scale); }
	if (m_pTag->tag == ObjectTag::Team2) { m_var.Init(MV1DuplicateModel(AssetManager::UseModel(m_modelName)), pos, rotate, scale); }
	if (m_pTag->tag == ObjectTag::Team3) { m_var.Init(MV1DuplicateModel(AssetManager::UseModel(m_modelName)), pos, rotate, scale); }

	// Transformの値に位置などの情報を代入
	m_pTransform->position = m_var.pos;
	m_pTransform->rotate = m_var.rotate;
	m_pTransform->scale = m_var.scale;

	// 3Dモデル設定
	MV1SetScale(m_var.handle, m_var.scale);
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);
	MV1SetPosition(m_var.handle, m_var.pos);

	m_animType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_var.handle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_var.handle, m_animType);

	// アイコンをセット
	m_pIcon = m_pParent->GetComponent<Icon>();
	m_pIcon->SetOwnerTag(m_pTag);
	m_pIcon->SetOwnerPosition(m_pTransform->position);
	m_pIcon->Init(m_var.pos, VGet(0.0f, 0.0f, 0.0f), VGet(0.7f, 0.7f, 0.7f));

	// 最初に3つトマトを作成しておく(メモリ容量のため3つに限定)
	for (int i = 0; i < 3; i++)
	{
		Object* obj = new Object;
		obj->AddComponent<Transform>();
		auto tag = obj->AddComponent<Tag>();
		switch (m_pTag->tag)
		{
		case ObjectTag::Team1:
			tag->tag = ObjectTag::Team1Tomato;
			break;
		case ObjectTag::Team2:
			tag->tag = ObjectTag::Team2Tomato;
			break;
		case ObjectTag::Team3:
			tag->tag = ObjectTag::Team3Tomato;
			break;
		default:
			break;
		}
		auto sphere = obj->AddCollider<SphereCollider>();
		sphere->SetCollider(new Sphere(VGet(0.0f, 0.0f, 0.0f), 1.0f));
		Tomato* t = obj->AddComponent<Tomato>();
		t->Init(VGet(0.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.02f, 0.02f, 0.02f));
		m_pTomato.push_back(t);
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);
	}
}

void Human::SetTomatoWallPtr(std::list<class Object*> tomatoWall)
{
	for (auto obj : tomatoWall)
	{
		m_pTomatoWall.push_back(obj->GetComponent<TomatoWallManager>());
	}
}

double Human::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}

float Human::GetSize(float v1, float v2)
{
	float value = v1 - v2;
	if (value < 0)
	{
		value = value * -1.0f;
	}
	return value;
}
