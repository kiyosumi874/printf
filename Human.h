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

	void SetTomatoWallPtr(std::vector<class TomatoWall*>* tomatoWall);
private:
	void Input();
	void Rotate();
	void ChangeAnimation();	// アニメーション変更処理
	void TomatoCollect();	// トマト回収処理
	double GetDistance(VECTOR& pos1, VECTOR& pos2);

	// 二つのベクトルの角度が同じか
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVecからdirVecの最短の回転方向を調べる(Y軸)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

	class Transform* m_pTransform;
	class Tag* m_pTag;
	std::vector<class TomatoWall*>* m_tomatoWall;

	VECTOR m_dir;			// 向き
	VECTOR m_aimDir;		// 目標向き
	VECTOR m_velocity;		// 速度

	int m_modelHandle;		// モデルハンドル
	int m_bulletNum;        // 球の所持数
	const int m_bulletCapacity; // 球の限界所持数

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
};
