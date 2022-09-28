#pragma once
#include "Component.h"

class StillProjector : public Component
{
public:
	StillProjector();				// �R���X�g���N�^
	~StillProjector();				// �f�X�g���N�^

	void Start();
	void Update()override;	// �X�V����.
	void Draw();
private:
	class Transform* m_pPlayerTransform;		// �v���C���[��ێ����锠

	VECTOR m_position;				// ���W
	VECTOR m_viewPoint;				// �J�����̒����_
	VECTOR m_targetViewPoint;		// �J�����̒����_�ڕW
};