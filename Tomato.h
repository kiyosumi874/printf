#pragma once
#include "Component.h"

class Tomato : public ModelBase, public Component
{
public:
	Tomato();   // コンストラクタ
	~Tomato();  // デストラクタ

	void Start() override;
	void Update() override;  // 更新処理
	void Draw() override;  // 描画処理
	void OnCollisionEnter(class ColliderComponent* ownColl, class ColliderComponent* otherColl) override;

	// 必ず呼ぶこと
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
	// @param トマトを出現させる
	// pos 出現位置  dir 投げる方向  tag 投げたオブジェクトタグ名
	void ShotTomato(const VECTOR& pos, const VECTOR& dir, class Tag* tag);

	float GetTime();  // トマトを投げてからの時間を返す
	VECTOR GetPosition() { return m_var.pos; }
	VECTOR GetDir() { return m_dir; }

	class Tag* GetTag() { return m_pTag; }
	bool GetActive() { return m_isActive; }
private:
	void Move();  // 投げられた後の処理

	class SphereCollider* m_pSphere = nullptr;

	class Transform* m_pTransform = nullptr;
	class Tag* m_pTag = nullptr;
	class HitEffect* m_phitEffect = nullptr;
	class HitTomatoEffect* m_phitTomatoEffect = nullptr;
	VECTOR m_velocity;  // 速度
	VECTOR m_startVelocity;  // 初速
	VECTOR m_dir;  // 投げる方向

	float m_time;     // 投げた後の経過時間 
	float m_gravity;  // 重力
	float m_deg;      // 何度か
	float m_rad;      // ラジアン

	bool m_isActive = false;  // トマトの処理を行うか
};

