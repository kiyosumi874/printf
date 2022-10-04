#pragma once
#include "Component.h"

class Image : public Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Image();
	// デストラクタ
	~Image();

	/// <param name="pos">グローバル座標(xとyだけ)</param>
    /// <param name="extendRate">拡大率(xとyだけ)</param>
    /// <param name="angle">角度(度数法)</param>
    /// <param name="fileName">画像のパス</param>
    /// <param name="transFlag">画像の透明度を有効にするかどうか</param>
    /// <param name="turnFlagX">画像の左右反転を行うか</param>
    /// <param name="turnFlagY">画像の上下反転を行うか</param>
	void Init(const VECTOR& pos, const VECTOR& extendRate, double angle, const char* fileName, bool transFlag = true, bool turnFlagX = false, bool turnFlagY = false);

	void Update()override;	// 更新処理
	void Draw()override;	// 描画処理

	/// <summary>
	/// 自分を回す
	/// </summary> 
	/// <param name="angle">角度(度数法)</param>
	/// 概要：一回呼ぶだけで回り続けるよ,引数に0.0を入れると止まる
	/// 例  ：引数に1.0と入れた場合1ループに1.0度ずつ回ります。
	void Rotation(double angle)
	{
		m_addAngle = angle * DX_PI / 180.0;
	}

	/// <summary>
	/// 自分の角度を設定
	/// </summary>
	/// <param name="angle">角度(度数法)</param>
	void SetAngle(double angle)
	{
		m_angle = angle * DX_PI / 180.0;
	}

	/// <summary>
	/// 自分のグローバル座標を変更
	/// </summary>
	/// <param name="pos">座標(xとyだけ)</param>
	void SetPos(const VECTOR& pos)
	{
		m_pos = pos;
	}

	// 座標のゲッター
	const VECTOR& GetPos() const
	{
		return m_pos;
	}

	// 画像を動かす
	void MovePos(const VECTOR& pos)
	{
		m_pos.x += pos.x;
		m_pos.y += pos.y;
		m_pos.z += pos.z;
	}

	/// <summary>
	/// 自分の拡大率を変更
	/// </summary>
	/// <param name="extendRate">拡大率(xとyだけ)</param>
	void SetExtendRate(const VECTOR& extendRate)
	{
		m_extendRate = extendRate;
	}

	// 描画するか否か
	void IsDraw(bool isDraw)
	{
		m_isDraw = isDraw;
	}

	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

private:
	VECTOR m_pos;        // グローバル座標
	VECTOR m_extendRate; // 拡大率
	double m_angle;      // 角度(弧度法)
	double m_addAngle;   // 回転させる角度(弧度法)
	int m_graphHandle;   // 画像ハンドル
	int m_alpha;
	bool m_transFlag;    // 画像の透明度を有効にするかどうか
	bool m_turnFlagX;    // 画像の左右反転を行うか
	bool m_turnFlagY;    // 画像の上下反転を行うか
	bool m_isDraw;       // 描画するか？
};
