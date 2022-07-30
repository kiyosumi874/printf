#include "pch.h"

Effect::Effect(const char* _SourceEffectHandle)
	: m_effectHandle(-1)
	, m_playingEffect(-1)
{
	m_effectHandle = LoadEffekseerEffect(_SourceEffectHandle, 1.5);
}

Effect::~Effect()
{
	DeleteEffekseerEffect(m_effectHandle);
}

void Effect::PlayEffect(VECTOR _EffectPos)
{
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);

	SetScalePlayingEffekseer3DEffect(m_playingEffect, 1.0f,1.0f,1.0f);

	SetPosPlayingEffekseer3DEffect(m_playingEffect, _EffectPos.x, _EffectPos.y, _EffectPos.z);

	//SetRotationPlayingEffekseer3DEffect(m_playingEffect,0.0f, 0.0f, 90.0f * DX_PI_F / 180.0f);
}

int Effect::GetNowPlaying3D()
{
	return IsEffekseer3DEffectPlaying(m_playingEffect);
}
