#pragma once
#include "Component.h"

class Human : public ModelBase, public Component
{
public:
	Human();
	virtual ~Human() {};

	virtual void Start() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void OnCollisionEnter(class ColliderComponent* ownColl, class ColliderComponent* otherColl) {};

	// 必ず呼ぶこと
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);

	void SetTomatoWallPtr(std::list<class Object*> tomatoWall);

	VECTOR GetPosition() { return m_var.pos; }
	VECTOR GetRotate() { return m_var.rotate; }
protected:
	AssetManager::ModelName m_modelName;

	class Transform* m_pTransform = nullptr;
	class Tag* m_pTag = nullptr;
	class BoxCollider* m_pBox = nullptr;

	std::vector<class TomatoWallManager*> m_pTomatoWall;
	class Icon* m_pIcon = nullptr;  // アイコンクラス
	class std::vector<class Tomato*> m_pTomato;

	const int m_bulletCapacity = 10; // 球の限界所持数
	int m_bulletNum = m_bulletCapacity;        // 球の所持数

	enum Anim
	{
		None = -1,  // 何もしない
		Idle,  // 止まる
		Run,   // 走る
		Throw,  // 投げる
		Pick,  // 拾う
	};

	int m_animType;  // 現在のアニメーションが何か
	int m_beforeAnimType;  // 前のアニメーション
	int m_animIndex;  // 現在のアニメーションを記録
	float m_animTime;  // アニメーションの経過時間
	float m_animTotalTime;  // アニメーションの総時間
	float m_animSpeed;  // 基準のアニメーションスピード
	float m_throwSpeed;  // 投げるスピード(補正をかける)
	float m_pickSpeed;  // 拾うスピード(補正をかける)

	bool m_moveFlag;  // 動いているか
	bool m_throwFlag;  // トマトを投げたか
	bool m_pickFlag;  // トマトを拾ったか

	virtual void Animation() {};  // アニメーション処理
	virtual void ChangeAnimation() {};  // アニメーション変更処理

	double GetDistance(VECTOR& pos1, VECTOR& pos2);
	float GetSize(float v1, float v2);
};
