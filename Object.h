#pragma once
#include <list>
#include "Component.h"
#include "ColliderComponent.h"


class Object
{
public:

	Object(){}
	~Object()
	{
		for (auto com : m_pComponentLists)
		{
			if (com != nullptr)
			{
				delete com;
				com = nullptr;
			}
		}
		for (auto com : m_pColliderComponentLists)
		{
			if (com != nullptr)
			{
				delete com;
				com = nullptr;
			}
		}
	}
	std::list<Component*>m_pComponentLists;
	std::list<ColliderComponent*> m_pColliderComponentLists;  // 一応複数のColliderを持てるように
	void Update()
	{
		auto& buff = m_pComponentLists;
		for (auto com : buff)
		{
			com->Update();
		}
	}
	void Draw()
	{
		for (auto com : m_pComponentLists)
		{
			com->Draw();
		}
	}
	void OnCollision(const list<Object*>& collObj)
	{
		for (auto own : m_pColliderComponentLists)
		{
			// 当たり判定を行なうか判定
			if (own->GetOnCollisionFlag())
			{
				// 他のオブジェクトからそのColliderComponentをもらう
				for (auto obj : collObj)
				{
					for (auto other : obj->m_pColliderComponentLists)
					{
						// 条件を満たしたら、そのあたり判定を無視して次に行く
						if (own->GetOwner() == other->GetOwner() || !other->GetOnCollisionFlag())
						{
							break;
						}

						// 相手Colliderと当たっていたら
						if (own->CollisionDetection(other))
						{
							// 当たった時の処理を行う(自分ではなく相手の情報を変える)
							other->GetOwner()->OnCollisionEnter(other, own);
						}
					}
				}
			}
		}
	}

	void OnDrawCollider()
	{
		for (auto com : m_pColliderComponentLists)
		{
			com->DrawCollider();
		}
	}

	// オブジェクトが持っているコンポーネントの取得
	template<class T>
	T* GetComponent()
	{
		for (auto com : m_pComponentLists)
		{
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
			{
				return buff;
			}
		}
		return nullptr;
	}

	// オブジェクトが持っているコンポーネントを追加
	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->m_pParent = this;
		m_pComponentLists.push_back(buff);
		buff->Start();
		return buff;
	}

	template<class T>
	T* GetCollider()
	{
		for (auto com : m_pColliderComponentLists)
		{
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
			{
				return buff;
			}
		}
		return nullptr;
	}

	template<class T>
	T* AddCollider()
	{
		T* buff = new T();
		buff->m_pParent = this;
		m_pColliderComponentLists.push_back(buff);
		return buff;
	}

	template<class T>
	Component* GetOwner()
	{
		for (auto com : m_pComponentLists)
		{
			Component* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
			{
				if (buff == com)
				{
					return buff;
				}
			}
		}
		return nullptr;
	}
};

extern std::list<Object*>m_pObjectLists;
extern std::list<Object*> m_pColliderLists;  // 当たり判定を行いたいオブジェクト(必要以上に回さないように)
