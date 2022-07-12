#pragma once

class GameClearScene : public Scene
{
public:
	GameClearScene() = delete;
	GameClearScene(const MODE& mode);
	~GameClearScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:
};
