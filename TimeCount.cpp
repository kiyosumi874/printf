//----------------------------------------
// @file TimeCount.cpp
// @brief 時間を計測する
// @author shiihara_kiyosumi
// @date 2022_09_01
//----------------------------------------

// ヘッダーファイルのインクルード
#include "pch.h"
#include "TimeCount.h"

// using宣言
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::system_clock;

// コンストラクタ
TimeCount::TimeCount()
{
	m_isCount = false;
	m_start = m_end = system_clock::now();
}

// デストラクタ
TimeCount::~TimeCount()
{
}

// 更新
void TimeCount::Update()
{
	if (m_isCount)
	{
		m_end = system_clock::now();
	}
}

// カウントを開始する
void TimeCount::StartCount()
{
	m_start = m_end = system_clock::now();
	m_isCount = true;
}

void TimeCount::RestCount()
{
	m_isCount = false;
}


// カウントを確認する
double TimeCount::CheckCount()
{
	// カウントを開始していないとき計算しないようにする
	if (!m_isCount) { return -1.0; }

	double time = static_cast<double>(duration_cast<microseconds>(m_end - m_start).count() / 1000000.0);
	return time;
}
