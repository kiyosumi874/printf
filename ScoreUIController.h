//----------------------------------------
// @file ScoreUIController.h
// @brief スコアのUI
// @author shiihara_kiyosumi
// @date 2022_09_10
//----------------------------------------

// 多重インクルード防止
#pragma once

// ヘッダーファイルのインクルード
#include "Component.h"


class ScoreUIController : public Component
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

	void AdjustScore();

	class Image* m_scoreUI[4][10]; // 4桁 0から9
	class Image* m_scoreBack;
	class Transform* m_transform;

	bool m_isStart;
	int m_index; // 0 or 1 or 2 (0だったら1P,1だったら2PのUIということ)
	float m_alpha;
};
