#pragma once
#include "ObjectTag.h"

// 3D���f���̊��N���X
class GameObject
{
public:
	GameObject();
	GameObject(ObjectTag tag);
	GameObject(ObjectTag tag, VECTOR position);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �Z�b�^�[
	void SetPosition(const VECTOR& positon) { m_position = positon; }
	// �Q�b�^�[
	const VECTOR& GetPosition() const { return m_position; }
	const ObjectTag& GetTag() const { return m_tag; }
protected:
	// ��̃x�N�g���̊p�x��������
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVec����dirVec�̍ŒZ�̉�]�����𒲂ׂ�(Y��)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVec����aimVec�Ɍ�������degreeVelocity�̑��x��Y����]����
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

	VECTOR m_position;
	ObjectTag m_tag;
	int m_modelHandle;
};