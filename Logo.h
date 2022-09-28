#pragma once
#include "UIBase.h"

class Logo : public UIBase
{
public:
	Logo();
	~Logo();

	void Init()override;
	void Update()override;
	void Draw()override;
};