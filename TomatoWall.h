#pragma once
#include "GameObject.h"

class TomatoWall : public ModelBase, public GameObject
{
public:
	TomatoWall(ObjectTag tag);
	~TomatoWall();

	void Update() override;
	void Draw() override;

	// �K���ĂԂ���
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
protected:
	// Init���p�������N���X���g��Ȃ��Ă����悤
	// ���f���̖��O�����p�������N���X�ɓ���Ă��炤
	AssetManager::ModelName m_modelName;
};

