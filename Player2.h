﻿#pragma once
#include "Human.h"

class Player2 : public Human
{
public:
	Player2();
	~Player2() override;

	void Start() override;
	void Update() override;
	void Draw() override;
private:
	void Input();
	void Rotate();
	void Animation() override;  // アニメーション処理
	void ChangeAnimation() override;	// アニメーション変更処理
	void TomatoCollect();	// トマト回収処理

	// 二つのベクトルの角度が同じか
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVecからdirVecの最短の回転方向を調べる(Y軸)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

	VECTOR m_dir;			// 向き
	VECTOR m_aimDir;		// 目標向き
	VECTOR m_velocity;		// 速度
	VECTOR m_inputVector;  // 押した合計座標取得用変数

	bool m_rotateNow;		// 回転中か判定用
};
