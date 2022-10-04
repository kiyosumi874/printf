#pragma once
#include <DxLib.h>
#include "Component.h"

class Transform : public Component
{
public:
	Transform()
		: position(VGet(0.0f,0.0f,0.0f))
		, rotate(VGet(0.0f,0.0f,0.0f))
		, scale(VGet(0.1f,0.1f,0.1f))
	{
	}
	~Transform(){}

	VECTOR position;
	VECTOR rotate;
	VECTOR scale;
};