#pragma once

class Tomato : public GameObject
{
public:
	Tomato(ObjectTag tag, VECTOR position);   // �R���X�g���N�^
	~Tomato();  // �f�X�g���N�^

	void Update();  // �X�V����
	void Draw() override;  // �`�揈��

private:
	void Move();  // ������ꂽ��̏���

	VECTOR m_velocity;  // ���x

	float m_time;     // ��������̌o�ߎ��� 
	float m_gravity;  // �d��
};

