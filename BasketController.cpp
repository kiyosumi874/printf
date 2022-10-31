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
		auto pos = m_image->GetPos();
		if (pos.x < 10.0f)
		{
			m_image->MovePos(VGet(2.0f, 0.0f, 0.0f));
			if (pos.x > 8.0f)
			{
				pos.x = 10.0f;
				m_image->SetPos(pos);
			}

		}
		else if (pos.x > 1826.0f)
		{
			m_image->MovePos(VGet(-2.0f, 0.0f, 0.0f));
			if (pos.x < 1828.0f)
			{
				pos.x = 1826.0f;
				m_image->SetPos(pos);
			}
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
