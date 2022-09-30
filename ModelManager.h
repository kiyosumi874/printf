#pragma once

#define MODEL_NUM 6

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	void LoadGameModel();  // ゲームシーンのモデルをAssetManagerにロードする
	void LoadResultModel();  // リザルトシーンのモデルをAssetManagerにロードする
private:
};

