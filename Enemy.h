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
	float m_shotTime;  // �g�}�g�𓊂��鎞��

	VECTOR m_dir;      // ����

	std::vector<GameObject*> m_objects;

	std::vector<Tomato*> m_tomatos;

	void Move1(GameObject* object);  // �v���C���[�ɍ��킹�ē�������
	void Move2(GameObject* object);  
	void Move3(GameObject* object);

	double GetDistance(VECTOR& pos1, VECTOR& pos2);  // ���g�Ƒ��̃I�u�W�F�N�g�̋������o��
};

