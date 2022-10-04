//----------------------------------------
// @file TomatoUIController.h
// @brief 残段数のUI
// @author shiihara_kiyosumi
// @date 2022_09_08
//----------------------------------------

// 多重インクルード防止
#pragma once

// ヘッダーファイルのインクルード
#include "Component.h"

// 定数
const int cTomatoMax = 10;

class TomatoUIController : public Component
{
public:

	// 最初に一回通るやつ
	void Start()override;

	// 更新
	void Update()override;

	// 描画
	void Draw()override;

	// UIを画面に移動させだす
	void CheckIsStart(const int index)
	{
		m_isStart = true;
		m_index = index;
	}

private:

	void AdjustTomato(const int index);

	class Image* m_tomatoUI[cTomatoMax];
	class Transform* m_transform;

	bool m_isStart;
	int m_index; // 1 or 0 (1だったら1P,0だったら2PのUIということ)
};
