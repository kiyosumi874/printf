#pragma once
#include "GameObject.h"

class Tomato;

class Player : public GameObject
{
public:
	Player(ObjectTag tag, VECTOR position);				// �R���X�g���N�^
	~Player();				// �f�X�g���N�^

	void Update()override;	// �X�V����.
	void Draw()override;	// �`�揈��.

	// �Q�b�^�[
	const float& GetAngle() const { return m_angle; }
private:
	void Input();			// ���͈ړ�����.
	void Rotate();			// ��]����.

	VECTOR m_dir;			// ����
	VECTOR m_aimDir;		// �ڕW����
	VECTOR m_velocity;		// ���x

	float m_angle;			//	���_��]�p�x

	bool m_rotateNow;		// ��]��������p

	std::vector<Tomato*> m_tomatos;
};
