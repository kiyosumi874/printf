#pragma once
class GameObject;
class TomatoWall;
class Player;
class Enemy;
class Camera;

class PlayScene : public Scene
{
public:
	PlayScene() = delete;
	PlayScene(const MODE& mode);
	~PlayScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:
	// ÉVÅ[Éìì‡ÇÃèÛë‘ëJà⁄Çï\Ç∑
	enum class Transition
	{
		START,
		PLAY,
		OVER,
		END
	};

	Transition m_transition;
	TAG_SCENE m_tagScene;

	bool m_isStartBlendAdd;
	float m_startBlendAdd;
	int m_graphHandleWhite;

	void UpdateTransitionStart();
	void UpdateTransitionPlay();
	void UpdateTransitionOver();
	void UpdateTransitionEnd();

	void DrawTransitionStart();
	void DrawTransitionPlay();
	void DrawTransitionOver();
	void DrawTransitionEnd();

	class TimeCount* m_timeCount;

	class Map* m_map;  // Map
  
	std::vector<GameObject*>m_pGameObjects;
	//std::list<class Object*>m_pObjectLists;

	const int m_tomatoWallNum = 2;

	TomatoWall* m_pTomatoWall[2];
	Player* m_pPlayer1P;
	Player* m_pPlayer2P;
	Camera* m_pCamera1P;
	Camera* m_pCamera2P;
	Enemy* m_pEnemy1;
	Enemy* m_pEnemy2;
};
