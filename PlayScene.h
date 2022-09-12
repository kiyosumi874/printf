#pragma once
class GameObject;

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
	int m_skyDomeHandle;

	void UpdateTransitionStart();
	void UpdateTransitionPlay();
	void UpdateTransitionOver();
	void UpdateTransitionEnd();

	void DrawTransitionStart();
	void DrawTransitionPlay();
	void DrawTransitionOver();
	void DrawTransitionEnd();

	class TimeCount* m_timeCount;
	class Image* m_startNumber[4];
	class Image* m_transitionImage[2];

	class TomatoUIController* m_tomatoUICon[2];
	class ScoreUIController* m_scoreUICon[3];

	class Map* m_map;  // Map
  
	std::vector<class TomatoWall*>m_pGameObjects;
	//std::list<class Object*>m_pObjectLists;

	const int m_tomatoWallNum = 8;
};
