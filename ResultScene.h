﻿#pragma once

class ResultScene : public Scene
{
public:
	ResultScene() = delete;
	ResultScene(const MODE& mode);
	~ResultScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:
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

	void UpdateTransitionStart();
	void UpdateTransitionPlay();
	void UpdateTransitionOver();
	void UpdateTransitionEnd();

	void DrawTransitionStart();
	void DrawTransitionPlay();
	void DrawTransitionOver();
	void DrawTransitionEnd();
};