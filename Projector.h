#pragma once
#include "Component.h"

class Projector : public Component
{
public:
	Projector();				// コンストラクタ
	~Projector();				// デストラクタ

	void Update()override;	// 更新処理.

	// 初めに一回呼ぶセッター
	void SetPlayerptr(class Transform* ptr);
private:
	class Transform* m_pPlayerTransform;		// プレイヤーを保持する箱

	VECTOR m_position;				// 座標
	VECTOR m_viewPoint;				// カメラの注視点
	VECTOR m_targetViewPoint;		// カメラの注視点目標
};