#pragma once
#include <cstdint>
#include "Tag.h"

// 3Dƒ‚ƒfƒ‹‚ÌŠî’êƒNƒ‰ƒX
class GameObject
{
public:

	GameObject();
	virtual ~GameObject() = 0;

	virtual void Draw() = 0;

protected:
	VECTOR m_position;
};