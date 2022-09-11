#include "pch.h"
#include "ScoreUIController.h"
#include "Object.h"
#include "Image.h"
#include "Transform.h"
#include "Score.h"

void ScoreUIController::Start()
{
	m_transform = m_pParent->GetComponent<Transform>();
	m_index = 2;
	int x = -100;
	for (int i = 0; i < 4; i++)
	{
		x += 100;
		for (int j = 0; j < 10; j++)
		{
			std::string str = "data/Number/";
			str += std::to_string(j);
			str += ".png";
			m_scoreUI[i][j] = m_pParent->AddComponent<Image>();
			m_scoreUI[i][j]->Init(VAdd(VGet(x, 0.0f, 0.0f), m_transform->position), VGet(0.5f, 0.5f, 1.0f), 0.0, str.c_str());
			m_scoreUI[i][j]->IsDraw(false);
		}
	}
}

void ScoreUIController::Update()
{
	if (m_isStart)
	{

	}
	AdjustScore();
}

void ScoreUIController::Draw()
{
}

void ScoreUIController::AdjustScore()
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
