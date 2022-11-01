#include "pch.h"
#include "ResultScoreUI.h"
#include "ScoreUIController.h"
#include "Object.h"
#include "Image.h"
#include "Score.h"
#include "Transform.h"

void ResultScoreUI::Start()
{
	m_transform = m_pParent->GetComponent<Transform>();
	m_index = -1;
	m_alpha = 0;
	int x = -100;

	//x += 20;
	//std::string str = "data/scoreBack";
	//static int num = 0;
	//str += std::to_string(num);
	//if (++num > 2)
	//{
	//	num = 0;
	//}
	//str += ".png";
	//m_scoreBack = m_pParent->AddComponent<Image>();
	//m_scoreBack->Init(VAdd(VGet(-85.0f, -5.0f, 0.0f), m_transform->position), VGet(0.4f, 0.30f, 1.0f), 0.0, str.c_str());
	//m_scoreBack->IsDraw(true);
	//m_scoreBack->SetAlpha(0.0f);


}

void ResultScoreUI::Update()
{
	if (m_isStart)
	{
		if (m_alpha < 270)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					m_scoreUI[i][j]->SetAlpha(m_alpha);
				}
			}

			m_scoreBack->SetAlpha(m_alpha);

			m_alpha += 8.0f;
		}
		else
		{
			m_isStart = false;
		}
	}
	AdjustScore();
}

void ResultScoreUI::Draw()
{
}

void ResultScoreUI::CheckIsStart(const int index)
{
	m_isStart = true;
	m_index = index;

	if (index == 0)
	{
		m_scoreBack = m_pParent->AddComponent<Image>();
		m_scoreBack->Init(VAdd(VGet(-85.0f, -5.0f, 0.0f), m_transform->position), VGet(0.4f, 0.30f, 1.0f), 0.0, "data/scoreBack0.png");
		m_scoreBack->IsDraw(true);
		m_scoreBack->SetAlpha(0.0f);
	}
	if (index == 1)
	{
		m_scoreBack = m_pParent->AddComponent<Image>();
		m_scoreBack->Init(VAdd(VGet(-85.0f, -5.0f, 0.0f), m_transform->position), VGet(0.4f, 0.30f, 1.0f), 0.0, "data/scoreBack1.png");
		m_scoreBack->IsDraw(true);
		m_scoreBack->SetAlpha(0.0f);
	}
	if (index == 2)
	{
		m_scoreBack = m_pParent->AddComponent<Image>();
		m_scoreBack->Init(VAdd(VGet(-85.0f, -5.0f, 0.0f), m_transform->position), VGet(0.4f, 0.30f, 1.0f), 0.0, "data/scoreBack2.png");
		m_scoreBack->IsDraw(true);
		m_scoreBack->SetAlpha(0.0f);
	}

	auto x = -100;
	for (int i = 0; i < 4; i++)
	{
		x += 35;
		for (int j = 0; j < 10; j++)
		{
			std::string str = "data/Number/";
			str += std::to_string(j);
			str += ".png";
			m_scoreUI[i][j] = m_pParent->AddComponent<Image>();
			m_scoreUI[i][j]->Init(VAdd(VGet(x, 8.0f, 0.0f), m_transform->position), VGet(0.25f, 0.25f, 1.0f), 0.0, str.c_str());
			m_scoreUI[i][j]->IsDraw(false);
		}
	}
}

void ResultScoreUI::AdjustScore()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_scoreUI[i][j]->IsDraw(false);
		}
	}

	// チーム1
	if (m_index == 0)
	{
		int num = Score::GetTeam1Score();
		m_scoreUI[3][num % 10]->IsDraw(true);
		m_scoreUI[2][num % 100 / 10]->IsDraw(true);
		m_scoreUI[1][num % 1000 / 100]->IsDraw(true);
		m_scoreUI[0][num % 10000 / 1000]->IsDraw(true);

	}

	// チーム2
	if (m_index == 1)
	{
		int num = Score::GetTeam2Score();
		m_scoreUI[3][num % 10]->IsDraw(true);
		m_scoreUI[2][num % 100 / 10]->IsDraw(true);
		m_scoreUI[1][num % 1000 / 100]->IsDraw(true);
		m_scoreUI[0][num % 10000 / 1000]->IsDraw(true);
	}

	// チーム3
	if (m_index == 2)
	{
		int num = Score::GetTeam3Score();

		m_scoreUI[3][num % 10]->IsDraw(true);
		m_scoreUI[2][num % 100 / 10]->IsDraw(true);
		m_scoreUI[1][num % 1000 / 100]->IsDraw(true);
		m_scoreUI[0][num % 10000 / 1000]->IsDraw(true);
	}
}
