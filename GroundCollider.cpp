#include "pch.h"
#include "GroundCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

GroundCollider::GroundCollider()
{
}

GroundCollider::~GroundCollider()
{
	delete m_pGround;
}

void GroundCollider::SetCollider(const Ground* ground)
{
	m_pGround = const_cast<Ground*>(ground);
}

void GroundCollider::Init(const VECTOR& pos, Component* owner, Tag* tag, CollisionInfo::CollisionType type)
{
	m_pGround->m_center = pos;
	m_pOwner = owner;
	m_pTag = tag;
	m_pInfo = new CollisionInfo();
	m_pInfo->m_collType = type;
}

bool GroundCollider::CollisionDetection(ColliderComponent* other)
{
	return other->Check(this);
}

bool GroundCollider::Check(BoxCollider* other)
{
	const Box& otherBox = *other->GetWorldBox();
	const Ground& ownGround = *GetWorldGround();

	bool result = Intersect(otherBox, ownGround, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownGround, otherBox, m_pInfo->m_fixVec);
	}

	return result;
}

bool GroundCollider::Check(SphereCollider* other)
{
	const Sphere& otherSphere = *other->GetWorldSphere();
	const Ground& ownGround = *GetWorldGround();

	bool result = Intersect(otherSphere, ownGround, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownGround, otherSphere, m_pInfo->m_fixVec);
	}

	return result;
}

void GroundCollider::DrawCollider()
{
}
