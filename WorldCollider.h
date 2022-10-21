#pragma once
#include "ColliderComponent.h"

class WorldCollider : public ColliderComponent
{
public:
    WorldCollider();
    ~WorldCollider() override;  // ŒÂ•ÊƒNƒ‰ƒX‚ª‚ ‚é‚Ì‚Å“ÆŽ©‚Åíœ‚ðs‚¤

    void SetCollider(const World* world);
    void Init(const VECTOR& pos, class Component* owner, class Tag* tag, CollisionInfo::CollisionType type) override;
    void UpdatePosition(const VECTOR& pos) { m_pWorld->m_pSphere->m_center = pos; }
    void UpdateRadius(const float rad) { m_pWorld->m_pSphere->m_radius = rad; }

    bool CollisionDetection(ColliderComponent* other) override;
    bool Check(BoxCollider* other) override;
    bool Check(SphereCollider* other) override;

    void DrawCollider() override;
    const World* GetWorld() { return m_pWorld; }
private:
    World* m_pWorld;
};

