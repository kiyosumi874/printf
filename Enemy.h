#pragma once
#include "GameObject.h"

class Tomato;
class TomatoWall;
class ModelManager;

class Enemy : public GameObject
{
public:
	Enemy(ObjectTag tag, VECTOR position);				// コンストラクタ
	~Enemy();				// デストラクタ

	void Update()override;	// 更新処理.
	void Draw()override;	// 描画処理.

	void SetPlayerPtr(GameObject* player);  // Enemyに見せたいPlayerをセット
	void SetTomatoWallPtr(TomatoWall* tomatoWall);  // Enemyに見せたいTomatoWallをセット
private:
	void ProcessTomato();

	enum Type
	{
		SearchTarget,   // ターゲットを探す
		AimTarget,      // ターゲットを狙う
		EscapeTarget,   // ターゲットから逃げる
		TomatoCollect,  // トマトを回収しに行く
	};

	enum Anim
	{
		Idle,  // 止まる
		Run,   // 走る
	};

	// アニメーション変数
	int m_animType;  // 現在のアニメーションが何か
	int m_animIndex;  // 現在のアニメーションを記録
	float m_animTime;  // アニメーションの経過時間
	float m_animTotalTime;  // アニメーションの総時間

	// エネミーのパラメーター
	VECTOR m_velocity;  // 移動スピード
	VECTOR m_dir;       // 向き
	VECTOR m_tomatoDir;  // トマトを投げる向き
	VECTOR m_moveValue;  // 乱数移動量
	int m_bulletNum;  // 球の所持弾数
	const int m_bulletCapacity; // 球の限界所持数

	// 動作時間
	int m_moveTime;  // 乱数行動時間
	const int m_movePhaseTime;  // 次の行動に移る時間
	float m_shotTime;   // トマトを投げる時間

	// フラグ変数
	int m_moveType;  // 今の行動
	bool m_moveFlag;  // 動いているか
	bool m_aimTargetFlag;  // 標的に向けて移動するか

	// 範囲指定変数
	const float m_targetRangeMin = 0.0f;        // ターゲットを感知する始まり値
	const float m_targetRangeMax = 150.0f;      // ターゲットを感知する最終範囲値
	const float m_targetMoveRangeMin = 50.0f;   // ターゲットに対する行動の変化最小値
	const float m_targetMoveRangeMax = 100.0f;  // ターゲットに対する行動の変化最大値
	const float m_targetEscapeRange = 200.0f;   // ターゲットから逃げる範囲

	// ポインタ
	std::vector<GameObject*> m_player;  // エネミークラスにに情報を渡したいプレイヤー
	std::vector<TomatoWall*> m_tomatoWall;  // トマトの壁オブジェクトを格納する
	std::vector<Tomato*> m_tomatos;  // 投げたトマトを確保

	// 関数
	void CheckMovePattern();  // 行動パターンをチェックして実行する

	void CheckTargetMovePattern();  // ターゲットに対しての行動パターンを実行する
	void TargetMove1(GameObject* object);  // 標的に合わせて動く処理
	void TargetMove2(GameObject* object);  // 標的がいないときの処理
	void TargetMove3(GameObject* object);  // 標的から逃げる処理

	void CheckTomatoWall();  // トマトを回収する行動パターンを実行する
	void TomatoCollectMove(TomatoWall* object);  // トマトを回収しに行く処理
	void RotateTowardTarget(VECTOR& aimTargetPos);  // 標的がいる方向に正面を向ける

	void ChangeAnimation();  // アニメーションを変更する関数

	double GetDistance(VECTOR& pos1, VECTOR& pos2);  // 自身と他のオブジェクトの距離を出す
};

