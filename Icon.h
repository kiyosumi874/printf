#pragma once
#include "ModelBase.h"
#include "Component.h"

class Icon : public ModelBase, public Component
{
public:
	Icon(class Tag* tag);   // �R���X�g���N�^
	~Icon();  // �f�X�g���N�^

	void Update(VECTOR& position);  // �X�V����
	void Draw();  // �`�揈��

	// �K���ĂԂ���
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);

	void Animation();


private:
	VECTOR m_correctionVector;  // �ʒu�̕␳�p
	class Tag* m_pTag;

	int m_animIndex;  // ���݂̃A�j���[�V�������L�^
	float m_animTime;  // �A�j���[�V�����̌o�ߎ���
	float m_animTotalTime;  // �A�j���[�V�����̑�����
	float m_animSpeed;  // ��̃A�j���[�V�����X�s�[�h

	bool m_noIconFlag;  // �A�C�R�����K�v�Ȃ��I�u�W�F�N�g�����ăo�O��Ȃ��悤��
};

