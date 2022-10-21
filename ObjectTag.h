#pragma once
#include <vector>

// ゲームオブジェクト・当たり判定の種類別タグ
// 必要なものはBeginとEndの間に255個まで定義できる
enum class ObjectTag : unsigned char
{
	Begin,			// Tagの開始マーカー（Beginより手前に定義しないこと）

	Team1 = Begin,
	Team2,
	Team3,
	Team1Tomato,
	Team2Tomato,
	Team3Tomato,
	TomatoWall,
	Ground,
	Camera1,
	Camera2,
	Effect,
	World,
	Debug,

	End				// Tagの終了マーカー（Endより後に定義しないこと）
};

// for( ObjectTag &tag : ObjectTagAll )で全Tag要素のループにできる
constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Team1,
	ObjectTag::Team2,
	ObjectTag::Team3,
	ObjectTag::Team1Tomato,
	ObjectTag::Team2Tomato,
	ObjectTag::Team3Tomato,
	ObjectTag::TomatoWall,
	ObjectTag::Ground,
	ObjectTag::Camera1,
	ObjectTag::Camera2,
	ObjectTag::Effect,
	ObjectTag::World,
	ObjectTag::Debug,
};