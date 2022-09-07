#pragma once
#include "Component.h"

class Human : public Component
{
public:
	Human();
	~Human();

	void Start();
	void Update();
	void Draw();

private:
	void Input();
	void Rotate();
	void ChangeAnimation();  // アニメーション変更処理

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



	enum Anim
	{
		Idle,
		Run,
	};

	int m_animType;  // 現在のアニメーションが何か
	int m_animIndex;  // 現在のアニメーションを記録
	float m_animTime;  // アニメーションの経過時間
	float m_animTotalTime;  // アニメーションの総時間
	bool m_moveFlag;  // 動いているか

	std::vector<class Tomato*> m_tomatos;
};
