#include "pch.h"

VECTOR HitEffect::m_DrawPos = VGet(0.0f, 0.0f, 0.0f);
bool HitEffect::m_DrawFlag = false;

HitEffect::HitEffect()
	: m_effectHandle(-1)
	, m_playingEffect(-1)
{
	// エフェクト
	m_effectHandle = LoadEffekseerEffect("data/effect/hit/ToonHit.efkefc", 0.5f);
}

HitEffect::~HitEffect()
{
	DeleteEffekseerEffect(m_effectHandle);
}

//void HitEffect::Update(VECTOR _EffectPos)
//{
//	m_DrawPos = _EffectPos;
//	
//	//SetRotationPlayingEffekseer3DEffect(m_playingEffect,0.0f, 0.0f, 90.0f * DX_PI_F / 180.0f);
//}

void HitEffect::Draw()
{
	if (m_DrawFlag)
	{
		m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);

		SetScalePlayingEffekseer3DEffect(m_playingEffect, 1.0f, 1.0f, 1.0f);

		SetPosPlayingEffekseer3DEffect(m_playingEffect, 0.0f, 0.0f, 0.0f);

		m_DrawFlag = false;
	}
}

int HitEffect::GetNowPlaying3D()
{
	return IsEffekseer3DEffectPlaying(m_playingEffect);
}
