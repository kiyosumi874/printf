#pragma once
#include "Component.h"

class Tomato : public ModelBase, public Component
{
public:
	Tomato();   // コンストラクタ
	~Tomato();  // デストラクタ

	void Start();
	void Update();  // 更新処理
	void Draw();  // 描画処理

	// 必ず呼ぶこと
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
	void ShotTomato(const VECTOR& pos, const VECTOR& dir, class Tag* tag) { m_dir = dir; m_tag = tag; }  // トマトを飛ばす方向

	float GetTime();  // トマトを投げてからの時間を返す
	VECTOR GetPosition() { return m_var.pos; }
	VECTOR GetDir() { return m_dir; }

	class Tag* GetTag() { return m_tag; }
private:
	void Move();  // 投げられた後の処理

	class Transform* m_pTransform;
	class Tag* m_tag;
	VECTOR m_velocity;  // 速度
	VECTOR m_startVelocity;  // 初速
	VECTOR m_dir;  // 投げる方向

	float m_time;     // 投げた後の経過時間 
	float m_gravity;  // 重力
	float m_deg;      // 何度か
	float m_rad;      // ラジアン
};

