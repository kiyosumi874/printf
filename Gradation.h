#pragma once
#include "UIBase.h"
#include "Component.h"

class Gradation final : public UIBase, public Component
{
public:
	Gradation();
	~Gradation();

	void Start()override;
	void Update()override;
	void Draw()override;
};