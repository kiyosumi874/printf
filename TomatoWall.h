#pragma once
#include "Component.h"

class TomatoWall : public ModelBase, public Component
{
public:
	TomatoWall();
	~TomatoWall();

	void Update() override;
	virtual void Draw();

	// 必ず呼ぶこと
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
	void SetTag(Tag* tag) { m_pTag = tag; }
protected:
	// Initを継承したクラスが使わなくていいよう
	// モデルの名前だけ継承したクラスに入れてもらう
	AssetManager::ModelName m_modelName;
	Tag* m_pTag;
};

