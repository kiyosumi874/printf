#include "pch.h"
#include "WorldCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Tag.h"
#include "Object.h"

WorldCollider::WorldCollider()
{
}

WorldCollider::~WorldCollider()
{
	delete m_pWorld;
}

void WorldCollider::SetCollider(const World* world)
{
	m_pWorld = const_cast<World*>(world);
}

void WorldCollider::Init(const VECTOR& pos, Component* owner, Tag* tag, CollisionInfo::CollisionType type)
{
	m_pWorld->m_pSphere->UpdateSphere(pos);
	m_pOwner = owner;
	m_pTag = tag;
	m_pInfo = new CollisionInfo();
	m_pInfo->m_collType = type;
}

bool WorldCollider::CollisionDetection(ColliderComponent* other)
{
	return other->Check(this);
}

bool WorldCollider::Check(BoxCollider* other)
{
	const Box& otherBox = *other->GetWorldBox();
	const World& ownWorld = *GetWorld();

	bool result = Intersect(otherBox, ownWorld, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownWorld, otherBox, m_pInfo->m_fixVec);
	}

	return result;
}

bool WorldCollider::Check(SphereCollider* other)
{
	const Sphere& otherSphere = *other->GetWorldSphere();
	const World& ownWorld = *GetWorld();

	bool result = Intersect(otherSphere, ownWorld, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownWorld, otherSphere, m_pInfo->m_fixVec);
	}

	return result;
}

void WorldCollider::DrawCollider()
{
	DrawSphere3D(m_pWorld->m_pSphere->m_center, m_pWorld->m_pSphere->m_radius, 32, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
}
