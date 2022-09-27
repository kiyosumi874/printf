#pragma once

class GameOverScene : public Scene
{
public:
	GameOverScene() = delete;
	GameOverScene(const MODE& mode);
	~GameOverScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:
	void UpdateTransitionStart();
	void UpdateTransitionPlay();
	void UpdateTransitionEnd();

	enum RankOrder
	{
		one,	// �@���A���B
		two,	// �@���B���A
		three,	// �A���@���B
		four,	// �A���B���@
		five,	// �B���@���A
		six		// �B���A���@
	};

	void RankOrderInit(RankOrder num);

	// �V�[�����̏�ԑJ�ڂ�\��
	enum class Transition
	{
		START,
		PLAY,
		OVER,
		END
	};

	Transition m_transition;
	TAG_SCENE m_tagScene;
	class Image* m_transitionImage[2];
	class ScoreUIController* m_scoreUICon[3];
};
