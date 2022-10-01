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
	void InitSkyDomeModel();
	void InitGroundModel();
	void InitTomatoWallModel();
	void InitLogoUI();
	void InitTransitionButtonUI();
	void InitGradationUI();

	void TermObject(); // �I�u�W�F�N�g�̉��
	void UpdateObject(); // �I�u�W�F�N�g�̍X�V
	void DrawObject(); // �I�u�W�F�N�g�̕`��
};