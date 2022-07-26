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
	class Map* m_map;  // Map�N���X�̃|�C���^
  
	std::vector<GameObject*>m_pGameObjects;

	Player* m_pPlayer1P;
	Player* m_pPlayer2P;
	Camera* m_pCamera1P;
	Camera* m_pCamera2P;
};
