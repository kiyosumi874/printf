#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: m_position()
	, m_tag()
	, m_modelHandle(-1)
{
}

// ‰Šú‰»
GameObject::GameObject(ObjectTag tag)
	: m_position()
	, m_tag(tag)
	, m_modelHandle(-1)
{
}
// ‰Šú‰»
GameObject::GameObject(ObjectTag tag, VECTOR position)
	: m_position(position)
	, m_tag(tag)
	, m_modelHandle(-1)
{
}

GameObject::~GameObject()
{
}