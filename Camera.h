#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera(ObjectTag tag, VECTOR position);				// コンストラクタ
	~Camera();				// デストラクタ

	void Update()override;	// 更新処理.
	void Draw()override;	// 描画処理.

	// 初めに一回呼ぶセッター
	void SetPlayerptr(class Player1* ptr);
private:
	class Player1* m_pPlayer;		// プレイヤーを保持する箱

	VECTOR m_viewPoint;				// カメラの注視点
	VECTOR m_cameraOffSet;			// プレイヤーからの相対位置
	VECTOR m_targetCameraPosition;	// カメラ目標位置
	VECTOR m_targetViewPoint;		// カメラの注視点目標
};