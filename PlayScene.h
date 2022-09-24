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
	//class Map* m_map;  // Map
	// シーン内の状態遷移を表す
	enum class Transition
	{
		START,
		PLAY,
		OVER,
		END
	};

	Transition m_transition;
	TAG_SCENE m_tagScene;

	bool m_playOnFlag;
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
	class Image* m_startNumber[4];
	class Image* m_transitionImage[2];
	class Image* m_timerKoron;
	class Image* m_timerBack;

	class TomatoUIController* m_tomatoUICon[2];
	class ScoreUIController* m_scoreUICon[3];
  
	std::vector<class TomatoWall*>m_pGameObjects;
	//std::list<class Object*>m_pObjectLists;

	class Ground* m_pGround;
	class HitEffect* m_HitEffect;

	const int m_tomatoWallNum = 8;

};
