#pragma once
#include "Human.h"

class PlayerCPU : public Human
{
public:
    PlayerCPU();
    ~PlayerCPU() override;

	void Start() override;	// �R���|�[�l���g����������.
	void Update() override;	// �X�V����.
	void Draw() override;	// �`�揈��.

	void SetAimTargetPtr(class Object* target);  // PlayerCPU�ɑ_�킹����Target���Z�b�g

private:
	void ProcessTomato();

	enum Type
	{
		SearchTarget,   // �^�[�Q�b�g��T��
		AimTarget,      // �^�[�Q�b�g��_��
		EscapeTarget,   // �^�[�Q�b�g���瓦����
		TomatoCollect,  // �g�}�g��������ɍs��
	};

	// �G�l�~�[�̃p�����[�^�[
	VECTOR m_velocity;  // �ړ��X�s�[�h
	VECTOR m_dir;       // ����
	VECTOR m_tomatoDir;  // �g�}�g�𓊂������
	VECTOR m_moveValue;  // �����ړ���
	VECTOR m_avoidVelocity;

	// ���쎞��
	int m_moveTime;  // �����s������
	const int m_movePhaseTime;  // ���̍s���Ɉڂ鎞��
	float m_shotTime;   // �����鎞��
	const float m_shotPhaseTime;  // ��������̃N�[������

	// �t���O�ϐ�
	int m_moveType;  // ���̍s��
	bool m_aimTargetFlag;  // �W�I�Ɍ����Ĉړ����邩
	bool m_avoidWallFlag;  // �ǂ������
	bool m_absolutelyMoveFlag;  // ��΂Ɉړ�������t���O

	// �͈͎w��ϐ�
	const float m_targetRangeMin = 0.0f;        // �^�[�Q�b�g�����m����n�܂�l
	const float m_targetRangeMax = 150.0f;      // �^�[�Q�b�g�����m����ŏI�͈͒l
	const float m_targetMoveRangeMin = 60.0f;   // �^�[�Q�b�g�ɑ΂���s���̕ω��ŏ��l
	const float m_targetMoveRangeMax = 100.0f;  // �^�[�Q�b�g�ɑ΂���s���̕ω��ő�l
	const float m_targetEscapeRange = 200.0f;   // �^�[�Q�b�g���瓦����͈�

	// �|�C���^
	std::vector<class Object*> m_target;  // PlayerCPU�ɏ���n�����^�[�Q�b�g

	// �֐�
	void CheckMovePattern();  // �s���p�^�[�����`�F�b�N���Ď��s����

	void CheckTargetMovePattern();  // �^�[�Q�b�g�ɑ΂��Ă̍s���p�^�[�������s����
	void Move1Target(class Object* player);  // �W�I�ɍ��킹�ē�������
	void Move2Target(class Object* player);  // �W�I�����Ȃ��Ƃ��̏���
	void Move3Target(class Object* player);  // �W�I���瓦���鏈��

	void CheckTomatoWall();  // �g�}�g���������s���p�^�[�������s����
	void CollectTomato(TomatoWallManager* object);  // �g�}�g��������ɍs������
	void AvoidTomatoWall(TomatoWallManager* object);    // �g�}�g�̕ǂ�����鏈��

	void RotateTowardTarget(VECTOR& aimTargetPos);  // �W�I����������ɐ��ʂ�������

	void Animation() override;  // �A�j���[�V���������֐�
	void ChangeAnimation() override;  // �A�j���[�V������ύX����֐�
};

