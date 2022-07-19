#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: m_position()
	, m_tag()
	, m_modelHandle(-1)
{
}

// 初期化
GameObject::GameObject(ObjectTag tag)
	: m_position()
	, m_tag(tag)
	, m_modelHandle(-1)
{
}
// 初期化
GameObject::GameObject(ObjectTag tag, VECTOR position)
	: m_position(position)
	, m_tag(tag)
	, m_modelHandle(-1)
{
}

GameObject::~GameObject()
{
}

bool GameObject::IsNearAngle(const VECTOR& v1, const VECTOR& v2)
{
	float dot = VDot(v1, v2);
	if (dot < 0.99f)
	{
		return true;
	}
	return false;
}

float GameObject::CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
{
	VECTOR axis;
	axis = VCross(nowVec, dirVec);
	if (axis.y < 0.0f)
	{
		return -1.0f;
	}
	return 1.0f;
}

VECTOR GameObject::RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity)
{
	// 角速度（度数）をラジアン角に変換、右回りか左回りかを調べる
	float rotRadian = (DX_PI_F * degreeVelocity / 180.0f);
	rotRadian *= CalcRotationDirectionYAxis(nowVec, aimVec);

	// Y軸回転行列を作成する
	MATRIX yRotMat = MGetRotY(rotRadian);

	// Y軸回転する
	VECTOR rotVec;
	rotVec = VTransform(nowVec, yRotMat);
	return rotVec;
}
