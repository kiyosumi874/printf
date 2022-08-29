#pragma once
#include <DxLib.h>
#include "Component.h"

class Transform : public Component
{
public:
	VECTOR position;
	VECTOR rotate;
	VECTOR scale;
};