#pragma once
#include "Component.h"

class Tomato : public Component
{
public:
	Tomato(VECTOR& position, VECTOR& dir);   // コンストラクタ
	~Tomato();  // デストラクタ

	void Update();  // 更新処理
	void Draw();  // 描画処理

	float GetTime();  // トマトを投げてからの時間を返す
	VECTOR GetPosition() { return m_position; }
private:
	void Move();  // 投げられた後の処理

	int m_modelHandle;

	VECTOR m_position;
	VECTOR m_velocity;  // 速度
	VECTOR m_startVelocity;  // 初速
	VECTOR m_dir;  // 投げる方向

	float m_time;     // 投げた後の経過時間 
	float m_gravity;  // 重力
	float m_deg;      // 何度か
	float m_rad;      // ラジアン
};

