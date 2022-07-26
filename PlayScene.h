#pragma once
class GameObject;
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
	class Map* m_map;  // Map�N���X�̃|�C���^
  
	std::vector<GameObject*>m_pGameObjects;

	Player* m_pPlayer;
	Enemy* m_pEnemy;
	Camera* m_pCamera;
};
