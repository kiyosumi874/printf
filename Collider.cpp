#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "Transform.h"
#include "Human.h"
#include "Tomato.h"
#include "Score.h"

Collider::Collider()
	: flag(false)
	, tag(ObjectTag::End)
	, width(0.0f)
{
}

Collider::~Collider()
{
}

void Collider::Init(std::list<Object*>* objectLists)
{
	copyObjectList = objectLists;
}

void Collider::Update()
{
	CollisionCheck();
}

void Collider::CollisionCheck()
{
	auto self = m_pParent;
	auto selfPosition = self->GetComponent<Transform>()->position;
	auto selfTag = self->GetComponent<Tag>();
	for (auto obj : *copyObjectList)
	{
		if (self == obj) { continue; }	// 自分以外のオブジェクトと判定するため
		Transform* trans = nullptr;
		trans = obj->GetComponent<Transform>();
		if (trans == nullptr) { continue; }	// Transformをコンポーネントしていないものと判定はしない
		auto L_tag = obj->GetComponent<Tag>();
		if (L_tag == nullptr) { continue; } // Tagをコンポーネントしていないものと判定しない
		float distance = 0.0f;
		distance = GetDistance(selfPosition, trans->position);

		// 距離が負の値なら正の値に変える
		if (distance < 0.0f)
		{
			distance = distance * -1.0f;
		}

		if (distance < width)
		{
			if (L_tag->tag == ObjectTag::tomato)	// 当たったのはトマトだった
			{
				auto tomato = obj->GetComponent<Tomato>();
				tag = tomato->m_tag->tag;	// だれが投げたトマト？（当たった人のタグはいらないと思う。当たる人だけコライダーをコンポーネントさせる）
				if (selfTag->tag == tag)	// 自分が投げたトマトだったので無視
				{
					continue;
				}
				// ここにカプセル化したスコア管理クラスを呼べばいいと思う
				if (tag == ObjectTag::Team1) { Score::AddTeam1Score(); }
				if (tag == ObjectTag::Team2) { Score::AddTeam2Score(); }
				if (tag == ObjectTag::Team3) { Score::AddTeam3Score(); }
			}
			flag = true;
			break;
		}
		flag = false;
	}
}

void Collider::Shot(VECTOR position, VECTOR dir, Tag* tag)
{
	Object* obj = new Object;
	obj->AddComponent<Transform>();
	auto L_tag = obj->AddComponent<Tag>();
	L_tag->tag = ObjectTag::tomato;
	obj->AddComponent<Tomato>()->Init(position, dir, tag);
	copyObjectList->push_front(obj);
}

double Collider::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}
