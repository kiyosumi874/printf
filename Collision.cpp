#include "pch.h"
#include "Collision.h"

// �~�`�̉����߂��x�N�g���̕�����������������
void CollMath::CheckDistance(VECTOR& dis, const VECTOR& min, const VECTOR& max)
{
    // ��Βl��min.x�̕���������������
    if (CollMath::Abs(min.x) <= CollMath::Abs(max.x))
    {
        // ������0��菬�����Ƃ�������ς���
        if (dis.x < 0)
        {
            dis.x = dis.x * -1.0f;
        }
    }
    else  // �������
    {
        // ������0���傫���Ƃ�������ς���
        if (dis.x > 0)
        {
            dis.x = dis.x * -1.0f;
        }
    }

    // ��Βl��min.x�̕���������������
    if (CollMath::Abs(min.y) <= CollMath::Abs(max.y))
    {
        // ������0��菬�����Ƃ�������ς���
        if (dis.y < 0)
        {
            dis.y = dis.y * -1.0f;
        }
    }
    else  // �������
    {
        // ������0���傫���Ƃ�������ς���
        if (dis.y > 0)
        {
            dis.y = dis.y * -1.0f;
        }
    }

    // ��Βl��min.x�̕���������������
    if (CollMath::Abs(min.z) <= CollMath::Abs(max.z))
    {
        // ������0��菬�����Ƃ�������ς���
        if (dis.z < 0)
        {
            dis.z = dis.z * -1.0f;
        }
    }
    else  // �������
    {
        // ������0���傫���Ƃ�������ς���
        if (dis.z > 0)
        {
            dis.z = dis.z * -1.0f;
        }
    }
}

//===============================================================================
// Sphere
//===============================================================================

// �R���X�g���N�^ 
// center ���̒��S  radius ���̔��a
Sphere::Sphere(const VECTOR& center, float radius)
    : m_center(center)
    , m_radius(radius)
{
}

// �ʒu���A�b�v�f�[�g����(���a�͕ۑ�����Ă�����̂Ōv�Z)
// center ���̒��S
void Sphere::UpdateSphere(const VECTOR& center)
{
    m_center = center;
}

// ���a��ݒ肷��
// radius ���a
void Sphere::Radius(float radius)
{
    m_radius = radius;
}

// Sphere��Box�̓����蔻��
// s (const)Sphere�N���X�ϐ�  b (const)Box�N���X�ϐ�  info Collision���
bool Intersect(const Sphere& s, const Box& b, CollisionInfo& info)
{
    // �S�Ă̕����Œ��S���甼���̒��������
    float otherRadiusX = b.m_max.x - b.m_center.x;
    float otherRadiusY = b.m_max.y - b.m_center.y;
    float otherRadiusZ = b.m_max.z - b.m_center.z;

    // ���S���m�̋����𒲂ׂ�
    float dis = CollMath::Distance(b.m_center, s.m_center);

    // ��������ł�����̔��a�����������A���������Ɣ���
    auto result = otherRadiusX > dis ||
                  otherRadiusY > dis ||
                  otherRadiusZ > dis;
    return result;
}

// Sphere��Sphere�̓����蔻��
// s1 (const)Sphere�N���X�ϐ�  s2 (const)Sphere�N���X�ϐ�  info Collision���
bool Intersect(const Sphere& s1, const Sphere& s2, CollisionInfo& info)
{
    // ���݂��̒��S�Ԃ̋����𑪂�
    double dis = CollMath::Distance(s1.m_center, s2.m_center);
    // ���̋��������a��菬�����ꍇ
    if (dis < s1.m_radius)
    {
        return true;
    }
    return false;
}

// Sphere��Wall�̓����蔻��
// s (const)Sphere�N���X�ϐ�  w (const)Wall�N���X�ϐ�  info Collision���
bool Intersect(const Sphere& s, const Wall& w, CollisionInfo& info)
{
    info.m_fixVec = VGet(0.0f, 0.0f, 0.0f);
    // Wall����Box�ł̓����蔻����s��
    return Intersect(s, *w.m_pWallBox, info);
}

