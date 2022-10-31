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
		AimTarget,       // ターゲットを狙う
		EscapeTarget,    // ターゲットから逃げる
		RandomMove,      // 時間が経つと動きを変える(ターゲットがいないとき)
		TrackingTarget,  // ターゲットを追跡する(未発見)
		Wandering,       // 徘徊する(未発見)
		CollectTomato,   // トマトを回収しに行く
	};
	Type m_moveType;  // 今の行動

	Anim m_beforeAnim;

	// エネミーのパラメーター
	VECTOR m_speed;      // 移動スピード
	VECTOR m_avoidDir;  // 敵から逃げる方向
	VECTOR m_velocity;  // 移動量
	VECTOR m_dir;       // 向き
	VECTOR m_tomatoDir;  // トマトを投げる向き
	VECTOR m_moveValue;  // 乱数移動量
	VECTOR m_avoidVelocity;
	VECTOR m_towardDir;  // 向く方向

	// 動作時間
	int m_randomNum;  // ランダム行動の番号
	int m_moveTime;  // 乱数行動時間
	const int m_movePhaseTime;  // 次の行動に移る時間
	float m_shotTime;   // 投げる時間
	const float m_shotPhaseTime;  // 投げた後のクール時間

	// フラグ変数
	bool m_isAnimFlag;  // アニメーションできるか
	bool m_shotFlag;  // トマトを投げる
	bool m_pickFlag;  // トマトを拾う
	bool m_aimTargetFlag;  // 標的に向けて移動するか
	bool m_hitTomatoWallFlag = false;

	// 範囲指定変数
	const float m_targetRangeMin = 0.0f;        // ターゲットを感知する始まり値
	const float m_targetRangeMax = 150.0f;      // ターゲットを感知する最終範囲値
	const float m_targetMoveRangeMin = 60.0f;   // ターゲットに対する行動の変化最小値
	const float m_targetMoveRangeMax = 100.0f;  // ターゲットに対する行動の変化最大値
	const float m_targetEscapeRange = 200.0f;   // ターゲットから逃げる範囲

	// ポインタ
	std::vector<class Object*> m_pTarget;  // エネミークラスにに情報を渡したいプレイヤー
	std::vector<class Transform*> m_pTargetTf;  // ターゲットのTransformをキャッシュ
	VECTOR m_targetPos;

	// 関数
	void CheckMovePattern();  // 行動パターンをチェックして実行する

	void CheckTargetMovePattern();  // ターゲットに対しての行動パターンを実行する
	int FindTargetNearby();  // 最も近くにいるターゲットを調べる
	void MoveFoundTarget(const VECTOR& player);  // 標的に合わせて動く処理
	void MoveEscapeTarget(const VECTOR& player);  // 標的から逃げる処理

	void CheckTomatoWallMovePattern();  // トマトを回収する行動パターンを実行する
	int FindTomatoWallNearby();  // 最も近くにいるトマトの壁を調べる
	void MoveCollectTomato(TomatoWallManager* object);  // トマトを回収しに行く処理

	void CheckRandomMovePattern();
	void MoveTrackingTarget(const VECTOR& targetPos);
	void MoveWandering();
	void MoveTomato();

	void RotateTowardTarget(VECTOR& aimTargetPos);  // 標的がいる方向に正面を向ける

	void Animation();  // アニメーション処理関数
	void ChangeAnimation();  // アニメーションを変更する関数

	double GetDistance(VECTOR& pos1, VECTOR& pos2);  // 自身と他のオブジェクトの距離を出す
	float GetSize(float v1, float v2);
};

