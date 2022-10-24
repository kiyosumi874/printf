//----------------------------------------
// @file ScoreUIController.h
// @brief �X�R�A��UI
// @author shiihara_kiyosumi
// @date 2022_10_24
//----------------------------------------

// ���d�C���N���[�h�h�~
#pragma once

// �w�b�_�[�t�@�C���̃C���N���[�h
#include "Component.h"


class BasketController : public Component
{
public:

	// �ŏ��Ɉ��ʂ���
	void Start()override;

	// �X�V
	void Update()override;

	// �`��
	void Draw()override;

	// UI����ʂɈړ���������
	void CheckIsStart(const int index)
	{
		m_isStart = true;
		m_index = index;
	}

private:
	bool m_isStart;
	class Image* m_image;
	int m_index; // 1 or 0 (1��������1P,0��������2P��UI�Ƃ�������)
};
