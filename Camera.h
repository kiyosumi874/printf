#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera(ObjectTag tag, VECTOR position);				// �R���X�g���N�^
	~Camera();				// �f�X�g���N�^

	void Update()override;	// �X�V����.
	void Draw()override;	// �`�揈��.

	// ���߂Ɉ��ĂԃZ�b�^�[
	void SetPlayerptr(class Player* ptr);
private:
	class Player* m_pPlayer;		// �v���C���[��ێ����锠

	VECTOR m_viewPoint;				// �J�����̒����_
	VECTOR m_cameraOffSet;			// �v���C���[����̑��Έʒu
	VECTOR m_targetCameraPosition;	// �J�����ڕW�ʒu
	VECTOR m_targetViewPoint;		// �J�����̒����_�ڕW
};