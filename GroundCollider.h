#pragma once
#include "ColliderComponent.h"

class GroundCollider : public ColliderComponent
{
public:
    GroundCollider();
    ~GroundCollider() override;  // ŒÂ•ÊƒNƒ‰ƒX‚ª‚ ‚é‚Ì‚Å“ÆŽ©‚Åíœ‚ðs‚¤

    void SetCollider(const Ground* ground);
    void Init(const VECTOR& pos, class Component* owner, class Tag* tag, CollisionInfo::CollisionType type) override;
    void UpdatePosition(const VECTOR& pos) { m_pGround->m_center = pos; }
    void UpdateScale(const float upSize, const float downSize, const float side) { m_pGround->m_upSize = upSize; m_pGround->m_downSize = downSize; m_pGround->m_sideSize = side; }

    bool CollisionDetection(ColliderComponent* other) override;
    bool Check(BoxCollider* other) override;
    bool Check(SphereCollider* other) override;

    void DrawCollider() override;
    const Ground* GetWorldGround() const { return m_pGround; }
private:
    Ground* m_pGround;

};

