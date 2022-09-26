#pragma once
#include "GameObject.h"

class Tomato;
class TomatoWall;
class ModelManager;

class Player : public GameObject
{
public:
	Player(ObjectTag tag, VECTOR position);				// コンストラクタ
	~Player();				// デストラクタ

	void Update()override;	// 更新処理.
	void Draw()override;	// 描画処理.

	// ゲッター
	const float& GetAngle() const { return m_angle; }
	void SetTomatoWallPtr(TomatoWall* tomatoWall) { m_tomatoWall.push_back(tomatoWall); }
private:
	void Input();			// 入力移動処理.
	void Rotate();			// 回転処理.

	void TomatoCollect();  // トマト回収処理

	void ChangeAnimation();  // アニメーション変更処理

	VECTOR m_dir;			// 向き
	VECTOR m_aimDir;		// 目標向き
	VECTOR m_velocity;		// 速度
	int m_bulletNum;        // 球の所持数
	const int m_bulletCapacity; // 球の限界所持数

	float m_angle;			//	視点回転角度

	bool m_rotateNow;		// 回転中か判定用

	enum Anim
	{
		Idle,
		Run,
	};

	int m_animType;  // 現在のアニメーションが何か
	int m_animIndex;  // 現在のアニメーションを記録
	float m_animTime;  // アニメーションの経過時間
	float m_animTotalTime;  // アニメーションの総時間
	bool m_moveFlag;  // 動いているか

	std::vector<Tomato*> m_tomatos;
	std::vector<TomatoWall*> m_tomatoWall;

	double GetDistance(VECTOR& pos1, VECTOR& pos2);
};
