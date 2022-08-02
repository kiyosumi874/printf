#pragma once
#include "GameObject.h"

class Tomato;

class Enemy : public GameObject
{
public:
	Enemy(ObjectTag tag, VECTOR position);				// コンストラクタ
	~Enemy();				// デストラクタ

	void Update()override;	// 更新処理.
	void Draw()override;	// 描画処理.

	void SetGameObjectPtr(GameObject* object);  // Enemyに見せたいGameObjectをセット
private:
	void ProcessTomato();

	int m_moveTime;  // 乱数行動時間
	float m_shotTime;   // トマトを投げる時間

	const int m_movePhaseTime;  // 次の行動に移る時間

	VECTOR m_velocity;  // 移動スピード
	VECTOR m_dir;       // 向き
	VECTOR m_tomatoDir;  // トマトを投げる向き
	VECTOR m_moveValue;  // 乱数移動量

	bool m_targetFoundFlag;  // 標的を発見したか
	bool m_aimTargetFlag;  // 標的に向けて移動するか

	std::vector<GameObject*> m_objects;  // エネミークラスにに情報を渡したいオブジェクト

	std::vector<Tomato*> m_tomatos;  // 投げたトマトを確保

	void Move1(GameObject* object);  // 標的に合わせて動く処理
	void Move2(GameObject* object);  // 標的がいないときの処理
	void Move3(GameObject* object);  // その他
	void RotateTowardTarget(VECTOR& aimTargetPos);  // 標的がいる方向に正面を向ける

	double GetDistance(VECTOR& pos1, VECTOR& pos2);  // 自身と他のオブジェクトの距離を出す
};

