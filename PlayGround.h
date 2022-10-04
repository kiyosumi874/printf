#pragma once

// プレイシーン時の床
class PlayGround :public ModelBase,public Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	PlayGround();
	// デストラクタ
	~PlayGround();

	void Start()override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

private:
	VECTOR m_Pos;   // ポジション
	VECTOR m_Scale; // 拡大率
};

