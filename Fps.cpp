#include "Fps.h"
#include "Common.h"
#include "Dxlib.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
Fps* Fps::m_this = nullptr;

Fps::Fps()
	: m_fps       (0.0f)
	, m_frameTime (0.0f)
	, m_flag      (false)
{
	memset(&m_timeStart, 0x00, sizeof(m_timeStart));
	memset(&m_timeEnd, 0x00, sizeof(m_timeEnd));
	memset(&m_timeFreq, 0x00, sizeof(m_timeFreq));

	// ‰‰ñŒvZ—p
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
	// ¡‚ÌŠÔ‚ğæ“¾
	QueryPerformanceCounter(&timeEnd);
	// (¡‚ÌŠÔ - ‘OƒtƒŒ[ƒ€‚ÌŠÔ) / ü”g” = Œo‰ßŠÔ(•b’PˆÊ)
	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

	if (frameTime < MIN_FRAME_TIME) { // ŠÔ‚É—]—T‚ª‚ ‚é
		// ƒ~ƒŠ•b‚É•ÏŠ·
		DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // •ª‰ğ”\‚ğã‚°‚é(‚±‚¤‚µ‚È‚¢‚ÆSleep‚Ì¸“x‚ÍƒKƒ^ƒKƒ^)
		Sleep(sleepTime);   // Q‚é
		timeEndPeriod(1);   // –ß‚·

		// ŸT‚É‚¿‰z‚µ(‚±‚¤‚µ‚È‚¢‚Æfps‚ª•Ï‚É‚È‚é?)
		return;
	}

	// Œo‰ßŠÔ‚ª0‚æ‚è‘å‚«‚¢(‚±‚¤‚µ‚È‚¢‚Æ‰º‚ÌŒvZ‚Åƒ[ƒœZ‚É‚È‚é‚Æv‚í‚ê)
	if (frameTime > 0.0f) 
	{ 
		fps = (fps * 0.99f) + (0.01f / frameTime); // •½‹Ïfps‚ğŒvZ
	}

	timeStart = timeEnd;
}

void Fps::Draw()
{
	printfDx("FPS:%0.2f\n", m_this->m_fps);
}
