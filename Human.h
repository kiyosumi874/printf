#pragma once
#include "Component.h"

class Human : public Component
{
public:
	Human();
	~Human();

	void Update();
	void Draw();

private:
	void Input();
	void Rotate();

	// 二つのベクトルの角度が同じか
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVecからdirVecの最短の回転方向を調べる(Y軸)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

	class Transform* m_pTransform;
	class Tag* m_pTag;

	VECTOR m_dir;			// 向き
	VECTOR m_aimDir;		// 目標向き
	VECTOR m_velocity;		// 速度

	int m_modelHandle;		// モデルハンドル

	//float m_angle;			//	視点回転角度

	bool m_rotateNow;		// 回転中か判定用
};
