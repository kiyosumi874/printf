#pragma once

/* ���֘A�̃N���X */
class Ground
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	Ground(const VECTOR& _pos);
	// �f�X�g���N�^
	~Ground();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="_deltaTime">�Ō�̃t���[������������̂ɗv��������</param>
	void Update(float _deltaTime);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

private:
	int mModel;    // ���f���f�[�^
};

