#pragma once
#include "Component.h"

class DebugColliderObject : public ModelBase, public Component
{
public:
	void Start() override;
	void Update() override;
	void Draw() override;
	void OnCollisionEnter(class ColliderComponent* ownColl, class ColliderComponent* otherColl) override;

	// •K‚¸ŒÄ‚Ô‚±‚Æ
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);
protected:
	class Transform* m_pTransform = nullptr;
	class Tag* m_pTag = nullptr;
	/*class BoxCollider* m_pColl = nullptr;*/
	class SphereCollider* m_pColl = nullptr;
	/*class WallCollider* m_pWall = nullptr;*/
	/*class GroundCollider* m_pGround = nullptr;*/
	/*class WorldCollider* m_pWorld = nullptr;*/
};

