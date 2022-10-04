#pragma once
#include "ModelBase.h"
#include "Component.h"
#include "DxLib.h"

class SkyDome final : public ModelBase, public Component
{
public:
	SkyDome();
	~SkyDome();

	void Start()override;
	void Update()override;
	void Draw()override;
private:
	float m_rotate;
};