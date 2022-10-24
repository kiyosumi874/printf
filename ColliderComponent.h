#pragma once
#include "Collision.h"
#include "Tag.h"
#include "Object.h"

class ColliderComponent
{
public:
	// @param コンストラクタ
	ColliderComponent() {};
	// @param デストラクタ(継承先でoverride)
	virtual ~ColliderComponent() {};

	class Object* m_pParent;  // Objectクラスポインタ変数

	// @param コライダーのパラメーター設定を初期化
	// pos コライダーの位置  owner コライダーを持つコンポーネント  tag コライダーを持つオブジェクトのタグ名  type コライダータイプ
	virtual void Init(const VECTOR& pos, class Component* owner, class Tag* tag, CollisionInfo::CollisionType type) {};

	// @param コライダーを持つオブジェクトのタグ名を返す
	class Tag* GetTag() { return m_pTag; }
	// @param コライダーを持つオブジェクトのタグ名を得る
	// tag コライダーを持つオブジェクトのタグ名
	void SetTag(Tag* tag) { m_pTag = tag; }
	// @param コライダーを持つオブジェクトを生成したオブジェクトのタグ名を返す
	class Tag* GetParentTag() { return m_pParentTag; }
	// @param コライダーを持つオブジェクトを生成したオブジェクトのタグ名を得る
	// tag コライダーを持つオブジェクトを生成したオブジェクトのタグ名(コピーとする)
	void SetParentTag(Tag* tag) { m_pParentTag = tag; }
	// @param 前回のループで当たったオブジェクトのタグ名をもらう(コピーとする)
	// tag 当たったオブジェクトのタグ名
	void SetOnCollisionTag(class Tag* tag);
	enum class ObjectTag* GetOnCollisionTag(ObjectTag tag);
	void CleanCollisionTag();
	// @param コライダータイプを返す
	CollisionInfo::CollisionType GetCollisionType() { return m_pInfo->m_collType; }
	// @param 当たり判定フラグを返す
	bool GetOnCollisionFlag() { return m_onCollisionFlag; }
	// @param 当たり判定フラグを得る
	// flag 当たり判定を  true 行う  false 行わない
	void SetOnCollisionFlag(bool flag) { m_onCollisionFlag = flag; }

	// @prama 当たり判定情報をもらってくる
	// info 当たり判定情報
	void SetInfo(const CollisionInfo& info) { *m_pInfo = info; }
	// @param 当たり判定情報を初期化
	void ClearInfo();

	// @param 当たり判定情報を返す
	CollisionInfo& GetCollisionInfo() { return *m_pInfo; }

	// @param コライダーを持つコンポーネントを返す
	class Component* GetOwner() { return m_pOwner; }
	// @param コライダーを持つコンポーネントを得る(Component*に変換する)
	// owner コライダーを持つコンポーネント
	template<class T>
	class Component* SetOwner(T* owner) { return dynamic_cast<Component*>(owner); }

	// overrideされない場合falseを返す

	// @param 当たり判定を検出
	// other 相手のコライダー
	virtual bool CollisionDetection(ColliderComponent* other);
	
	// @param 当たり判定結果を返す
	// other 自分のコライダー
	virtual bool Check(class BoxCollider* other) { return false; }
	// @param 当たり判定結果を返す
	// other 自分のコライダー
	virtual bool Check(class SphereCollider* other) { return false; }
	// @param 当たり判定結果を返す
	// other 自分のコライダー
	virtual bool Check(class WallCollider* other) { return false; }
	// @param 当たり判定結果を返す
	// other 自分のコライダー
	virtual bool Check(class WorldCollider* other) { return false; }
	// @param 当たり判定結果を返す
	// other 自分のコライダー
	virtual bool Check(class GroundCollider* other) { return false; }

	// @ param Collider描画(絶対関数定義override)
	// DxLibのカメラ関係で位置がうまくあっていないので、大きさを見るために使ってください
	virtual void DrawCollider() = 0;

protected:
	class Tag* m_pTag = nullptr;               // コライダーを持つオブジェクトのタグ名
	class Tag* m_pParentTag = nullptr;         // 親の判別が必要なオブジェクトのみ使用(誰の弾かなど)
	std::vector<class Tag> m_onCollisionTag;  // 当たったオブジェクトのタグ名

	class Component* m_pOwner = nullptr;       // コライダーを持つコンポーネント
	class CollisionInfo* m_pInfo = nullptr;    // 当たり判定情報

	bool m_onCollisionFlag = false;            // 当たり判定を行うかどうか
};

