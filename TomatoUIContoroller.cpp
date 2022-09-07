#include "pch.h"
#include "TomatoUIContoroller.h"
#include "Object.h"
#include "Image.h"
#include "Transform.h"

void TomatoUIController::Start()
{
	m_isStart = false;
	m_transform = m_pParent->GetComponent<Transform>();
	for (int i = 0; i < cTomatoMax; i++)
	{
		m_tomatoUI[i] = m_pParent->AddComponent<Image>();
		m_tomatoUI[i]->Init(VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0, "data/tomatoUI.png");
		m_tomatoUI[i]->SetExtendRate(VGet(0.3f, 0.3f, 0.3f));
		m_tomatoUI[i]->MovePos(VAdd(VGet(0.0f, -50.0f * static_cast<float>(i), 0.0f), m_transform->position));
	}
}

// 更新
void TomatoUIController::Update()
{
	if (m_isStart)
	{
		if (m_tomatoUI[0]->GetPos().x < 10.0f)
		{
			for (int i = 0; i < cTomatoMax; i++)
			{
				m_tomatoUI[i]->MovePos(VGet(2.0f, 0.0f, 0.0f));
			}
		}
		else if (m_tomatoUI[0]->GetPos().x > SCREEN_WIDTH - 60.0f)
		{
			for (int i = 0; i < cTomatoMax; i++)
			{
				m_tomatoUI[i]->MovePos(VGet(-2.0f, 0.0f, 0.0f));
			}
		}
		else
		{
			m_isStart = false;
		}
	}
	AdjustTomato(m_index);
}

// 描画
void TomatoUIController::Draw()
{
}

void TomatoUIController::AdjustTomato(const int index)
{
	// 1Pの残段数
	if (index == 0)
	{

	}

	// 2Pの残段数
	if (index == 1)
	{

	}
}
