#pragma once
#include "Component.h"

class TomatoWallFull;
class TomatoWallOne;
class TomatoWallTwo;
class TomatoWallThree;
class TomatoWallFour;

class TomatoWallManager : public ModelBase, public Component
{
public:
	TomatoWallManager();
	~TomatoWallManager();

	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
	void Update() override;
	void Draw() override;
	void Start() override;

	void OnCollisionEnter(class ColliderComponent* ownColl, class ColliderComponent* otherColl) override;

	void DecreaseAllTomatoNum() { m_allTomatoNum = m_allTomatoNum - 1; }
	int GetAllTomatoNum() { return m_allTomatoNum; }
	float GetWidthDistance() { return m_width; }

	VECTOR GetPosition() { return m_var.pos; }
	VECTOR GetRotate() { return m_var.rotate; }
	VECTOR GetScale() { return m_var.scale; }

private:
	class WallCollider* m_pWall = nullptr;

	class Transform* m_pTransform = nullptr;

	const int m_modelPattern = 5;
	int m_modelPatternIndex;
	const int m_modelChangeNum[4];

	class TomatoWall* m_tomatoWall[5];

	Tag* m_pTag = nullptr;

	int m_allTomatoNum;
	int m_time;
	const int m_revivalTime;

	const float m_width = 18.0f;  // 自分の幅
};

