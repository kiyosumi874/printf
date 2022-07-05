#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
public:
	GameOverScene() = delete;
	GameOverScene(const MODE& mode);
	~GameOverScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:

};
