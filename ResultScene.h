#pragma once

class ResultScene : public Scene
{
public:
	ResultScene() = delete;
	ResultScene(const MODE& mode);
	~ResultScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:
	void UpdateTransitionStart();
	void UpdateTransitionPlay();
	void UpdateTransitionEnd();

	enum RankOrder
	{
		one,	// ①→②→③
		two,	// ①→③→②
		three,	// ②→①→③
		four,	// ②→③→①
		five,	// ③→①→②
		six		// ③→②→①
	};

	void RankOrderInit(RankOrder num);

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
	class Image* m_transitionImage[2];
	class ScoreUIController* m_scoreUICon[3];
};
