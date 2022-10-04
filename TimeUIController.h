//----------------------------------------
// @file TimeUIController.h
// @brief 時計のUI
// @author shiihara_kiyosumi
// @date 2022_09_02
//----------------------------------------

// 多重インクルード防止
#pragma once

// ヘッダーファイルのインクルード
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