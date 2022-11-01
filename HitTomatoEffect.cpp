#include "pch.h"
#include "HitTomatoEffect.h"
#include "EffekseerForDXLib.h"

HitTomatoEffect::HitTomatoEffect()
{
}

HitTomatoEffect::~HitTomatoEffect()
{
	// 削除
	DeleteEffekseerEffect(m_effectHandle);
}

void HitTomatoEffect::Init(const char* filePath, const VECTOR& pos, const VECTOR& scale, const VECTOR& rotate)
{
	// エフェクトデータ
	m_effectHandle = LoadEffekseerEffect(filePath, 1.0f);
	m_pos = pos;
	m_scale = scale;
	m_rotate = rotate;
}

void HitTomatoEffect::Start()
{
}

void HitTomatoEffect::Update()
{	
}

void HitTomatoEffect::Draw()
{
}

void HitTomatoEffect::PlayEffect()
{
	// エフェクトを再生させ、そのデータをm_playingEffectに代入
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);
	m_nowPlayFlag = true;
	m_drawFlag = true;
}

void HitTomatoEffect::StopEffect()
{
	StopEffekseer3DEffect(m_playingEffect);
}

void HitTomatoEffect::UpdatePosition(const VECTOR& pos)
{
	m_pos = pos;
	// 再生中のエフェクトの位置を設定
	SetPosPlayingEffekseer3DEffect(m_playingEffect, m_pos.x, m_pos.y, m_pos.z);
}

void HitTomatoEffect::UpdateScale(const VECTOR& scale)
{
	m_scale = scale;
	// 再生中のエフェクトの拡大率を設定
	SetScalePlayingEffekseer3DEffect(m_playingEffect, m_scale.x, m_scale.y, m_scale.z);
}

void HitTomatoEffect::UpdateRotate(const VECTOR& rotate)
{
	m_rotate = rotate;
	// 再生中のエフェクトの角度を設定
	SetRotationPlayingEffekseer3DEffect(m_playingEffect, m_rotate.x, m_rotate.y, m_rotate.z);
}

void HitTomatoEffect::UpdateState(const VECTOR& pos, const VECTOR& scale, const VECTOR& rotate)
{
	m_pos = pos;
	// 再生中のエフェクトの位置を設定
	SetPosPlayingEffekseer3DEffect(m_playingEffect, m_pos.x, m_pos.y, m_pos.z);
	m_scale = scale;
	// 再生中のエフェクトの拡大率を設定
	SetScalePlayingEffekseer3DEffect(m_playingEffect, m_scale.x, m_scale.y, m_scale.z);
	m_rotate = rotate;
	// 再生中のエフェクトの角度を設定
	SetRotationPlayingEffekseer3DEffect(m_playingEffect, m_rotate.x, m_rotate.y, m_rotate.z);
}

int HitTomatoEffect::GetPlayFlag()
{
	int result = IsEffekseer3DEffectPlaying(m_playingEffect);
	return result;
}
