#include "pch.h"
//
//bool Effect::m_EffectDrawFlag = false;
//VECTOR Effect::m_EffectPos = VGet(0.0f, 0.0f, 0.0f);
//
//EffectManager::EffectManager()
//	: m_effectHandle(-1)
//	, m_playingEffect(-1)
//{
//	// エフェクト
//	m_effectHandle = LoadEffekseerEffect("data/effect/hit/ToonHit.efkefc", 0.5f);
//}
//
//EffectManager::~EffectManager()
//{
//	DeleteEffekseerEffect(m_effectHandle);
//}
//
//void EffectManager::PlayEffect()
//{
//	if (m_EffectDrawFlag)
//	{
//		m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);
//
//		SetScalePlayingEffekseer3DEffect(m_playingEffect, 1.0f, 1.0f, 1.0f);
//
//		SetPosPlayingEffekseer3DEffect(m_playingEffect, m_EffectPos.x, m_EffectPos.y, m_EffectPos.z);
//	}
//
//	if (GetNowPlaying3D() == -1)
//	{
//		m_EffectDrawFlag = false;
//	}
//
//	//SetRotationPlayingEffekseer3DEffect(m_playingEffect,0.0f, 0.0f, 90.0f * DX_PI_F / 180.0f);
//}
//
//int EffectManager::GetNowPlaying3D()
//{
//	return IsEffekseer3DEffectPlaying(m_playingEffect);
//}
