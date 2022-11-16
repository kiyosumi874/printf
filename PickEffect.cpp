#include "pch.h"
#include "PickEffect.h"

PickEffect::PickEffect()
{
}

PickEffect::~PickEffect()
{
	// �폜
	DeleteEffekseerEffect(m_effectHandle);
}

void PickEffect::Init(const char* filePath, const VECTOR& pos, const VECTOR& scale, const VECTOR& rotate)
{
	// �G�t�F�N�g�f�[�^
	m_effectHandle = LoadEffekseerEffect(filePath, 1.0f);
	m_pos = pos;
	m_scale = scale;
	m_rotate = rotate;
}

void PickEffect::Start()
{
}

void PickEffect::Update()
{
}

void PickEffect::Draw()
{
}

void PickEffect::PlayEffect()
{
	// �G�t�F�N�g���Đ������A���̃f�[�^��m_playingEffect�ɑ��
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);
	m_nowPlayFlag = true;
	m_drawFlag = true;
}

void PickEffect::StopEffect()
{
	StopEffekseer3DEffect(m_playingEffect);
}

void PickEffect::UpdatePosition(const VECTOR& pos)
{
	m_pos = pos;
	// �Đ����̃G�t�F�N�g�̈ʒu��ݒ�
	SetPosPlayingEffekseer3DEffect(m_playingEffect, m_pos.x, m_pos.y, m_pos.z);
}

void PickEffect::UpdateScale(const VECTOR& scale)
{
	m_scale = scale;
	// �Đ����̃G�t�F�N�g�̊g�嗦��ݒ�
	SetScalePlayingEffekseer3DEffect(m_playingEffect, m_scale.x, m_scale.y, m_scale.z);
}

void PickEffect::UpdateRotate(const VECTOR& rotate)
{
	m_rotate = rotate;
	// �Đ����̃G�t�F�N�g�̊p�x��ݒ�
	SetRotationPlayingEffekseer3DEffect(m_playingEffect, m_rotate.x, m_rotate.y, m_rotate.z);
}

void PickEffect::UpdateState(const VECTOR& pos, const VECTOR& scale, const VECTOR& rotate)
{
	m_pos = pos;
	// �Đ����̃G�t�F�N�g�̈ʒu��ݒ�
	SetPosPlayingEffekseer3DEffect(m_playingEffect, m_pos.x, m_pos.y, m_pos.z);
	m_scale = scale;
	// �Đ����̃G�t�F�N�g�̊g�嗦��ݒ�
	SetScalePlayingEffekseer3DEffect(m_playingEffect, m_scale.x, m_scale.y, m_scale.z);
	m_rotate = rotate;
	// �Đ����̃G�t�F�N�g�̊p�x��ݒ�
	SetRotationPlayingEffekseer3DEffect(m_playingEffect, m_rotate.x, m_rotate.y, m_rotate.z);
}

int PickEffect::GetPlayFlag()
{
	int result = IsEffekseer3DEffectPlaying(m_playingEffect);
	return result;
}
