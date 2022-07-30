#pragma once

/* エフェクトの制御を行うクラス */
class Effect
{
public:
	// コンストラクタ
	Effect(const char* _SourceEffectHandle);
	// デストラクタ
	~Effect();

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	/// <param name="_EffectPos">エフェクトのポジション </param>
	void PlayEffect(VECTOR _EffectPos);

	/// <summary>
	/// エフェクトが再生中かどうか
	/// </summary>
	/// <returns>0:再生中、-1:再生されていない、もしくは再生終了</returns>
	int GetNowPlaying3D();

private:
	int m_effectHandle;  // エフェクトのハンドル
	int m_playingEffect; // 再生中のエフェクトデータ
};