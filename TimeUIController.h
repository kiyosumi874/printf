//----------------------------------------
// @file TimeUIController.h
// @brief ���v��UI
// @author shiihara_kiyosumi
// @date 2022_09_02
//----------------------------------------

// ���d�C���N���[�h�h�~
#pragma once

// �w�b�_�[�t�@�C���̃C���N���[�h
#include "Component.h"

class TimeUIController : public Component
{
public:
	TimeUIController();
	~TimeUIController();
	void Init(int digit, int number);
	void Update()override;

private:
	void UpdateDidit0(double nowTime);
	void UpdateDidit1(double nowTime);
	void UpdateDidit2(double nowTime);
	void UpdateDidit3(double nowTime);

	class TimeCount* m_pTimeCount;
	class Image* m_pImage;
	int m_digit;
	int m_number;
};