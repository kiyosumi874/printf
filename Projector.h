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
	class Transform* m_pTransform;

	VECTOR m_viewPoint;				// カメラの注視点
	VECTOR m_cameraOffSet;			// プレイヤーからの相対位置
	VECTOR m_targetCameraPosition;	// カメラ目標位置
	VECTOR m_targetViewPoint;		// カメラの注視点目標
};