#pragma once
//#include "GameObject.h"
#include "Component.h"

class Ground :public Component
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	Ground(/*ObjectTag tag, VECTOR position*/);
	// �f�X�g���N�^
	~Ground();

	void Start()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void Update()override;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw()override;


private:
	int m_modelHandle;
};

