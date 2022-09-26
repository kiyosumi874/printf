#include "pch.h"
#include "TimeUIController.h"
#include "Object.h"
#include "TimeCount.h"
#include "Image.h"

TimeUIController::TimeUIController()
{
	// –¢ŽÀ‘•
}

TimeUIController::~TimeUIController()
{
	// –¢ŽÀ‘•
}

void TimeUIController::Init(int digit, int number)
{
	m_digit = digit;
	m_number = number;
	m_pTimeCount = m_pParent->GetComponent<TimeCount>();

	m_pImage = m_pParent->GetComponent<Image>();
}

void TimeUIController::Update()
{
	auto nowTime = m_pTimeCount->CheckCount();
	if (nowTime != -1.0)
	{
		UpdateDidit0(91 - nowTime);
		UpdateDidit1(91 - nowTime);
		UpdateDidit2(91 - nowTime);
		UpdateDidit3(91 - nowTime);
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
