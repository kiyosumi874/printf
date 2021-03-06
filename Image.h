#pragma once

class Image
{
public:
	// デフォルトコンストラクタは使わないのでdelete
	Image() = delete;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="pos">グローバル座標(xとyだけ)</param>
	/// <param name="extendRate">拡大率(xとyだけ)</param>
	/// <param name="angle">角度(度数法)</param>
	/// <param name="fileName">画像のパス</param>
	/// <param name="transFlag">画像の透明度を有効にするかどうか</param>
	/// <param name="turnFlagX">画像の左右反転を行うか</param>
	/// <param name="turnFlagY">画像の上下反転を行うか</param>
	Image(const VECTOR& pos, const VECTOR& extendRate, double angle, const char* fileName, bool transFlag = true, bool turnFlagX = false, bool turnFlagY = false);
	// デストラクタ
	~Image();

	void Update();	// 更新処理
	void Draw();	// 描画処理

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

	/// <summary>
	/// 自分の拡大率を変更
	/// </summary>
	/// <param name="extendRate">拡大率(xとyだけ)</param>
	void SetExtendRate(const VECTOR& extendRate)
	{
		m_extendRate = extendRate;
	}

private:
	VECTOR m_pos;        // グローバル座標
	VECTOR m_extendRate; // 拡大率
	double m_angle;      // 角度(弧度法)
	double m_addAngle;   // 回転させる角度(弧度法)
	int m_graphHandle;   // 画像ハンドル
	bool m_transFlag;    // 画像の透明度を有効にするかどうか
	bool m_turnFlagX;    // 画像の左右反転を行うか
	bool m_turnFlagY;    // 画像の上下反転を行うか
};
