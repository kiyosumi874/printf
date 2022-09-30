#pragma once
#include "GameObject.h"

class TomatoWall : public GameObject
{
public:
	TomatoWall(ObjectTag tag, VECTOR position);  // コンストラクタ
	~TomatoWall();  // デストラクタ

	void Update() override;  // 更新処理
	void Draw() override;    // 描画処理

	void DecreaseAllTomatoNum() { m_allTomatoNum = m_allTomatoNum - 1; }  // 山のトマトの数を減らす(相手側から読んでもらう)

	// Getter
	int GetAllTomatoNum() { return m_allTomatoNum; }
	float GetWidthDistance() { return m_width; } 
private:
	VECTOR m_size;  // トマトの山の範囲
	const int m_modelPattern = 5;  // モデルの数
	int m_modelPatternIndex;  // 今現在のモデル番号
	int m_modelPatternHandle[5];  // モデルデータ
	const int m_modelChangeNum[4];  // モデルを変えるトマトの数

	int m_allTomatoNum;  // トマトの山のトマトの総数
	int m_time;  // トマトの山がなくなった後の時間
	const int m_revivalTime;  // トマトの山が復活するまでも時間

	const float m_width = 20.0f;  // 自分の幅
};

