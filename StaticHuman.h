#pragma once
#include "Component.h"

class StaticHuman : public Component
{
public:
	StaticHuman();
	~StaticHuman();

	void Start();
	void Update();
	void Draw();

private:
	class Icon* m_icon;  // アイコンクラス

	VECTOR m_dir;			// 向き
	VECTOR m_aimDir;		// 目標向き
	VECTOR m_velocity;		// 速度

	int m_modelHandle;		// モデルハンドル

	enum Anim
	{
		Idle,
		Run,
	};

	int m_animType;  // 現在のアニメーションが何か
	int m_animIndex;  // 現在のアニメーションを記録
	float m_animTime;  // アニメーションの経過時間
	float m_animTotalTime;  // アニメーションの総時間
};
