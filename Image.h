#pragma once
#include "Component.h"

class Image : public Component
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Image();
	// �f�X�g���N�^
	~Image();

	/// <param name="pos">�O���[�o�����W(x��y����)</param>
    /// <param name="extendRate">�g�嗦(x��y����)</param>
    /// <param name="angle">�p�x(�x���@)</param>
    /// <param name="fileName">�摜�̃p�X</param>
    /// <param name="transFlag">�摜�̓����x��L���ɂ��邩�ǂ���</param>
    /// <param name="turnFlagX">�摜�̍��E���]���s����</param>
    /// <param name="turnFlagY">�摜�̏㉺���]���s����</param>
	void Init(const VECTOR& pos, const VECTOR& extendRate, double angle, const char* fileName, bool transFlag = true, bool turnFlagX = false, bool turnFlagY = false);

	void Update()override;	// �X�V����
	void Draw()override;	// �`�揈��

	/// <summary>
	/// ��������
	/// </summary> 
	/// <param name="angle">�p�x(�x���@)</param>
	/// �T�v�F���ĂԂ����ŉ�葱�����,������0.0������Ǝ~�܂�
	/// ��  �F������1.0�Ɠ��ꂽ�ꍇ1���[�v��1.0�x�����܂��B
	void Rotation(double angle)
	{
		m_addAngle = angle * DX_PI / 180.0;
	}

	/// <summary>
	/// �����̊p�x��ݒ�
	/// </summary>
	/// <param name="angle">�p�x(�x���@)</param>
	void SetAngle(double angle)
	{
		m_angle = angle * DX_PI / 180.0;
	}

	/// <summary>
	/// �����̃O���[�o�����W��ύX
	/// </summary>
	/// <param name="pos">���W(x��y����)</param>
	void SetPos(const VECTOR& pos)
	{
		m_pos = pos;
	}

	/// <summary>
	/// �����̊g�嗦��ύX
	/// </summary>
	/// <param name="extendRate">�g�嗦(x��y����)</param>
	void SetExtendRate(const VECTOR& extendRate)
	{
		m_extendRate = extendRate;
	}

	// �`�悷�邩�ۂ�
	void IsDraw(bool isDraw)
	{
		m_isDraw = isDraw;
	}

private:
	VECTOR m_pos;        // �O���[�o�����W
	VECTOR m_extendRate; // �g�嗦
	double m_angle;      // �p�x(�ʓx�@)
	double m_addAngle;   // ��]������p�x(�ʓx�@)
	int m_graphHandle;   // �摜�n���h��
	bool m_transFlag;    // �摜�̓����x��L���ɂ��邩�ǂ���
	bool m_turnFlagX;    // �摜�̍��E���]���s����
	bool m_turnFlagY;    // �摜�̏㉺���]���s����
	bool m_isDraw;       // �`�悷�邩�H
};
