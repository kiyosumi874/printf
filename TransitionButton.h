#pragma once
#include "UIBase.h"
#include "Component.h"

class TransitionButton final : public UIBase, public Component
{
public:
	TransitionButton();
	~TransitionButton();

	void Start()override;
	void Update()override;
	void Draw()override;
private:
	bool m_alphaFlag;
};