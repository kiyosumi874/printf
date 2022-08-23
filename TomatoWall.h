#pragma once
#include "GameObject.h"

class TomatoWall : public GameObject
{
public:
	TomatoWall(ObjectTag tag, VECTOR position);
	~TomatoWall();

	void Update() override;
	void Draw() override;

	void DecreaseAllTomatoNum() { m_allTomatoNum = m_allTomatoNum - 1; }
	int GetAllTomatoNum() { return m_allTomatoNum; }
	float GetWidthDistance() { return m_width; }
private:
	VECTOR m_size;
	const int m_modelPattern = 5;
	int m_modelPatternIndex;
	std::string m_modelPatternHandle[5];
	const int m_modelChangeNum[4];

	int m_allTomatoNum;
	int m_time;
	const int m_revivalTime;

	const float m_width = 20.0f;  // é©ï™ÇÃïù
};

