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
	enum ImageName
	{
		Logo,
		TransitionButton,
		Gradation
	};

	struct ImageVar
	{
		int modelHandle;
		int x;
		int y;
		int width;
		int height;
		float alpha;
	};

	enum ModelName
	{
		Ground,
		TomatoWall1,
		TomatoWall2,
		TomatoWall3
	};

	void InitImage(); // �摜�̏�����
	void UpdateImage(); // �摜�̍X�V
	void DrawImage(); // �摜�̕`��
	vector<int> m_images;

	void InitModel(); // 3D���f���̏�����
	void UpdateModel(); // 3D���f���̍X�V
	void DrawModel(); // 3D���f���̕`��
	vector<int> m_models;
};
