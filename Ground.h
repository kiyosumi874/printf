#pragma once

/* 床関連のクラス */
class Ground
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	Ground(const VECTOR& _pos);
	// デストラクタ
	~Ground();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void Update(float _deltaTime);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	int mModel;    // モデルデータ
};