// Sphere��World�̓����蔻��
// s (const)Sphere�N���X�ϐ�  w (const)World�N���X�ϐ�  info Collision���
bool Intersect(const Sphere& s, const World& w, CollisionInfo& info)
{
    bool result = false;

    // World�̊O�ɏo�Ă�����A���������Ƃ݂Ȃ�
    result = w.m_pSphere->m_radius < CollMath::Distance(w.m_pSphere->m_center, s.m_center);

    return result;
}

// Sphere��Ground�̓����蔻��
// s (const)Sphere�N���X�ϐ�  g (const)Ground�N���X�ϐ�  info Collision���
bool Intersect(const Sphere& s, const Ground& g, CollisionInfo& info)
{
    // �n�ʂ͈̔͂ɑ��݂��A�Ȃ����n�ʂ�艺�ɂ���ꍇ���������Ƃ݂Ȃ�
    bool result = g.m_center.x - g.m_sideSize < s.m_center.x&& g.m_center.x + g.m_sideSize > s.m_center.x &&
        g.m_center.y + g.m_upSize > s.m_center.y - s.m_radius;

    return result;
}

// Sphere��Box�̉����߂��ʌv�Z
// sphere (const)
void calcCollisionFixVec(const Sphere& sphere, const Box& box, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);
    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = box.m_max.x - (sphere.m_center.x - sphere.m_radius);
    float dx2 = box.m_min.x - (sphere.m_center.x + sphere.m_radius);
    float dy1 = box.m_max.y - (sphere.m_center.y - sphere.m_radius);
    float dy2 = box.m_min.y - (sphere.m_center.y + sphere.m_radius);
    float dz1 = box.m_max.z - (sphere.m_center.z - sphere.m_radius);
    float dz2 = box.m_min.z - (sphere.m_center.z + sphere.m_radius);

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        calcFixVec.y = dy;
    }
    else
    {
        calcFixVec.z = dz;
    }
}
void calcCollisionFixVec(const Sphere& sphere1, const Sphere& sphere2, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);
    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = (sphere2.m_center.x - sphere2.m_radius) - (sphere1.m_center.x + sphere1.m_radius);
    float dx2 = (sphere2.m_center.x + sphere2.m_radius) - (sphere1.m_center.x - sphere1.m_radius);
    float dy1 = (sphere2.m_center.y - sphere2.m_radius) - (sphere1.m_center.y + sphere1.m_radius);
    float dy2 = (sphere2.m_center.y + sphere2.m_radius) - (sphere1.m_center.y - sphere1.m_radius);
    float dz1 = (sphere2.m_center.z - sphere2.m_radius) - (sphere1.m_center.z + sphere1.m_radius);
    float dz2 = (sphere2.m_center.z + sphere2.m_radius) - (sphere1.m_center.z - sphere1.m_radius);

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        calcFixVec.y = dy;
    }
    else
    {
        calcFixVec.z = dz;
    }
}
void calcCollisionFixVec(const Sphere& sphere, const Wall& wall, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Box& wa = *wall.m_pWallBox;

    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = wa.m_max.x - (sphere.m_center.x - sphere.m_radius);
    float dx2 = wa.m_min.x - (sphere.m_center.x + sphere.m_radius);
    float dy1 = wa.m_max.y - (sphere.m_center.y - sphere.m_radius);
    float dy2 = wa.m_min.y - (sphere.m_center.y + sphere.m_radius);
    float dz1 = wa.m_max.z - (sphere.m_center.z - sphere.m_radius);
    float dz2 = wa.m_min.z - (sphere.m_center.z + sphere.m_radius);

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        calcFixVec.y = dy;
    }
    else
    {
        calcFixVec.z = dz;
    }
}
void calcCollisionFixVec(const Sphere& sphere, const World& world, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Sphere& wor = *world.m_pSphere;

    calcFixVec = VGet(0, 0, 0);
    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = (wor.m_center.x + wor.m_radius) - sphere.m_center.x;
    float dx2 = (wor.m_center.x - wor.m_radius) - sphere.m_center.x;
    float dy1 = (wor.m_center.y + wor.m_radius) - sphere.m_center.y;
    float dy2 = (wor.m_center.y - wor.m_radius) - sphere.m_center.y;
    float dz1 = (wor.m_center.z + wor.m_radius) - sphere.m_center.z;
    float dz2 = (wor.m_center.z - wor.m_radius) - sphere.m_center.z;

    // �����߂��ʂ͋�������o��
    float tmp = CollMath::Distance(world.m_pSphere->m_center, sphere.m_center) - world.m_pSphere->m_radius;
    VECTOR dis = VGet(tmp, tmp, tmp);

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        // �����߂��ʂ̕������ʒu�֌W���画�肷��
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.x = dis.x;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        // �����߂��ʂ̕������ʒu�֌W���画�肷��
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.y = dis.y;
    }
    else
    {
        // �����߂��ʂ̕������ʒu�֌W���画�肷��
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.z = dis.z;
    }
}

