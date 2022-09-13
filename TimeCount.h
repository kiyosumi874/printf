//----------------------------------------
// @file TimeCount.h
// @brief 時間を計測する
// @author shiihara_kiyosumi
// @date 2022_09_01
//----------------------------------------

// 多重インクルード防止
#pragma once
// ヘッダーファイルのインクルード
#include "Component.h"
#include <chrono>

// using宣言
using std::chrono::system_clock;

class TimeCount : public Component
{
public:
	// コンストラクタ
	TimeCount();
	// デストラクタ
	~TimeCount();

	// 更新
	void Update() override;

	// カウントを開始する
	void StartCount();

	// 休憩
	void RestCount();

	bool CheckIsCount();

	// カウントを確認する
	double CheckCount();

private:
	system_clock::time_point m_start; // カウントを開始した時間
	system_clock::time_point m_end; // 今のカウント時間

	bool m_isCount; // カウントをするか否か
};