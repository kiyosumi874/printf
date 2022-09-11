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

	int m_skyDomeHandle;
};
