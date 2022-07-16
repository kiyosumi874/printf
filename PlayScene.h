#pragma once
class GameObject;
class Player;
class Camera;

class PlayScene : public Scene
{
public:
	PlayScene() = delete;
	PlayScene(const MODE& mode);
	~PlayScene() override;

	TAG_SCENE Update() override;
	void Draw() override;

private:
	std::vector<GameObject*>m_pGameObjects;

	Player* m_pPlayer;
	Camera* m_pCamera;
};
