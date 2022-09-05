#include "pch.h"
#include "Collision.h"
#include "Object.h"
#include "Transform.h"

Collider::Collider()
	: flag(false)
	, tag(ObjectTag::End)
{
}

Collider::~Collider()
{
}

void Collider::Update()
{
	CollisionCheck();
}

void Collider::CollisionCheck()
{
	auto self = m_pParent;
	auto selfPosition = self->GetComponent<Transform>()->position;
	for (auto obj : m_pObjectLists)
	{
		if (self == obj) { continue; }	// 自分以外のオブジェクトと判定するため
		Transform* trans = nullptr;
		trans = obj->GetComponent<Transform>();
		if (trans == nullptr) { continue; }	// Transformをコンポーネントしていないものと判定はしない
		float distance = 0.0f;
		distance = GetDistance(selfPosition, trans->position);

		// 距離が負の値なら正の値に変える
		if (distance < 0.0f)
		{
			distance = distance * -1.0f;
		}
		// 範囲に入っているトマトの壁からトマトを回収
		if (distance < 5.0f)
		{
			flag = true;
			tag = obj->GetComponent<Tag>()->tag;
			break;
		}
		flag = false;
	}
}

double Collider::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}
