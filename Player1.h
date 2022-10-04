#pragma once
#include "Human.h"

class Player1 : public Human
{
public:
	Player1();
	~Player1() override;

	void Start() override;
	void Update() override;
	void Draw() override;
private:
	void Input();
	void Rotate();
	void Animation() override;  // �A�j���[�V��������
	void ChangeAnimation() override;	// �A�j���[�V�����ύX����
	void TomatoCollect();	// �g�}�g�������

	// ��̃x�N�g���̊p�x��������
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVec����dirVec�̍ŒZ�̉�]�����𒲂ׂ�(Y��)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVec����aimVec�Ɍ�������degreeVelocity�̑��x��Y����]����
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

	VECTOR m_dir;			// ����
	VECTOR m_aimDir;		// �ڕW����
	VECTOR m_velocity;		// ���x
	VECTOR m_inputVector;  // ���������v���W�擾�p�ϐ�

	bool m_rotateNow;		// ��]��������p
};
