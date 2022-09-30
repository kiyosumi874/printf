#pragma once
#include "GameObject.h"

class TomatoWall : public GameObject
{
public:
	TomatoWall(ObjectTag tag, VECTOR position);  // �R���X�g���N�^
	~TomatoWall();  // �f�X�g���N�^

	void Update() override;  // �X�V����
	void Draw() override;    // �`�揈��

	void DecreaseAllTomatoNum() { m_allTomatoNum = m_allTomatoNum - 1; }  // �R�̃g�}�g�̐������炷(���葤����ǂ�ł��炤)

	// Getter
	int GetAllTomatoNum() { return m_allTomatoNum; }
	float GetWidthDistance() { return m_width; } 
private:
	VECTOR m_size;  // �g�}�g�̎R�͈̔�
	const int m_modelPattern = 5;  // ���f���̐�
	int m_modelPatternIndex;  // �����݂̃��f���ԍ�
	int m_modelPatternHandle[5];  // ���f���f�[�^
	const int m_modelChangeNum[4];  // ���f����ς���g�}�g�̐�

	int m_allTomatoNum;  // �g�}�g�̎R�̃g�}�g�̑���
	int m_time;  // �g�}�g�̎R���Ȃ��Ȃ�����̎���
	const int m_revivalTime;  // �g�}�g�̎R����������܂ł�����

	const float m_width = 20.0f;  // �����̕�
};

