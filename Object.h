#pragma once
#include <list>
#include "Component.h"

class Object
{
public:

	Object(){}
	~Object()
	{
		for (auto com : m_pComponentLists)
		{
			delete com;
		}
	}
	std::list<Component*>m_pComponentLists;
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
};

static std::list<Object*>m_pObjectLists;