#include "pch.h"
#include "WallCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Tag.h"
#include "Object.h"

WallCollider::WallCollider()
{
}

WallCollider::~WallCollider()
{
	delete m_pWall;
}

void WallCollider::SetCollider(const Wall* wall)
{
	m_pWall = const_cast<Wall*>(wall);
}

void WallCollider::Init(const VECTOR& pos, Component* owner, Tag* tag, CollisionInfo::CollisionType type)
{
	m_pWall->m_pWallBox->UpdateMinMax(pos);
	m_pOwner = dynamic_cast<Component*>(owner);
	m_pTag = tag;
	m_pInfo = new CollisionInfo();
	m_pInfo->m_collType = type;
}

bool WallCollider::CollisionDetection(ColliderComponent* other)
{
	return other->Check(this);
}

bool WallCollider::Check(BoxCollider* other)
{
	const Box& otherBox = *other->GetWorldBox();
	const Wall& ownWall = *GetWorldWall();

	bool result = Intersect(ownWall, otherBox, other->GetCollisionInfo());
	if (result)
	{
		calcCollisionFixVec(ownWall, otherBox, m_pInfo->m_fixVec);
		return result;
	}

	return result;
}

bool WallCollider::Check(SphereCollider* other)
{
	const Sphere& otherSphere = *other->GetWorldSphere();
	const Wall& ownWall = *GetWorldWall();

	bool result = Intersect(otherSphere, ownWall, *m_pInfo);
	if (result)
	{
		calcCollisionFixVec(ownWall, otherSphere, m_pInfo->m_fixVec);
	}

	return result;
}

void WallCollider::DrawCollider()
{
	DrawCube3D(m_pWall->m_pWallBox->m_min, m_pWall->m_pWallBox->m_max, GetColor(0, 255, 0), GetColor(0, 255, 0), false);
}
