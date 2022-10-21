#include "pch.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "WallCollider.h"
#include "GroundCollider.h"
#include "WorldCollider.h"
#include "Tag.h"
#include "Object.h"

SphereCollider::SphereCollider()
{
}

SphereCollider::~SphereCollider()
{
	delete m_pSphere;
}

void SphereCollider::SetCollider(const Sphere* sphere)
{
	m_pSphere = const_cast<Sphere*>(sphere);
}

void SphereCollider::Init(const VECTOR& pos, Component* owner, Tag* tag, CollisionInfo::CollisionType type)
{
	m_pSphere->UpdateSphere(pos);
	m_pOwner = owner;
	m_pTag = tag;
	m_pInfo = new CollisionInfo();
	m_pInfo->m_collType = type;
}

bool SphereCollider::CollisionDetection(ColliderComponent* other)
{
	return other->Check(this);
}

bool SphereCollider::Check(BoxCollider* other)
{
	const Box& otherBox = *other->GetWorldBox();
	const Sphere& ownSphere = *GetWorldSphere();

	bool result = Intersect(otherBox, ownSphere, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownSphere, otherBox, m_pInfo->m_fixVec);
	}

	return result;
}

bool SphereCollider::Check(SphereCollider* other)
{
	const Sphere& otherSphere = *other->GetWorldSphere();
	const Sphere& ownSphere = *GetWorldSphere();

	bool result = Intersect(otherSphere, ownSphere, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownSphere, otherSphere, m_pInfo->m_fixVec);
	}

	return result;
}

bool SphereCollider::Check(WallCollider* other)
{
	const Wall& otherWall = *other->GetWorldWall();
	const Sphere& ownSphere = *GetWorldSphere();

	bool result = Intersect(otherWall, ownSphere, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownSphere, otherWall, m_pInfo->m_fixVec);
	}

	return result;
}

bool SphereCollider::Check(GroundCollider* other)
{
	const Ground& otherGround = *other->GetWorldGround();
	const Sphere& ownSphere = *GetWorldSphere();

	bool result = Intersect(otherGround, ownSphere, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(otherGround, ownSphere, m_pInfo->m_fixVec);
	}

	return result;
}

bool SphereCollider::Check(WorldCollider* other)
{
	const World& otherWorld = *other->GetWorld();
	const Sphere& ownSphere = *GetWorldSphere();

	bool result = Intersect(otherWorld, ownSphere, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownSphere, otherWorld, m_pInfo->m_fixVec);
	}

	return result;
}

void SphereCollider::DrawCollider()
{
	DrawSphere3D(m_pSphere->m_center, m_pSphere->m_radius, 32, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
}
