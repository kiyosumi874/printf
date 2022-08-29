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

	// ��̃x�N�g���̊p�x��������
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVec����dirVec�̍ŒZ�̉�]�����𒲂ׂ�(Y��)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVec����aimVec�Ɍ�������degreeVelocity�̑��x��Y����]����
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

	class Transform* m_pTransform;
	class Tag* m_pTag;

	VECTOR m_dir;			// ����
	VECTOR m_aimDir;		// �ڕW����
	VECTOR m_velocity;		// ���x

	int m_modelHandle;		// ���f���n���h��

	//float m_angle;			//	���_��]�p�x

	bool m_rotateNow;		// ��]��������p
};
