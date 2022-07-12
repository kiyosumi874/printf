#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();			// コンストラクタ
	~Player()override;	// デストラクタ

	void Update();			// 更新処理
	void Draw()override;	// 描画処理

private:
	int m_playerModelHandle;	// 
};