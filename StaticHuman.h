#pragma once
#include "Component.h"

class StaticHuman : public ModelBase,public Component
{
public:
	StaticHuman();
	~StaticHuman() override;

	void Start() override;
	void Update() override;
	void Draw() override;

private:
	class Icon* m_icon;  // アイコンクラス

	AssetManager::ModelName m_modelName;

	VECTOR m_dir;			// 向き
	VECTOR m_aimDir;		// 目標向き
	VECTOR m_velocity;		// 速度

	enum Anim
	{
		None = -1,  // 何もしない
		Idle,  // 止まる
		Run,   // 走る
		Throw,  // 投げる
		Pick,  // 拾う
	};

	int m_animType;  // 現在のアニメーションが何か
	int m_animIndex;  // 現在のアニメーションを記録
	float m_animTime;  // アニメーションの経過時間
	float m_animTotalTime;  // アニメーションの総時間
};
