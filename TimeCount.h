//----------------------------------------
// @file TimeCount.h
// @brief ���Ԃ��v������
// @author shiihara_kiyosumi
// @date 2022_09_01
//----------------------------------------

// ���d�C���N���[�h�h�~
#pragma once
// �w�b�_�[�t�@�C���̃C���N���[�h
#include "Component.h"
#include <chrono>

// using�錾
using std::chrono::system_clock;

class TimeCount : public Component
{
public:
	// �R���X�g���N�^
	TimeCount();
	// �f�X�g���N�^
	~TimeCount();

	// �X�V
	void Update() override;

	// �J�E���g���J�n����
	void StartCount();

	// �x�e
	void RestCount();

	bool CheckIsCount();

	// �J�E���g���m�F����
	double CheckCount();

private:
	system_clock::time_point m_start; // �J�E���g���J�n��������
	system_clock::time_point m_end; // ���̃J�E���g����

	bool m_isCount; // �J�E���g�����邩�ۂ�
};