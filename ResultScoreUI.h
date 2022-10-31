//----------------------------------------
// @file ScoreUIController.h
// @brief �X�R�A��UI
// @author iguchiShougo
// @date 2022_10_31
//----------------------------------------

// ���d�C���N���[�h�h�~
#pragma once

// �w�b�_�[�t�@�C���̃C���N���[�h
#include "Component.h"


class ResultScoreUI : public Component
{
public:

	// �ŏ��Ɉ��ʂ���
	void Start()override;

	// �X�V
	void Update()override;

	// �`��
	void Draw()override;

	// UI����ʂɈړ���������
	void CheckIsStart(const int index);

private:

	void AdjustScore();

	class Image* m_scoreUI[4][10]; // 4�� 0����9
	class Image* m_scoreBack;
	class Transform* m_transform;

	bool m_isStart;
	int m_index; // 0 or 1 or 2 (0��������1P,1��������2P��UI�Ƃ�������)
	float m_alpha;
};
