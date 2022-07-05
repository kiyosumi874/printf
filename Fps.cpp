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

	// ����v�Z�p
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
	// ���̎��Ԃ��擾
	QueryPerformanceCounter(&timeEnd);
	// (���̎��� - �O�t���[���̎���) / ���g�� = �o�ߎ���(�b�P��)
	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<float>(timeFreq.QuadPart);

	if (frameTime < MIN_FRAME_TIME) { // ���Ԃɗ]�T������
		// �~���b�ɕϊ�
		DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

		timeBeginPeriod(1); // ����\���グ��(�������Ȃ���Sleep�̐��x�̓K�^�K�^)
		Sleep(sleepTime);   // �Q��
		timeEndPeriod(1);   // �߂�

		// ���T�Ɏ����z��(�������Ȃ���fps���ςɂȂ�?)
		return;
	}

	// �o�ߎ��Ԃ�0���傫��(�������Ȃ��Ɖ��̌v�Z�Ń[�����Z�ɂȂ�Ǝv���)
	if (frameTime > 0.0f) 
	{ 
		fps = (fps * 0.99f) + (0.01f / frameTime); // ����fps���v�Z
	}

	timeStart = timeEnd;
}

void Fps::Draw()
{
	printfDx("FPS:%0.2f\n", m_this->m_fps);
}
