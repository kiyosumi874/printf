#pragma once
#include "ModelBase.h"
#include "Component.h"

class Icon : public ModelBase, public Component
{
public:
	Icon();   // コンストラクタ
	~Icon();  // デストラクタ

	void Update();  // 更新処理
	void Draw();  // 描画処理

	// 必ず呼ぶこと
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);

	void SetOwnerTag(class Tag* tag) { m_pOwnerTag = tag; }
	void SetOwnerPosition(VECTOR& position);  // 自分を管理しているオブジェクトの位置に自分の位置を補正

	void Animation();


private:
	VECTOR m_correctionVector;  // 位置の補正用
	class Tag* m_pOwnerTag;

	int m_animIndex;  // 現在のアニメーションを記録
	float m_animTime;  // アニメーションの経過時間
	float m_animTotalTime;  // アニメーションの総時間
	float m_animSpeed;  // 基準のアニメーションスピード
};

