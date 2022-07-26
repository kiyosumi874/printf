#pragma once
#include "ObjectTag.h"

// 3Dモデルの基底クラス
class GameObject
{
public:
	GameObject();
	GameObject(ObjectTag tag);
	GameObject(ObjectTag tag, VECTOR position);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	// セッター
	void SetPosition(const VECTOR& positon) { m_position = positon; }
	// ゲッター
	const VECTOR& GetPosition() const { return m_position; }
	const ObjectTag& GetTag() const { return m_tag; }
protected:
	// 二つのベクトルの角度が同じか
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVecからdirVecの最短の回転方向を調べる(Y軸)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVecからaimVecに向かってdegreeVelocityの速度でY軸回転する
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

	VECTOR m_position;
	ObjectTag m_tag;
	int m_modelHandle;
};