#pragma once
#include "GameObject.h"

class Ground :public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	Ground(ObjectTag tag, VECTOR position);
	// デストラクタ
	~Ground();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="_deltaTime">最後のフレームを完了するのに要した時間</param>
	void Update()override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;
};

