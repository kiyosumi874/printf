#pragma once

/* Hit�����Ƃ��̃t�F�N�g�̕`����s���N���X */
class HitEffect
{
public:
	// �R���X�g���N�^
	HitEffect();
	// �f�X�g���N�^
	~HitEffect();

	/// <summary>
	/// �G�t�F�N�g�̕`��
	/// </summary>
	/// <param name="_EffectPos">�G�t�F�N�g��`�悷��|�W�V����</param>
	/// <param name="_dir">�G�t�F�N�g��`�悷�����</param>
	void Draw(const VECTOR _EffectPos,const VECTOR _dir);

	/// <summary>
	/// �G�t�F�N�g���Đ������ǂ���
	/// </summary>
	/// <returns>0:�Đ����A-1:�Đ�����Ă��Ȃ��A�������͍Đ��I��</returns>
	//int GetNowPlaying3D();

	static bool m_DrawFlag;     // �`�悷�邩���Ȃ���

private:
	int m_effectHandle;  // �G�t�F�N�g�̃n���h��
	int m_playingEffect; // �Đ����̃G�t�F�N�g�f�[�^

	VECTOR m_DrawPos;    // �`��|�W�V����
	float m_Scale;       // �G�t�F�N�g�̊g�嗦
};