//===============================================================================
// Box
//===============================================================================
Box::Box(const VECTOR& center, const VECTOR& boxScale)
{
    // ��������傫���𔼕��ɂ��čő�̓_�ƍŏ��̓_�����߂�
    VECTOR scale = VGet(boxScale.x / 2.0f, boxScale.y / 2.0f, boxScale.z / 2.0f);
    m_min = VGet(center.x - scale.x, center.y - scale.y, center.z - scale.z);
    m_max = VGet(center.x + scale.x, center.y + scale.y, center.z + scale.z);

    m_center = center;
    m_scale = boxScale;
    CalcVertex();
}
void Box::CalcVertex()
{
    // ���̏㑤4�_
    m_vertex[0] = VGet(m_min.x, m_min.y, m_max.z);
    m_vertex[1] = VGet(m_max.x, m_min.y, m_max.z);
    m_vertex[2] = VGet(m_min.x, m_max.y, m_max.z);
    m_vertex[3] = VGet(m_max.x, m_max.y, m_max.z);

    // ���̉���4�_VECTOR
    m_vertex[4] = VGet(m_min.x, m_min.y, m_min.z);
    m_vertex[5] = VGet(m_max.x, m_min.y, m_min.z);
    m_vertex[6] = VGet(m_min.x, m_max.y, m_min.z);
    m_vertex[7] = VGet(m_max.x, m_max.y, m_min.z);
}
float Box::MinDistSq(const VECTOR& point) const
{
    // ���ꂼ��̎��ł̍����Ƃ�
    float dx = CollMath::Max(m_min.x - point.x, 0.0f);
    dx = CollMath::Max(dx, point.x - m_max.x);
    float dy = CollMath::Max(m_min.y - point.y, 0.0f);
    dy = CollMath::Max(dy, point.y - m_max.y);
    float dz = CollMath::Max(m_min.z - point.z, 0.0f);
    dz = CollMath::Max(dy, point.z - m_max.z);
    // 3������Ԃł̋����̓��̌������
    return dx * dx + dy * dy + dz * dz;
}
void Box::UpdateMinMax(const VECTOR& center)
{
    // ��������傫���𔼕��ɂ��čő�̓_�ƍŏ��̓_�����߂�
    VECTOR scale = VGet(m_scale.x / 2.0f, m_scale.y / 2.0f, m_scale.z / 2.0f);
    m_min = VGet(center.x - scale.x, center.y - scale.y, center.z - scale.z);
    m_max = VGet(center.x + scale.x, center.y + scale.y, center.z + scale.z);

    m_center = center;

    CalcVertex();
}
void Box::Scaling(float x, float y, float z)
{
    // ��������傫���ɕ␳��������
    m_scale = VGet(x * 10.0f, y * 10.0f, z * 10.0f);
}
void Box::Scaling(float scale)
{
    Scaling(scale, scale, scale);
}

