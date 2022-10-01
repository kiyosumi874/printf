#pragma once
#include "ModelBase.h"
#include "Component.h"
#include "DxLib.h"

class TitleGround final : public ModelBase, public Component
{
public:
	TitleGround();
	~TitleGround();

	void Start()override;
	void Update()override;
	void Draw()override;
private:
	float m_rotate;
};