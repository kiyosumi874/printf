#pragma once
#include "Scene.h"


class PlayScene : public Scene
{
public:
	PlayScene() = delete;
	PlayScene(const MODE& mode);
	~PlayScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:

};
