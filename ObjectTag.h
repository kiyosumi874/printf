#pragma once
#include <vector>

// ゲームオブジェクト・当たり判定の種類別タグ
// 必要なものはBeginとEndの間に255個まで定義できる
enum class ObjectTag : unsigned char
{
	Begin,			// Tagの開始マーカー（Beginより手前に定義しないこと）

	Team1 = Begin,
	Player1Bullet,
	Team2,
	Player2Bullet,
	Team3,
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
	ObjectTag::Team1,
	ObjectTag::Player1Bullet,
	ObjectTag::Team2,
	ObjectTag::Player2Bullet,
	ObjectTag::Team3,
	ObjectTag::EnemyBullet,
	ObjectTag::TomatoWall,
	ObjectTag::Ground,
	ObjectTag::Camera1,
	ObjectTag::Camera2,
	ObjectTag::Effect
};