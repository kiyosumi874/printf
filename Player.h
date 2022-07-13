#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(ObjectTag tag, VECTOR position);				// �R���X�g���N�^
	~Player();				// �f�X�g���N�^

	void Update();			// �X�V����.
	void Draw()override;	// �`�揈��.

private:
	void Input();			// ���͈ړ�����.
	void Rotate();			// ��]����.

	VECTOR m_dir;			// ����
	VECTOR m_aimDir;		// �ڕW����
	VECTOR m_velocity;		// ���x

	bool m_rotateNow;		// ��]��������p
};
