#pragma once
#include <vector>

// ゲームオブジェクト・当たり判定の種類別タグ
// 必要なものはBeginとEndの間に255個まで定義できる
enum class ObjectTag : unsigned char
{
	Begin,			// Tagの開始マーカー（Beginより手前に定義しないこと）

	Player1 = Begin,
	Player1Bullet,
	Player2,
	Player2Bullet,
	Enemy,
	EnemyBullet,
	tomato,
	TomatoWall,
	Ground,
	Camera1,
	Camera2,
	Effect,

	End				// Tagの終了マーカー（Endより後に定義しないこと）
};

// for( ObjectTag &tag : ObjectTagAll )で全Tag要素のループにできる
constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player1,
	ObjectTag::Player1Bullet,
	ObjectTag::Player2,
	ObjectTag::Player2Bullet,
	ObjectTag::Enemy,
	ObjectTag::EnemyBullet,
	ObjectTag::TomatoWall,
	ObjectTag::Ground,
	ObjectTag::Camera1,
	ObjectTag::Camera2,
	ObjectTag::Effect
};