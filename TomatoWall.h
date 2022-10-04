#pragma once
#include "GameObject.h"

class TomatoWall : public ModelBase, public GameObject
{
public:
	TomatoWall(ObjectTag tag);
	~TomatoWall();

	void Update() override;
	void Draw() override;

	// 必ず呼ぶこと
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
protected:
	// Initを継承したクラスが使わなくていいよう
	// モデルの名前だけ継承したクラスに入れてもらう
	AssetManager::ModelName m_modelName;
};

