#pragma once

#define MODEL_NUM 6

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	const int GetModelData(int modelNum);
private:
	std::vector<const TCHAR*> m_modelName;
};

