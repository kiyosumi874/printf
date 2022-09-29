#pragma once
#include <vector>

using namespace std;

class TitleScene : public Scene
{
public:
	TitleScene() = delete; // �f�t�H���g�R���X�g���N�^�͎g��Ȃ�
	TitleScene(const MODE& mode); // �R���X�g���N�^
	~TitleScene() override; // �f�X�g���N�^

	TAG_SCENE Update() override; // �X�V
	void Draw() override; // �`��

private:
	// �I�u�W�F�N�g�̏�����
	void InitObject();
	void InitLogo();
	void InitTransitionButton();
	void InitGradation();

	void TermObject(); // �I�u�W�F�N�g�̉��
	void UpdateObject(); // �I�u�W�F�N�g�̍X�V
	void DrawObject(); // �I�u�W�F�N�g�̕`��

	enum ModelName
	{
		Ground,
		TomatoWall1,
		TomatoWall2,
		TomatoWall3
	};

	void InitModel();   // 3D���f���̏�����
	void UpdateModel(); // 3D���f���̍X�V
	void DrawModel();   // 3D���f���̕`��
	vector<int> m_models;
};