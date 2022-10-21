#pragma once
#include "Human.h"

class PlayerCPU : public Human
{
public:
    PlayerCPU();
    ~PlayerCPU() override;

	void Start() override;	// コンポーネント初期化処理.
	void Update() override;	// 更新処理.
	void Draw() override;	// 描画処理.
	void OnCollisionEnter(class ColliderComponent* ownColl, class ColliderComponent* otherColl) override;

	void SetAimTargetPtr(class Object* target);  // PlayerCPUに狙わせたいTargetをセット

private:
	void ProcessTomato();

	enum Type
	{
		SearchTarget,   // ターゲットを探す
		AimTarget,      // ターゲットを狙う
		EscapeTarget,   // ターゲットから逃げる
		TomatoCollect,  // トマトを回収しに行く
	};

	// エネミーのパラメーター
	VECTOR m_velocity;  // 移動スピード
	VECTOR m_dir;       // 向き
	VECTOR m_tomatoDir;  // トマトを投げる向き
	VECTOR m_moveValue;  // 乱数移動量
	VECTOR m_avoidVelocity;

	// 動作時間
	int m_moveTime;  // 乱数行動時間
	const int m_movePhaseTime;  // 次の行動に移る時間
	float m_shotTime;   // 投げる時間
	const float m_shotPhaseTime;  // 投げた後のクール時間

	// フラグ変数
	int m_moveType;  // 今の行動
	bool m_aimTargetFlag;  // 標的に向けて移動するか
	bool m_avoidWallFlag;  // 壁を避ける
	bool m_absolutelyMoveFlag;  // 絶対に移動させるフラグ

	// 範囲指定変数
	const float m_targetRangeMin = 0.0f;        // ターゲットを感知する始まり値
	const float m_targetRangeMax = 150.0f;      // ターゲットを感知する最終範囲値
	const float m_targetMoveRangeMin = 60.0f;   // ターゲットに対する行動の変化最小値
	const float m_targetMoveRangeMax = 100.0f;  // ターゲットに対する行動の変化最大値
	const float m_targetEscapeRange = 200.0f;   // ターゲットから逃げる範囲

	// ポインタ
	std::vector<class Object*> m_target;  // PlayerCPUに情報を渡したターゲット

	// 関数
	void CheckMovePattern();  // 行動パターンをチェックして実行する

	void CheckTargetMovePattern();  // ターゲットに対しての行動パターンを実行する
	void Move1Target(class Object* player);  // 標的に合わせて動く処理
	void Move2Target(class Object* player);  // 標的がいないときの処理
	void Move3Target(class Object* player);  // 標的から逃げる処理

	void CheckTomatoWall();  // トマトを回収する行動パターンを実行する
	void CollectTomato(TomatoWallManager* object);  // トマトを回収しに行く処理
	void AvoidTomatoWall(TomatoWallManager* object);    // トマトの壁を避ける処理

	void RotateTowardTarget(VECTOR& aimTargetPos);  // 標的がいる方向に正面を向ける

	void Animation() override;  // アニメーション処理関数
	void ChangeAnimation() override;  // アニメーションを変更する関数
};

