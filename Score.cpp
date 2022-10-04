#include "pch.h"
#include "Score.h"

Score* Score::m_score = nullptr;

Score::Score()
	: m_team1(0)
	, m_team2(0)
	, m_team3(0)
	, m_1PBulletNum(0)
	, m_2PBulletNum(0)
{
}

Score::~Score()
{
}
