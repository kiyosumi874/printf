#pragma once
#include "GameObject.h"
class Ground2 :public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	Ground2(ObjectTag tag, VECTOR position);
	// �f�X�g���N�^
	~Ground2();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void Update()override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;
};

