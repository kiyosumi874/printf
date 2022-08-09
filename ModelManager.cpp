#include "pch.h"
#include "ModelManager.h"

ModelManager::ModelManager()
{
	m_modelName.push_back("data/character/man1.mv1");
	m_modelName.push_back("data/character/woman1.mv1");
	m_modelName.push_back("data/character/man2.mv1");
	m_modelName.push_back("data/character/woman2.mv1");
	m_modelName.push_back("data/character/man3.mv1");
	m_modelName.push_back("data/character/woman3.mv1");
}

ModelManager::~ModelManager()
{
	for (int i = 0; i < m_modelName.size(); i++)
	{
		m_modelName.erase(std::cbegin(m_modelName) + i);
		m_modelName.shrink_to_fit();
	}
}

const int ModelManager::GetModelData(int modelNum)
{
	return MV1LoadModel(m_modelName[modelNum]);
}
