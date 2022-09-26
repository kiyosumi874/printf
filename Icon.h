#pragma once
#include "Component.h"

class Tag;

class Icon : public Component
{
public:
	Icon(Tag* tag);   // コンストラクタ
	~Icon();  // デストラクタ

	void Init(VECTOR& position);  // 位置と目標方向
	void Update(VECTOR& position);  // 更新処理
	void Draw();  // 描画処理

	void Animation();

private:
	int m_modelHandle;  // アイコンのモデル

	VECTOR m_correctionVector;  // 位置の補正用

	int m_animIndex;  // 現在のアニメーションを記録
	float m_animTime;  // アニメーションの経過時間
	float m_animTotalTime;  // アニメーションの総時間
	float m_animSpeed;  // 基準のアニメーションスピード

	bool m_noIconFlag;  // アイコンが必要ないオブジェクトが来てバグらないように
};

