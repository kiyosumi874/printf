#pragma once
#include "UIBase.h"
#include <vector>

using namespace std;

class UIRenderer
{
public:
	template<class T>
	void Insert()
	{
		m_ui.emplace_back(new T);
		m_ui.back()->Init();
	}

	void Terminate()
	{
		for (const auto& it : m_ui)
		{
			delete it;
		}
		m_ui.clear();
	}

	void Update()
	{
		for (const auto& it : m_ui)
		{
			it->Update();
		}
	}

	void Draw()
	{
		for (const auto& it : m_ui)
		{
			it->Draw();
		}
	}

private:
	vector<UIBase*> m_ui;
};