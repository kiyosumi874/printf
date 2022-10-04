#pragma once
#include "Component.h"

class Tomato : public ModelBase, public Component
{
public:
	Tomato();   // �R���X�g���N�^
	~Tomato();  // �f�X�g���N�^

	void Start();
	void Update();  // �X�V����
	void Draw();  // �`�揈��

	// �K���ĂԂ���
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
	void ShotTomato(const VECTOR& pos, const VECTOR& dir, class Tag* tag) { m_dir = dir; m_tag = tag; }  // �g�}�g���΂�����

	float GetTime();  // �g�}�g�𓊂��Ă���̎��Ԃ�Ԃ�
	VECTOR GetPosition() { return m_var.pos; }
	VECTOR GetDir() { return m_dir; }

	class Tag* GetTag() { return m_tag; }
private:
	void Move();  // ������ꂽ��̏���

	class Transform* m_pTransform;
	class Tag* m_tag;
	VECTOR m_velocity;  // ���x
	VECTOR m_startVelocity;  // ����
	VECTOR m_dir;  // ���������

	float m_time;     // ��������̌o�ߎ��� 
	float m_gravity;  // �d��
	float m_deg;      // ���x��
	float m_rad;      // ���W�A��
};

