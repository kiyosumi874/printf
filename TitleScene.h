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

};