bool Intersect(const Box& b1, const Box& b2, CollisionInfo& info)
{
    bool result = b1.m_max.x < b2.m_min.x ||
        b1.m_max.y < b2.m_min.y ||
        b1.m_max.z < b2.m_min.z ||
        b2.m_max.x < b1.m_min.x ||
        b2.m_max.y < b1.m_min.y ||
        b2.m_max.z < b1.m_min.z;
    // ���true���Ȃ���΁A��͏Փ˂��Ă���
    return !result;
}
bool Intersect(const Box& b, const Sphere& s, CollisionInfo& info)
{
    // �S�Ă̕����Œ��S���甼���̒��������
    float otherRadiusX = b.m_max.x - b.m_center.x;
    float otherRadiusY = b.m_max.y - b.m_center.y;
    float otherRadiusZ = b.m_max.z - b.m_center.z;

    // ���S���m�̋����𑪂�
    float dis = CollMath::Distance(b.m_center, s.m_center);

    // ��������ł�����̔��a�����������A���������Ɣ���
    auto result = otherRadiusX > dis ||
        otherRadiusY > dis ||
        otherRadiusZ > dis;
    return result;
}
bool Intersect(const Box& b, const Wall& w, CollisionInfo& info)
{
    // �߂荞�ݖ߂�x�N�g��������
    info.m_fixVec = VGet(0, 0, 0);

    // Wall��Box�ł̓����蔻����s��
    return Intersect(b, *w.m_pWallBox, info);
}

bool Intersect(const Box& b, const Ground& g, CollisionInfo& info)
{
    // �n�ʂ͈̔͂ɑ��݂��A�Ȃ����n�ʂ�艺�ɂ���ꍇ���������Ƃ݂Ȃ�
    bool result = g.m_center.x - g.m_sideSize < b.m_center.x&& g.m_center.x + g.m_sideSize > b.m_center.x &&
        g.m_center.y + g.m_upSize > b.m_min.y;

    return result;
}
bool Intersect(const Box& b, const World& w, CollisionInfo& info)
{
    bool result = true;

    // World�̊O�ɂ���ꍇ�͓��������Ƃ݂Ȃ�
    result = w.m_pSphere->m_radius < CollMath::Distance(w.m_pSphere->m_center, b.m_center);

    return result;
}

void calcCollisionFixVec(const Box& box1, const Box& box2, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);
    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = box2.m_min.x - box1.m_max.x;
    float dx2 = box2.m_max.x - box1.m_min.x;
    float dy1 = box2.m_min.y - box1.m_max.y;
    float dy2 = box2.m_max.y - box1.m_min.y;
    float dz1 = box2.m_min.z - box1.m_max.z;
    float dz2 = box2.m_max.z - box1.m_min.z;

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        calcFixVec.y = dy;
    }
    else
    {
        calcFixVec.z = dz;
    }
}
void calcCollisionFixVec(const Box& box, const Sphere& sphere, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);
    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = (sphere.m_center.x - sphere.m_radius) - box.m_max.x;
    float dx2 = (sphere.m_center.x + sphere.m_radius) - box.m_min.x;
    float dy1 = (sphere.m_center.y - sphere.m_radius) - box.m_max.y;
    float dy2 = (sphere.m_center.y + sphere.m_radius) - box.m_min.y;
    float dz1 = (sphere.m_center.z - sphere.m_radius) - box.m_max.z;
    float dz2 = (sphere.m_center.z + sphere.m_radius) - box.m_min.z;

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        calcFixVec.y = dy;
    }
    else
    {
        calcFixVec.z = dz;
    }
}
void calcCollisionFixVec(const Box& box, const Wall& wall, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Box& wa = *wall.m_pWallBox;
    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = wa.m_min.x - box.m_max.x;
    float dx2 = wa.m_max.x - box.m_min.x;
    float dy1 = wa.m_min.y - box.m_max.y;
    float dy2 = wa.m_max.y - box.m_min.y;
    float dz1 = wa.m_min.z - box.m_max.z;
    float dz2 = wa.m_max.z - box.m_min.z;

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        calcFixVec.y = dy;
    }
    else
    {
        calcFixVec.z = dz;
    }
}
void calcCollisionFixVec(const Box& box, const World& world, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Sphere& wor = *world.m_pSphere;

    calcFixVec = VGet(0, 0, 0);
    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = (wor.m_center.x + wor.m_radius) - box.m_center.x;
    float dx2 = (wor.m_center.x - wor.m_radius) - box.m_center.x;
    float dy1 = (wor.m_center.y + wor.m_radius) - box.m_center.y;
    float dy2 = (wor.m_center.y - wor.m_radius) - box.m_center.y;
    float dz1 = (wor.m_center.z + wor.m_radius) - box.m_center.z;
    float dz2 = (wor.m_center.z - wor.m_radius) - box.m_center.z;

    float tmp = CollMath::Distance(world.m_pSphere->m_center, box.m_center) - world.m_pSphere->m_radius;
    VECTOR dis = VGet(tmp, tmp, tmp);

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.x = dis.x;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.y = dis.y;
    }
    else
    {
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.z = dis.z;
    }
}

