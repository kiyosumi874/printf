#pragma once
#include <stdexcept>

// ゲームオブジェクト・当たり判定の種類別タグ
// 必要なものはBeginとEndの間に255個まで定義できる

enum class Tag : unsigned char
{
	Begin,			// Tagの開始マーカー（Beginより手前に定義しないこと）

	Player = Begin,
	PlayerBullet,
	Enemy,
	EnemyBullet,
	Ground,
	Camera,
	Effect,

	End				// Tagの終了マーカー（Endより後に定義しないこと）
};

// 前置インクリメント
Tag& operator ++(Tag& rhs);