#include "pch.h"
#include "Score.h"

Score* Score::m_score = nullptr;

Score::Score()
	: m_team1(0)
	, m_team2(0)
	, m_team3(0)
{
}

Score::~Score()
{
}