//===============================================================================
// Wall
//===============================================================================
Wall::Wall(const Box* b)
{
    m_pWallBox = const_cast<Box*>(b);
    CreateWall(m_pWallBox->m_min, m_pWallBox->m_max, m_pWallBox->m_max.y - m_pWallBox->m_min.y);
}
void Wall::CreateWall(const VECTOR& start, const VECTOR& end, float wallHeight)
{
    m_start = start;
    m_end = end;

    // �ǖʂ̕\�ʃx�N�g�������߂�
    VECTOR wallLine = VSub(end, start);
    VECTOR nomalizedWallLine = wallLine;
    nomalizedWallLine = CollMath::Normalize(nomalizedWallLine);

    // �ǖʂ̕��ʕ�����
    m_normal = VCross(CollMath::m_unitZ, nomalizedWallLine);
    m_planeD = -1.0f * VDot(m_normal, start);

    // �ǖʂ�4�_�����߂�(start�_�̉����とend�_�̏と���̏�)
    VECTOR zMax = VGet(0.0f, 0.0f, start.z + wallHeight);

    m_wallVertex[0] = start;
    m_wallVertex[1] = VAdd(start, zMax);
    m_wallVertex[2] = VAdd(end, zMax);
    m_wallVertex[3] = end;

    mScale.x = 100.0f;
    mScale.y = CollMath::Length(VSub(end, start));
    mScale.z = wallHeight;

    // �\����]�p�Ɖ�]����
    VECTOR sgnVec = VCross(CollMath::m_unitX, nomalizedWallLine);
    float zAngle = acosf(VDot(CollMath::m_unitX, nomalizedWallLine)) - CollMath::m_piOver2;

    m_zRotate = sgnVec.z > 0 ? zAngle : -zAngle + CollMath::m_pi;
    CalcBox();
}
void Wall::CalcBox()
{
    // x,y,z�̍ő�l�@�ŏ��l�𒲂ׂ�
    m_pWallBox->m_min = m_pWallBox->m_max = m_wallVertex[0];
    for (int i = 1; i < 4; i++)
    {
        m_pWallBox->m_min.x = CollMath::Min(m_pWallBox->m_min.x, m_wallVertex[i].x);
        m_pWallBox->m_min.y = CollMath::Min(m_pWallBox->m_min.y, m_wallVertex[i].y);
        m_pWallBox->m_min.z = CollMath::Min(m_pWallBox->m_min.z, m_wallVertex[i].z);

        m_pWallBox->m_max.x = CollMath::Max(m_pWallBox->m_max.x, m_wallVertex[i].x);
        m_pWallBox->m_max.y = CollMath::Max(m_pWallBox->m_max.y, m_wallVertex[i].y);
        m_pWallBox->m_max.z = CollMath::Max(m_pWallBox->m_max.z, m_wallVertex[i].z);
    }
}

