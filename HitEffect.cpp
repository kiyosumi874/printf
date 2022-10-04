#include "pch.h"

// �ÓI�����o�ϐ��̏�����
bool HitEffect::m_DrawFlag = false;

HitEffect::HitEffect()
	: m_effectHandle(-1)
	, m_playingEffect(-1)
	, m_DrawPos(VGet(0.0f,0.0f,0.0f))
	, m_Expansion(3.0f)
{
	// �G�t�F�N�g�f�[�^
	m_effectHandle = LoadEffekseerEffect("data/effect/hit/ToonHit.efkefc", 0.5f);
}

HitEffect::~HitEffect()
{
	// �폜
	DeleteEffekseerEffect(m_effectHandle);
}

void HitEffect::Draw(const VECTOR _EffectPos, const VECTOR _dir)
{
	// �G�t�F�N�g���Đ������A���̃f�[�^��m_playingEffect�ɑ��
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);
	// �Đ����̃G�t�F�N�g�̈ʒu��ݒ�
	SetPosPlayingEffekseer3DEffect(m_playingEffect, _EffectPos.x, _EffectPos.y, _EffectPos.z);
	// �Đ����̃G�t�F�N�g�̊p�x��ݒ�
	SetRotationPlayingEffekseer3DEffect(m_playingEffect, _dir.x, _dir.y, _dir.z);
	// �Đ����̃G�t�F�N�g�̊g�嗦��ݒ�
	SetScalePlayingEffekseer3DEffect(m_playingEffect, m_Expansion, m_Expansion, m_Expansion);
}

//int HitEffect::GetNowPlaying3D()
//{
//	 �G�t�F�N�g���Đ������ǂ������擾����i-1:�Đ�����ĂȂ��j
//	return IsEffekseer3DEffectPlaying(m_playingEffect);
//}
