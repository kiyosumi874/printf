#pragma once

/* Hitしたときのフェクトの描画を行うクラス */
class HitEffect
{
public:
	// コンストラクタ
	HitEffect();
	// デストラクタ
	~HitEffect();

	///// <summary>
	///// エフェクトの更新
	///// </summary>
	///// <param name="_EffectPos">エフェクトのポジション </param>
	//void Update(VECTOR _EffectPos);

	/// <summary>
	/// エフェクトの描画
	/// </summary>
	void Draw();

	/// <summary>
	/// エフェクトが再生中かどうか
	/// </summary>
	/// <returns>0:再生中、-1:再生されていない、もしくは再生終了</returns>
	int GetNowPlaying3D();

	static VECTOR m_DrawPos;    // 描画ポジション
	static bool m_DrawFlag;     // 描画するかしないか

private:

	int m_effectHandle;  // エフェクトのハンドル
	int m_playingEffect; // 再生中のエフェクトデータ

};