#pragma once

class Tomato : public GameObject
{
public:
	Tomato(ObjectTag tag, VECTOR position);   // コンストラクタ
	~Tomato();  // デストラクタ

	void Update();  // 更新処理
	void Draw() override;  // 描画処理

private:
	void Move();  // 投げられた後の処理

	VECTOR m_velocity;  // 速度

	float m_time;     // 投げた後の経過時間 
	float m_gravity;  // 重力
};

