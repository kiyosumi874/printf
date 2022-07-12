#pragma once
class SceneManager;

class App
{
public:
	App();
	~App();

	void GameLoop();
private:
	SceneManager* m_sceneManager;

};