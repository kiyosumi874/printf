#pragma once
#include "UIBase.h"
#include "Component.h"

class Logo final : public UIBase, public Component
{
public:
	Logo();
	~Logo();

	void Start()override;
	void Update()override;
	void Draw()override;
};