#pragma once
class GameObject;
class TomatoWall;
class Player;
class Enemy;
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
	class Map* m_map;  // Map
  
	std::vector<GameObject*>m_pGameObjects;

	TomatoWall* m_pTomatoWall;
	Player* m_pPlayer1P;
	Player* m_pPlayer2P;
	Camera* m_pCamera1P;
	Camera* m_pCamera2P;
	Enemy* m_pEnemy1;
	Enemy* m_pEnemy2;
};
