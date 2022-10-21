#pragma once
#include "ColliderComponent.h"

class SphereCollider : public ColliderComponent
{
public:
    SphereCollider();
    ~SphereCollider() override;  // ŒÂ•ÊƒNƒ‰ƒX‚ª‚ ‚é‚Ì‚Å“ÆŽ©‚Åíœ‚ðs‚¤

    void SetCollider(const Sphere* sphere);
    void Init(const VECTOR& pos, class Component* owner, class Tag* tag, CollisionInfo::CollisionType type) override;
    void UpdatePosition(const VECTOR& pos) { m_pSphere->m_center = pos; }
    void UpdateRadius(const float rad) { m_pSphere->m_radius = rad; }

    bool CollisionDetection(ColliderComponent* other) override;
    bool Check(BoxCollider* other) override;
    bool Check(SphereCollider* other) override;
    bool Check(WallCollider* other) override;
    bool Check(GroundCollider* other) override;
    bool Check(WorldCollider* other) override;

    void DrawCollider() override;
    const Sphere* GetWorldSphere() { return m_pSphere; }
private:
    Sphere* m_pSphere;
};

