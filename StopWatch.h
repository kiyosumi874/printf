//----------------------------------------
// @file StopWatch.h
// @brief 時間を計測する
// @author shiihara_kiyosumi
// @date 2022_09_11_04
//----------------------------------------

// 多重インクルード防止
#pragma once
// ヘッダーファイルのインクルード
#include "Component.h"
#include <time.h>

class StopWatch : public Component
{
public:
	// 初期化
	void Start() override;

	// 更新
	void Update() override;

	// カウントを開始する
	void StartCount();

	// 停止
	void StopCount();

	// リセット
	void ResetCount();

	// カウントを確認する
	double GetSeconds();

private:
	clock_t m_begin; // カウントを開始した時間
	clock_t m_elapsed; // 経過時間
	clock_t m_stopTime; // 止まった時間
	clock_t m_end; // 今の計測した時間

	bool m_isRunning; // カウントをするか否か
};