bool Intersect(const Wall& w, const Box& b, CollisionInfo& info)
{
    // �߂荞�ݖ߂�x�N�g��������
    info.m_fixVec = VGet(0, 0, 0);

    return Intersect(b, *w.m_pWallBox, info);
}
bool Intersect(const Wall& w, const Sphere& s, CollisionInfo& info)
{
    info.m_fixVec = VGet(0.0f, 0.0f, 0.0f);

    // Wall��Box�̓����蔻����s��
    return Intersect(s, *w.m_pWallBox, info);
}

void calcCollisionFixVec(const Wall& wall, const Box& box, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Box& wa = *wall.m_pWallBox;

    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = box.m_min.x - wa.m_max.x;
    float dx2 = box.m_max.x - wa.m_min.x;
    float dy1 = box.m_min.y - wa.m_max.y;
    float dy2 = box.m_max.y - wa.m_min.y;
    float dz1 = box.m_min.z - wa.m_max.z;
    float dz2 = box.m_max.z - wa.m_min.z;

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        calcFixVec.y = dy;
    }
    else
    {
        calcFixVec.z = dz;
    }
}

void calcCollisionFixVec(const Wall& wall, const Sphere& sphere, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Box& wa = *wall.m_pWallBox;

    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = (sphere.m_center.x - sphere.m_radius) - wa.m_max.x;
    float dx2 = (sphere.m_center.x + sphere.m_radius) - wa.m_min.x;
    float dy1 = (sphere.m_center.y - sphere.m_radius) - wa.m_max.y;
    float dy2 = (sphere.m_center.y + sphere.m_radius) - wa.m_min.y;
    float dz1 = (sphere.m_center.z - sphere.m_radius) - wa.m_max.z;
    float dz2 = (sphere.m_center.z + sphere.m_radius) - wa.m_min.z;

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        calcFixVec.x = dx;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        calcFixVec.y = dy;
    }
    else
    {
        calcFixVec.z = dz;
    }
}

//===============================================================================
// Ground
//===============================================================================
Ground::Ground(const VECTOR& center, const float upSize, const float downSize, const float sideSize)
{
    m_center = center;
    m_upSize = upSize;
    m_downSize = downSize;
    m_sideSize = sideSize;
}


bool Intersect(const Ground& g, const Box& b, CollisionInfo& info)
{
    // �n�ʂ͈̔͂ɑ��݂��A�Ȃ����n�ʂ�艺�ɂ���ꍇ���������Ƃ݂Ȃ�
    bool result = g.m_center.x - g.m_sideSize < b.m_center.x&& g.m_center.x + g.m_sideSize > b.m_center.x &&
        g.m_center.y + g.m_upSize > b.m_min.y;
    
    return result;
}

bool Intersect(const Ground& g, const Sphere& s, CollisionInfo& info)
{
    // �n�ʂ͈̔͂ɑ��݂��A�Ȃ����n�ʂ�艺�ɂ���ꍇ���������Ƃ݂Ȃ�
    bool result = g.m_center.x - g.m_sideSize < s.m_center.x&& g.m_center.x + g.m_sideSize > s.m_center.x &&
        g.m_center.y + g.m_upSize > s.m_center.y - s.m_radius;

    return result;
}
void calcCollisionFixVec(const Ground& ground, const Box& box, VECTOR& calcFixVec)
{
    // �n�ʂ̉��ɂ��镪�����␳��������
    float dis = (ground.m_center.y + ground.m_upSize) - box.m_min.y;
    calcFixVec.y = dis;
}
void calcCollisionFixVec(const Ground& ground, const Sphere& sphere, VECTOR& calcFixVec)
{
    // �n�ʂ̉��ɂ��镪�����␳��������
    float dis = (ground.m_center.y + ground.m_upSize) - (sphere.m_center.y - sphere.m_radius);
    calcFixVec.y = dis;
}

