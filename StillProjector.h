#pragma once
#include "Component.h"

class StillProjector : public Component
{
public:
	StillProjector();				// コンストラクタ
	~StillProjector();				// デストラクタ

	void Start();
	void Update()override;	// 更新処理.
	void Draw();
private:
	class Transform* m_pPlayerTransform;		// プレイヤーを保持する箱

	VECTOR m_position;				// 座標
	VECTOR m_viewPoint;				// カメラの注視点
	VECTOR m_targetViewPoint;		// カメラの注視点目標
};