#include "pch.h"
#include "TimeUIController.h"
#include "Object.h"
#include "TimeCount.h"
#include "Image.h"

TimeUIController::TimeUIController()
{
	// 未実装
}

TimeUIController::~TimeUIController()
{
	// 未実装
}

void TimeUIController::Init(int digit, int number)
{
	m_digit = digit;
	m_number = number;
	m_pStopWatch = m_pParent->GetComponent<StopWatch>();

	m_pImage = m_pParent->GetComponent<Image>();
}

void TimeUIController::Update()
{
	auto nowTime = m_pStopWatch->GetSeconds();
	if (nowTime != 0.0)
	{
		UpdateDidit0(92 - nowTime);
		UpdateDidit1(92 - nowTime);
		UpdateDidit2(92 - nowTime);
		UpdateDidit3(92 - nowTime);
	}
	

	//MyOutputDebugString("Time:%lf\n", nowTime);
}

void TimeUIController::UpdateDidit0(double nowTime)
{
	if (m_digit == 0)
	{
		if (static_cast<int>(nowTime) % 10 == m_number)
		{
			m_pImage->IsDraw(true);
		}
		else
		{
			m_pImage->IsDraw(false);
		}
	}
}

void TimeUIController::UpdateDidit1(double nowTime)
{
	if (m_digit == 1)
	{
		if (static_cast<int>(nowTime) % 60 / 10 == m_number)
		{
			m_pImage->IsDraw(true);
		}
		else
		{
			m_pImage->IsDraw(false);
		}
	}
}

void TimeUIController::UpdateDidit2(double nowTime)
{
	if (m_digit == 2)
	{
		if (static_cast<int>(nowTime) % 600 / 60 == m_number)
		{
			m_pImage->IsDraw(true);
		}
		else
		{
			m_pImage->IsDraw(false);
		}
	}
}

void TimeUIController::UpdateDidit3(double nowTime)
{
	if (m_digit == 3)
	{
		if (static_cast<int>(nowTime) / 600 == m_number)
		{
			m_pImage->IsDraw(true);
		}
		else
		{
			m_pImage->IsDraw(false);
		}
	}
}
