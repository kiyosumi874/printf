#pragma once
#include "ColliderComponent.h"

class BoxCollider : public ColliderComponent
{
public:
    BoxCollider();
    ~BoxCollider() override;  // ŒÂ•ÊƒNƒ‰ƒX‚ª‚ ‚é‚Ì‚Å“ÆŽ©‚Åíœ‚ðs‚¤

    void SetCollider(const Box* box);
    void Init(const VECTOR& pos, class Component* owner, class Tag* tag, CollisionInfo::CollisionType type) override;
    void UpdatePosition(const VECTOR& pos) { m_pBox->UpdateMinMax(pos); }
    void UpdateScale(const VECTOR& scale) { m_pBox->Scaling(scale.x, scale.y, scale.z); }

    bool CollisionDetection(ColliderComponent* other) override;
    bool Check(BoxCollider* other) override;
    bool Check(SphereCollider* other) override;
    bool Check(WallCollider* other) override;
    bool Check(GroundCollider* other) override;
    bool Check(WorldCollider* other) override;

    void DrawCollider() override;
    const Box* GetWorldBox() const { return m_pBox; }
private:
    Box* m_pBox;
};

