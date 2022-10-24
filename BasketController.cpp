#include "pch.h"
#include "BasketController.h"
#include "Image.h"

void BasketController::Start()
{
	m_image = m_pParent->GetComponent<Image>();
}

void BasketController::Update()
{
	if (m_isStart)
	{
		if (m_image->GetPos().x < 10.0f)
		{
			m_image->MovePos(VGet(2.0f, 0.0f, 0.0f));

		}
		else if (m_image->GetPos().x > SCREEN_WIDTH - 114.0f)
		{
			m_image->MovePos(VGet(-2.0f, 0.0f, 0.0f));
		}
		else
		{
			m_isStart = false;
		}
	}
}

void BasketController::Draw()
{
}
