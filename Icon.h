#pragma once
#include "Component.h"

class Tag;

class Icon : public Component
{
public:
	Icon(Tag* tag);   // �R���X�g���N�^
	~Icon();  // �f�X�g���N�^

	void Init(VECTOR& position);  // �ʒu�ƖڕW����
	void Update(VECTOR& position);  // �X�V����
	void Draw();  // �`�揈��

	void Animation();

private:
	int m_modelHandle;  // �A�C�R���̃��f��

	VECTOR m_correctionVector;  // �ʒu�̕␳�p

	int m_animIndex;  // ���݂̃A�j���[�V�������L�^
	float m_animTime;  // �A�j���[�V�����̌o�ߎ���
	float m_animTotalTime;  // �A�j���[�V�����̑�����
	float m_animSpeed;  // ��̃A�j���[�V�����X�s�[�h

	bool m_noIconFlag;  // �A�C�R�����K�v�Ȃ��I�u�W�F�N�g�����ăo�O��Ȃ��悤��
};

