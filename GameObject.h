#pragma once
#include "ObjectTag.h"

// 3Dモデルの基底クラス
class GameObject
{
public:
	GameObject();
	GameObject(ObjectTag tag);
	GameObject(ObjectTag tag, VECTOR position);
	virtual ~GameObject();

	virtual void Update() = 0;
	virtual void Draw() = 0;

	// セッター
	void SetPosition(const VECTOR& positon) { m_position = positon; }
	// ゲッター
	const VECTOR& GetPosition() const { return m_position; }
protected:
	VECTOR m_position;
	ObjectTag m_tag;
	int m_modelHandle;
};