//----------------------------------------
// @file TimeCount.cpp
// @brief ���Ԃ��v������
// @author shiihara_kiyosumi
// @date 2022_09_01
//----------------------------------------

// �w�b�_�[�t�@�C���̃C���N���[�h
#include "pch.h"
#include "TimeCount.h"

// using�錾
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::system_clock;

// �R���X�g���N�^
TimeCount::TimeCount()
{
	m_isCount = false;
	m_start = m_end = system_clock::now();
}

// �f�X�g���N�^
TimeCount::~TimeCount()
{
}

// �X�V
void TimeCount::Update()
{
	if (m_isCount)
	{
		m_end = system_clock::now();
	}
}

// �J�E���g���J�n����
void TimeCount::StartCount()
{
	m_start = m_end = system_clock::now();
	m_isCount = true;
}

void TimeCount::RestCount()
{
	m_isCount = false;
}


// �J�E���g���m�F����
double TimeCount::CheckCount()
{
	// �J�E���g���J�n���Ă��Ȃ��Ƃ��v�Z���Ȃ��悤�ɂ���
	if (!m_isCount) { return -1.0; }

	double time = static_cast<double>(duration_cast<microseconds>(m_end - m_start).count() / 1000000.0);
	return time;
}
