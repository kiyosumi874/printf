#include "pch.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "WallCollider.h"
#include "GroundCollider.h"
#include "WorldCollider.h"
#include "Tag.h"
#include "Object.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
	delete m_pBox;
}

void BoxCollider::SetCollider(const Box* box)
{
	m_pBox = const_cast<Box*>(box);
}

void BoxCollider::Init(const VECTOR& pos, Component* owner, Tag* tag, CollisionInfo::CollisionType type)
{
	m_pBox->UpdateMinMax(pos);
	m_pOwner = owner;
	m_pTag = tag;
	m_pInfo = new CollisionInfo();
	m_pInfo->m_collType = type;
}

bool BoxCollider::CollisionDetection(ColliderComponent* other)
{
	return other->Check(this);
}

bool BoxCollider::Check(BoxCollider* other)
{
	const Box& otherBox = *other->GetWorldBox();
	const Box& ownBox = *GetWorldBox();

	bool result = Intersect(otherBox, ownBox, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownBox, otherBox, m_pInfo->m_fixVec);
	}

	return result;
}

bool BoxCollider::Check(SphereCollider* other)
{
	const Sphere& otherSphere = *other->GetWorldSphere();
	const Box& ownBox = *GetWorldBox();

	bool result = Intersect(otherSphere, ownBox, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownBox, otherSphere, m_pInfo->m_fixVec);
	}

	return result;
}

bool BoxCollider::Check(WallCollider* other)
{
	const Wall& otherWall = *other->GetWorldWall();
	const Box& ownBox = *GetWorldBox();

	bool result = Intersect(otherWall, ownBox, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownBox, otherWall, m_pInfo->m_fixVec);
		return result;
	}

	return result;
}

bool BoxCollider::Check(GroundCollider* other)
{
	const Ground& otherGround = *other->GetWorldGround();
	const Box& ownBox = *GetWorldBox();

	bool result = Intersect(otherGround, ownBox, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(otherGround, ownBox, m_pInfo->m_fixVec);
		return result;
	}

	return result;
}

bool BoxCollider::Check(WorldCollider* other)
{
	const World& otherWorld = *other->GetWorld();
	const Box& ownBox = *GetWorldBox();

	bool result = Intersect(otherWorld, ownBox, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownBox, otherWorld, m_pInfo->m_fixVec);
	}

	return result;
}

void BoxCollider::DrawCollider()
{
	DrawCube3D(m_pBox->m_min, m_pBox->m_max, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
}
