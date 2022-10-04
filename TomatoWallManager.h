#pragma once
#include "GameObject.h"

class TomatoWallFull;
class TomatoWallOne;
class TomatoWallTwo;
class TomatoWallThree;
class TomatoWallFour;

class TomatoWallManager : public GameObject
{
public:
	TomatoWallManager(ObjectTag tag);
	~TomatoWallManager();

	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
	void Update() override;
	void Draw() override;

	void DecreaseAllTomatoNum() { m_allTomatoNum = m_allTomatoNum - 1; }
	int GetAllTomatoNum() { return m_allTomatoNum; }
	float GetWidthDistance() { return m_width; }

	VECTOR GetPosition() { return m_position; }
	VECTOR GetRotate() { return m_rotate; }
	VECTOR GetScale() { return m_scale; }

private:
	VECTOR m_position;
	VECTOR m_rotate;
	VECTOR m_scale;

	const int m_modelPattern = 5;
	int m_modelPatternIndex;
	const int m_modelChangeNum[4];

	class TomatoWall* m_tomatoWall[5];

	int m_allTomatoNum;
	int m_time;
	const int m_revivalTime;

	const float m_width = 20.0f;  // 自分の幅
};

