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

void HitEffect::Update(const VECTOR _EffectPos, const VECTOR _dir)
{
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);
	SetRotationPlayingEffekseer3DEffect(m_playingEffect, _dir.x, _dir.y, _dir.z);

	SetScalePlayingEffekseer3DEffect(m_playingEffect, 3.0f, 3.0f, 3.0f);

	SetPosPlayingEffekseer3DEffect(m_playingEffect, _EffectPos.x, _EffectPos.y, _EffectPos.z);

	m_DrawFlag = false;
}

void HitEffect::Draw()
{
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);

	SetScalePlayingEffekseer3DEffect(m_playingEffect, 1.0f, 1.0f, 1.0f);

	SetPosPlayingEffekseer3DEffect(m_playingEffect, m_DrawPos.x, m_DrawPos.y, m_DrawPos.z);

	m_DrawFlag = false;
}

int HitEffect::GetNowPlaying3D()
{
	return IsEffekseer3DEffectPlaying(m_playingEffect);
}
