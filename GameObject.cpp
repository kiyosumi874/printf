#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: m_position()
	, m_tag()
	, m_modelHandle(-1)
{
}

// ������
GameObject::GameObject(ObjectTag tag)
	: m_position()
	, m_tag(tag)
	, m_modelHandle(-1)
{
}
// ������
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
	// �p���x�i�x���j�����W�A���p�ɕϊ��A�E��肩����肩�𒲂ׂ�
	float rotRadian = (DX_PI_F * degreeVelocity / 180.0f);
	rotRadian *= CalcRotationDirectionYAxis(nowVec, aimVec);

	// Y����]�s����쐬����
	MATRIX yRotMat = MGetRotY(rotRadian);

	// Y����]����
	VECTOR rotVec;
	rotVec = VTransform(nowVec, yRotMat);
	return rotVec;
}
