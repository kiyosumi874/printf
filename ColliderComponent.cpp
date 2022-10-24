#include "pch.h"
#include "ColliderComponent.h"
#include "ObjectTag.h"

void ColliderComponent::SetOnCollisionTag(Tag* tag)
{
	Tag t = *tag;
	m_onCollisionTag.push_back(t);
}

ObjectTag* ColliderComponent::GetOnCollisionTag(ObjectTag tag)
{
	for (auto onTag : m_onCollisionTag)
	{
		if (onTag.tag == tag)
		{
			return &onTag.tag;
		}
	}
	return nullptr;
}

void ColliderComponent::CleanCollisionTag()
{
	m_onCollisionTag.clear();
}

void ColliderComponent::ClearInfo()
{
	m_pInfo->m_collisionPoint = VGet(0.0f, 0.0f, 0.0f);
	m_pInfo->m_collType = CollisionInfo::CollisionType::Begin;
	m_pInfo->m_fixVec = VGet(0.0f, 0.0f, 0.0f);
	m_pInfo->m_hitNormal = VGet(0.0f, 0.0f, 0.0f);
}

bool ColliderComponent::CollisionDetection(ColliderComponent* other)
{
	return false;
}
