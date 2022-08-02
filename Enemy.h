#pragma once
#include "GameObject.h"

class Tomato;

class Enemy : public GameObject
{
public:
	Enemy(ObjectTag tag, VECTOR position);				// �R���X�g���N�^
	~Enemy();				// �f�X�g���N�^

	void Update()override;	// �X�V����.
	void Draw()override;	// �`�揈��.

	void SetGameObjectPtr(GameObject* object);  // Enemy�Ɍ�������GameObject���Z�b�g
private:
	void ProcessTomato();

	int m_moveTime;  // �����s������
	float m_shotTime;   // �g�}�g�𓊂��鎞��

	const int m_movePhaseTime;  // ���̍s���Ɉڂ鎞��

	VECTOR m_velocity;  // �ړ��X�s�[�h
	VECTOR m_dir;       // ����
	VECTOR m_tomatoDir;  // �g�}�g�𓊂������
	VECTOR m_moveValue;  // �����ړ���

	bool m_targetFoundFlag;  // �W�I�𔭌�������
	bool m_aimTargetFlag;  // �W�I�Ɍ����Ĉړ����邩

	std::vector<GameObject*> m_objects;  // �G�l�~�[�N���X�ɂɏ���n�������I�u�W�F�N�g

	std::vector<Tomato*> m_tomatos;  // �������g�}�g���m��

	void Move1(GameObject* object);  // �W�I�ɍ��킹�ē�������
	void Move2(GameObject* object);  // �W�I�����Ȃ��Ƃ��̏���
	void Move3(GameObject* object);  // ���̑�
	void RotateTowardTarget(VECTOR& aimTargetPos);  // �W�I����������ɐ��ʂ�������

	double GetDistance(VECTOR& pos1, VECTOR& pos2);  // ���g�Ƒ��̃I�u�W�F�N�g�̋������o��
};

