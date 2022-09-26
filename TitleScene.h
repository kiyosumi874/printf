#pragma once

class TitleScene : public Scene
{
public:
	TitleScene() = delete;
	TitleScene(const MODE& mode);
	~TitleScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:
	int m_logoGraph;
	int m_enterGraph;
	int m_postUIGraph;

	int m_groundHandle;
	int m_tomatoHandle;
	int m_tomatoHandle2;
	int m_tomatoHandle3;
};
