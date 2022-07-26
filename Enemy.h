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
	float m_shotTime;  // トマトを投げる時間

	VECTOR m_dir;      // 向き

	std::vector<GameObject*> m_objects;

	std::vector<Tomato*> m_tomatos;

	void Move1(GameObject* object);  // プレイヤーに合わせて動く処理
	void Move2(GameObject* object);  
	void Move3(GameObject* object);

	double GetDistance(VECTOR& pos1, VECTOR& pos2);  // 自身と他のオブジェクトの距離を出す
};

