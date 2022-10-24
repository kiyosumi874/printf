//----------------------------------------
// @file ScoreUIController.h
// @brief スコアのUI
// @author shiihara_kiyosumi
// @date 2022_10_24
//----------------------------------------

// 多重インクルード防止
#pragma once

// ヘッダーファイルのインクルード
#include "Component.h"


class BasketController : public Component
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
	bool m_isStart;
	class Image* m_image;
	int m_index; // 1 or 0 (1だったら1P,0だったら2PのUIということ)
};
