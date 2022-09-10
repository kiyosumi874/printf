//----------------------------------------
// @file TomatoUIController.h
// @brief �c�i����UI
// @author shiihara_kiyosumi
// @date 2022_09_08
//----------------------------------------

// ���d�C���N���[�h�h�~
#pragma once

// �w�b�_�[�t�@�C���̃C���N���[�h
#include "Component.h"

// �萔
const int cTomatoMax = 10;

class TomatoUIController : public Component
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

	void AdjustTomato(const int index);

	class Image* m_tomatoUI[cTomatoMax];
	class Transform* m_transform;

	bool m_isStart;
	int m_index; // 0 or 1 (0��������1P,1��������2P��UI�Ƃ�������)
};
