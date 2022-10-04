#include "pch.h"
Fps* Fps::m_this = nullptr;

Fps::Fps()
	: m_fps       (0.0f)
	, m_frameTime (0.0f)
	, m_flag      (false)
{
	memset(&m_timeStart, 0x00, sizeof(m_timeStart));
	memset(&m_timeEnd, 0x00, sizeof(m_timeEnd));
	memset(&m_timeFreq, 0x00, sizeof(m_timeFreq));

	// 初回計算用
	QueryPerformanceCounter(&m_timeStart);
	QueryPerformanceFrequency(&m_timeFreq);
}

Fps::~Fps()
{
}

void Fps::Update()
{
	auto& timeStart = m_this->m_timeStart;
	auto& timeEnd = m_this->m_timeEnd;
	auto& timeFreq = m_this->m_timeFreq;
	auto& frameTime = m_this->m_frameTime;
	auto& fps = m_this->m_fps;

	m_this->m_flag ^= true;
	// 今の時間を取得
	QueryPerformanceCounter(&timeEnd);
	// (今の時間 - 前フレームの時間) / 周波数 = 経過時間(秒単位)
	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

	if (frameTime < MIN_FRAME_TIME) { // 時間に余裕がある
		// ミリ秒に変換
		DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // 分解能を上げる(こうしないとSleepの精度はガタガタ)
		Sleep(sleepTime);   // 寝る
		timeEndPeriod(1);   // 戻す

		// 次週に持ち越し(こうしないとfpsが変になる?)
		return;
	}

	// 経過時間が0より大きい(こうしないと下の計算でゼロ除算になると思われ)
	if (frameTime > 0.0f) 
	{ 
		fps = (fps * 0.99f) + (0.01f / frameTime); // 平均fpsを計算
	}

	timeStart = timeEnd;
}

void Fps::Draw()
{
	printfDx("FPS:%0.2f\n", m_this->m_fps);
}
