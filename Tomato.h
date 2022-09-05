#pragma once
#include "Component.h"

class Tomato : public Component
{
public:
	Tomato(VECTOR& position, VECTOR& dir);   // �R���X�g���N�^
	~Tomato();  // �f�X�g���N�^

	void Update();  // �X�V����
	void Draw();  // �`�揈��

	float GetTime();  // �g�}�g�𓊂��Ă���̎��Ԃ�Ԃ�
	VECTOR GetPosition() { return m_position; }
private:
	void Move();  // ������ꂽ��̏���

	int m_modelHandle;

	VECTOR m_position;
	VECTOR m_velocity;  // ���x
	VECTOR m_startVelocity;  // ����
	VECTOR m_dir;  // ���������

	float m_time;     // ��������̌o�ߎ��� 
	float m_gravity;  // �d��
	float m_deg;      // ���x��
	float m_rad;      // ���W�A��
};

