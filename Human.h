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
	void ChangeAnimation();  // �A�j���[�V�����ύX����

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



	enum Anim
	{
		Idle,
		Run,
	};

	int m_animType;  // ���݂̃A�j���[�V����������
	int m_animIndex;  // ���݂̃A�j���[�V�������L�^
	float m_animTime;  // �A�j���[�V�����̌o�ߎ���
	float m_animTotalTime;  // �A�j���[�V�����̑�����
	bool m_moveFlag;  // �����Ă��邩

	std::vector<class Tomato*> m_tomatos;
};
