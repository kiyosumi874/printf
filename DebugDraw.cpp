#include "pch.h"
#include "DebugDraw.h"

// ワールド原点を中心に、縦横groundSizeの大きさ
// divideNum分割されたグリッド線を描画する
void DrawGrid(float groundSize, int divideNum)
{
	VECTOR L_start, L_end;						// 線分の始まりと終わりの座標
	int L_lineColor = GetColor(0, 128, 0);		// 黄緑色
	L_start = L_end = VGet(0.0f, 0.0f, 0.0f);	// 初期化

	float L_halfWidth = groundSize * 0.5f;				// グリッド線を引く半分の幅
	float L_addWidth = groundSize / (float)divideNum;	// グリッド線を引く幅

	// 縦線を引く
	L_start.z = -L_halfWidth;
	L_end.z = L_halfWidth;
	for (auto ix = 0; ix < divideNum + 1; ix++)
	{
		L_start.x = L_end.x = -L_halfWidth + ix * L_addWidth;
		DrawLine3D(L_start, L_end, L_lineColor);
	}

	// 横線を引く
	L_start.x = -L_halfWidth;
	L_end.x = L_halfWidth;
	for (auto iz = 0; iz < divideNum + 1; iz++)
	{
		L_start.z = L_end.z = -L_halfWidth + iz * L_addWidth;
		DrawLine3D(L_start, L_end, L_lineColor);
	}
}