//===============================================================================
// World
//===============================================================================
World::World(const Sphere* s)
{
    m_pSphere = const_cast<Sphere*>(s);
}

bool Intersect(const World& w, const Box& b, CollisionInfo& info)
{
    bool result = true;

    // World�̊O�ɏo�Ă�����A���������Ƃ݂Ȃ�
    result = w.m_pSphere->m_radius < CollMath::Distance(w.m_pSphere->m_center, b.m_center);

    return result;
}
bool Intersect(const World& w, const Sphere& s, CollisionInfo& info)
{
    bool result = false;

    // World�̊O�ɏo�Ă�����A���������Ƃ݂Ȃ�
    result = w.m_pSphere->m_radius < CollMath::Distance(w.m_pSphere->m_center, s.m_center);

    return result;
}

void calcCollisionFixVec(const World& world, const Box& box, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Sphere& wor = *world.m_pSphere;

    calcFixVec = VGet(0, 0, 0);
    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = (wor.m_center.x + wor.m_radius) - box.m_center.x;
    float dx2 = (wor.m_center.x - wor.m_radius) - box.m_center.x;
    float dy1 = (wor.m_center.y + wor.m_radius) - box.m_center.y;
    float dy2 = (wor.m_center.y - wor.m_radius) - box.m_center.y;
    float dz1 = (wor.m_center.z + wor.m_radius) - box.m_center.z;
    float dz2 = (wor.m_center.z - wor.m_radius) - box.m_center.z;

    // ���a�𒴂��������������߂��ʂ����߂�
    float tmp = CollMath::Distance(world.m_pSphere->m_center, box.m_center) - world.m_pSphere->m_radius;
    VECTOR dis = VGet(tmp, tmp, tmp);

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        // �����߂��ʂ̕������ʒu�֌W���画�肷��
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.x = dis.x;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        // �����߂��ʂ̕������ʒu�֌W���画�肷��
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.y = dis.y;
    }
    else
    {
        // �����߂��ʂ̕������ʒu�֌W���画�肷��
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.z = dis.z;
    }
}
void calcCollisionFixVec(const World& world, const Sphere& sphere, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Sphere& wor = *world.m_pSphere;

    calcFixVec = VGet(0, 0, 0);
    // �ʒu���ŏ��̓_�ƍő�̓_�̑S�Ă̋����p�^�[���𒲂ׂ�
    float dx1 = (wor.m_center.x + wor.m_radius) - sphere.m_center.x;
    float dx2 = (wor.m_center.x - wor.m_radius) - sphere.m_center.x;
    float dy1 = (wor.m_center.y + wor.m_radius) - sphere.m_center.y;
    float dy2 = (wor.m_center.y - wor.m_radius) - sphere.m_center.y;
    float dz1 = (wor.m_center.z + wor.m_radius) - sphere.m_center.z;
    float dz2 = (wor.m_center.z - wor.m_radius) - sphere.m_center.z;

    // ���a�𒴂��������������߂��ʂ����߂�
    float tmp = CollMath::Distance(world.m_pSphere->m_center, sphere.m_center) - world.m_pSphere->m_radius;
    VECTOR dis = VGet(tmp, tmp, tmp);

    // dx, dy, dz �ɂ� ���ꂼ��1,2�̂�����Βl�������������Z�b�g����
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, z�̂����ł��������������ňʒu�𒲐�
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        // �����߂��ʂ̕������ʒu�֌W���画�肷��
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.x = dis.x;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        // �����߂��ʂ̕������ʒu�֌W���画�肷��
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.y = dis.y;
    }
    else
    {
        // �����߂��ʂ̕������ʒu�֌W���画�肷��
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.z = dis.z;
    }
}