#pragma once

/* Hitしたときのフェクトの描画を行うクラス */
class HitEffect
{
public:
	// コンストラクタ
	HitEffect();
	// デストラクタ
	~HitEffect();

	/// <summary>
	/// エフェクトの描画
	/// </summary>
	/// <param name="_EffectPos">エフェクトを描画するポジション</param>
	/// <param name="_dir">エフェクトを描画する向き</param>
	void Draw(const VECTOR _EffectPos,const VECTOR _dir);

	/// <summary>
	/// エフェクトが再生中かどうか
	/// </summary>
	/// <returns>0:再生中、-1:再生されていない、もしくは再生終了</returns>
	//int GetNowPlaying3D();

	static bool m_DrawFlag;     // 描画するかしないか

private:
	int m_effectHandle;  // エフェクトのハンドル
	int m_playingEffect; // 再生中のエフェクトデータ

	VECTOR m_DrawPos;    // 描画ポジション
	float m_Scale;       // エフェクトの拡大率
};