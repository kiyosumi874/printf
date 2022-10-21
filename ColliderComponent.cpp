#include "pch.h"
#include "ColliderComponent.h"
#include "Tag.h"
#include "ObjectTag.h"
#include "Object.h"

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
