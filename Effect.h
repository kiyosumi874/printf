#pragma once

/* �G�t�F�N�g�̐�����s���N���X */
class Effect
{
public:
	// �R���X�g���N�^
	Effect(const char* _SourceEffectHandle);
	// �f�X�g���N�^
	~Effect();

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="_EffectPos">�G�t�F�N�g�̃|�W�V���� </param>
	void PlayEffect(VECTOR _EffectPos);

	/// <summary>
	/// �G�t�F�N�g���Đ������ǂ���
	/// </summary>
	/// <returns>0:�Đ����A-1:�Đ�����Ă��Ȃ��A�������͍Đ��I��</returns>
	int GetNowPlaying3D();

private:
	int m_effectHandle;  // �G�t�F�N�g�̃n���h��
	int m_playingEffect; // �Đ����̃G�t�F�N�g�f�[�^
};