#pragma once
#include "Component.h"

class Rank : public Component
{
public:
	Rank();
	~Rank();

	void Start();
	void Update();
	void Draw();
};