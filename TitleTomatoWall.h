#pragma once
#include "ModelBase.h"
#include "Component.h"
#include "DxLib.h"

class TitleTomatoWall final : public ModelBase, public Component
{
public:
	TitleTomatoWall();
	~TitleTomatoWall();

	void Start()override;
	void Update()override;
	void Draw()override;

	// 必ず呼ぶこと
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
private:
	float m_rotate;
};