#include "pch.h"

// 静的メンバ変数の初期化
bool HitEffect::m_DrawFlag = false;

HitEffect::HitEffect()
	: m_effectHandle(-1)
	, m_playingEffect(-1)
	, m_DrawPos(VGet(0.0f,0.0f,0.0f))
	, m_Expansion(3.0f)
{
	// エフェクトデータ
	m_effectHandle = LoadEffekseerEffect("data/effect/hit/ToonHit.efkefc", 0.5f);
}

HitEffect::~HitEffect()
{
	// 削除
	DeleteEffekseerEffect(m_effectHandle);
}

void HitEffect::Draw(const VECTOR _EffectPos, const VECTOR _dir)
{
	// エフェクトを再生させ、そのデータをm_playingEffectに代入
	m_playingEffect = PlayEffekseer3DEffect(m_effectHandle);
	// 再生中のエフェクトの位置を設定
	SetPosPlayingEffekseer3DEffect(m_playingEffect, _EffectPos.x, _EffectPos.y, _EffectPos.z);
	// 再生中のエフェクトの角度を設定
	SetRotationPlayingEffekseer3DEffect(m_playingEffect, _dir.x, _dir.y, _dir.z);
	// 再生中のエフェクトの拡大率を設定
	SetScalePlayingEffekseer3DEffect(m_playingEffect, m_Expansion, m_Expansion, m_Expansion);
}

//int HitEffect::GetNowPlaying3D()
//{
//	 エフェクトが再生中かどうかを取得する（-1:再生されてない）
//	return IsEffekseer3DEffectPlaying(m_playingEffect);
//}
