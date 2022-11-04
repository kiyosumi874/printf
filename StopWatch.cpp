//----------------------------------------
// @file StopWatch.cpp
// @brief 時間を計測する
// @author shiihara_kiyosumi
// @date 2022_11_04
//----------------------------------------

// ヘッダーファイルのインクルード
#include "pch.h"

void StopWatch::Start()
{
	m_isRunning = false;
	m_begin = 0;
	m_elapsed = 0;
	m_end = 0;
}

void StopWatch::Update()
{
	if (m_isRunning)
	{
		m_end = clock();
		m_elapsed = m_end - m_begin;
	}
}

void StopWatch::StartCount()
{
	m_isRunning = true;
	m_begin = clock();
	m_end = clock() + m_elapsed;
}

void StopWatch::StopCount()
{
	m_isRunning = false;
}

void StopWatch::ResetCount()
{
	m_begin = clock();
	m_end = clock();
	m_elapsed = 0;
}

double StopWatch::GetSeconds()
{
	return m_elapsed / 1000.0;
}
