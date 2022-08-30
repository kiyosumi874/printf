#pragma once
#include "Component.h"

class Projector : public Component
{
public:
	Projector();				// �R���X�g���N�^
	~Projector();				// �f�X�g���N�^

	void Update()override;	// �X�V����.

	// ���߂Ɉ��ĂԃZ�b�^�[
	void SetPlayerptr(class Transform* ptr);
private:
	class Transform* m_pPlayerTransform;		// �v���C���[��ێ����锠

	VECTOR m_position;				// ���W
	VECTOR m_viewPoint;				// �J�����̒����_
	VECTOR m_targetViewPoint;		// �J�����̒����_�ڕW
};