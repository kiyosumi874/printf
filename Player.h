#pragma once
#include "GameObject.h"

class Tomato;

class Player : public GameObject
{
public:
	Player(ObjectTag tag, VECTOR position);				// コンストラクタ
	~Player();				// デストラクタ

	void Update()override;	// 更新処理.
	void Draw()override;	// 描画処理.

	// ゲッター
	const float& GetAngle() const { return m_angle; }
private:
	void Input();			// 入力移動処理.
	void Rotate();			// 回転処理.

	VECTOR m_dir;			// 向き
	VECTOR m_aimDir;		// 目標向き
	VECTOR m_velocity;		// 速度

	float m_angle;			//	視点回転角度

	bool m_rotateNow;		// 回転中か判定用

	std::vector<Tomato*> m_tomatos;
};
