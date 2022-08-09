#pragma once
#include "GameObject.h"

class Tomato;
class Effct;
class ModelManager;

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

	void ChangeAnimation();  // �A�j���[�V�����ύX����

	VECTOR m_dir;			// ����
	VECTOR m_aimDir;		// �ڕW����
	VECTOR m_velocity;		// ���x

	float m_angle;			//	���_��]�p�x

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

	std::vector<Tomato*> m_tomatos;
	Effect* m_effect;
};
