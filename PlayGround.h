#pragma once

// �v���C�V�[�����̏�
class PlayGround :public ModelBase,public Component
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_pos">�|�W�V����</param>
	PlayGround();
	// �f�X�g���N�^
	~PlayGround();

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
	VECTOR m_Pos;   // �|�W�V����
	VECTOR m_Scale; // �g�嗦
};

