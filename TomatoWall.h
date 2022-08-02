#pragma once
#include "GameObject.h"

class TomatoWall : public GameObject
{
public:
	TomatoWall(ObjectTag tag, VECTOR position);
	~TomatoWall();

	void Update() override;
	void Draw() override;

	void SetAllTomatoNum() { m_allTomatoNum = m_allTomatoNum - 1; }
	int GetTomatoLimit() { return m_tomatoNumLimit; }
private:
	const int m_modelPattern = 5;
	std::string m_modelPatternHandle[5];

	int m_allTomatoNum;

	const int m_tomatoNumLimit = 10;
};

