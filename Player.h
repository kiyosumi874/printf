#pragma once
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();			// �R���X�g���N�^
	~Player()override;	// �f�X�g���N�^

	void Update();			// �X�V����
	void Draw()override;	// �`�揈��

private:
	int m_playerModelHandle;	// 
};