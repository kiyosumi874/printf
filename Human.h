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
	void ChangeAnimation();	// �A�j���[�V�����ύX����
	void TomatoCollect();	// �g�}�g�������
	double GetDistance(VECTOR& pos1, VECTOR& pos2);

	// ��̃x�N�g���̊p�x��������
	bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);
	// nowVec����dirVec�̍ŒZ�̉�]�����𒲂ׂ�(Y��)
	float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);
	// nowVec����aimVec�Ɍ�������degreeVelocity�̑��x��Y����]����
	VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity);

	class Transform* m_pTransform;
	class Tag* m_pTag;
	std::vector<class TomatoWall*>* m_tomatoWall;

	VECTOR m_dir;			// ����
	VECTOR m_aimDir;		// �ڕW����
	VECTOR m_velocity;		// ���x

	int m_modelHandle;		// ���f���n���h��
	int m_bulletNum;        // ���̏�����
	const int m_bulletCapacity; // ���̌��E������

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
};
