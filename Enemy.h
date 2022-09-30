#pragma once
#include "Component.h"

class Tomato;
class TomatoWall;
class ModelManager;

class Enemy : public Component
{
public:
	Enemy();				// �R���X�g���N�^
	~Enemy();				// �f�X�g���N�^

	void Start()override;	// �R���|�[�l���g����������.
	void Update()override;	// �X�V����.
	void Draw()override;	// �`�揈��.

	void SetPlayerPtr(class Object* player);  // Enemy�Ɍ�������Player���Z�b�g
	void SetTomatoWallPtr(TomatoWall* tomatoWall);  // Enemy�Ɍ�������TomatoWall���Z�b�g
private:
	void ProcessTomato();

	enum Type
	{
		SearchTarget,   // �^�[�Q�b�g��T��
		AimTarget,      // �^�[�Q�b�g��_��
		EscapeTarget,   // �^�[�Q�b�g���瓦����
		TomatoCollect,  // �g�}�g��������ɍs��
	};

	enum Anim
	{
		None = -1,  // �������Ȃ�
		Idle,  // �~�܂�
		Run,   // ����
		Throw,  // ������
		Pick,  // �E��
	};

	// ���f���n���h��
	int m_modelHandle;

	// �A�j���[�V�����ϐ�
	int m_animType;  // ���݂̃A�j���[�V����������
	int m_beforeAnimType;  // �O�̃A�j���[�V����
	int m_animIndex;  // ���݂̃A�j���[�V�������L�^
	float m_animTime;  // �A�j���[�V�����̌o�ߎ���
	float m_animTotalTime;  // �A�j���[�V�����̑�����
	float m_animSpeed;  // ��̃A�j���[�V�����X�s�[�h
	float m_throwSpeed;  // ������X�s�[�h(�␳��������)
	float m_pickSpeed;  // �E���X�s�[�h(�␳��������)

	// �G�l�~�[�̃p�����[�^�[
	VECTOR m_position;	// �ʒu���W

	VECTOR m_dir;       // ����
	VECTOR m_tomatoDir;  // �g�}�g�𓊂������

	VECTOR m_velocity;  // �ړ���
	VECTOR m_randomVelocity;  // �����ړ���
	VECTOR m_avoidVelocity;  // �������

	VECTOR m_speed;  // �ʏ�ړ����x
	VECTOR m_adjustmentSpeed;  // �����X�s�[�h
	VECTOR m_avoidSpeed;  // �����鑬�x

	int m_bulletNum;  // ���̏����e��
	const int m_bulletCapacity; // ���̌��E������

	// ���쎞��
	int m_moveTime;  // �����s������
	const int m_movePhaseTime;  // ���̍s���Ɉڂ鎞��
	float m_shotTime;   // �����鎞��
	const float m_shotPhaseTime;  // ��������̃N�[������

	// �t���O�ϐ�
	int m_moveType;  // ���̍s��
	bool m_moveFlag;  // �����Ă��邩
	bool m_pickFlag;  // �g�}�g���E������
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
	std::vector<class Object*> m_player;  // �G�l�~�[�N���X�ɂɏ���n�������v���C���[
	std::vector<TomatoWall*> m_tomatoWall;  // �g�}�g�̕ǃI�u�W�F�N�g���i�[����
	class Icon* m_icon;  // �A�C�R���N���X

	// �֐�
	void CheckMovePattern();  // �s���p�^�[�����`�F�b�N���Ď��s����

	void CheckTargetMovePattern();  // �^�[�Q�b�g�ɑ΂��Ă̍s���p�^�[�������s����
	void Move1Target(class Object* player);  // �W�I�ɍ��킹�ē�������
	void Move2Target(class Object* player);  // �W�I�����Ȃ��Ƃ��̏���
	void Move3Target(class Object* player);  // �W�I���瓦���鏈��

	void CheckTomatoWall();  // �g�}�g���������s���p�^�[�������s����
	void CollectTomato(TomatoWall* object);  // �g�}�g��������ɍs������
	void AvoidTomatoWall(TomatoWall* object);    // �g�}�g�̕ǂ�����鏈��

	void RotateTowardTarget(VECTOR& aimTargetPos);  // �W�I����������ɐ��ʂ�������

	void Animation();  // �A�j���[�V���������֐�
	void ChangeAnimation();  // �A�j���[�V������ύX����֐�

	double GetDistance(VECTOR& pos1, VECTOR& pos2);  // ���g�Ƒ��̃I�u�W�F�N�g�̋������o��
	float GetSize(float v1, float v2);
};

