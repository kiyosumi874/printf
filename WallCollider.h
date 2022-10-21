#pragma once
#include "ColliderComponent.h"

class WallCollider : public ColliderComponent
{
public:
    WallCollider();
    ~WallCollider() override;  // ŒÂ•ÊƒNƒ‰ƒX‚ª‚ ‚é‚Ì‚Å“ÆŽ©‚Åíœ‚ðs‚¤

    void SetCollider(const Wall* wall);
    void Init(const VECTOR& pos, class Component* owner, class Tag* tag, CollisionInfo::CollisionType type) override;
    void UpdatePosition(const VECTOR& pos) { m_pWall->m_pWallBox->UpdateMinMax(pos); }
    void UpdateScale(const VECTOR& scale) { m_pWall->m_pWallBox->Scaling(scale.x, scale.y, scale.z); }

    bool CollisionDetection(ColliderComponent* other) override;
    bool Check(BoxCollider* other) override;
    bool Check(SphereCollider* other) override;

    void DrawCollider() override;
    const Wall* GetWorldWall() { return m_pWall; }
private:
    Wall* m_pWall;
};

