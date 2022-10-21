#include "pch.h"
#include "Collision.h"

// 円形の押し戻しベクトルの符号が正しいか判定
void CollMath::CheckDistance(VECTOR& dis, const VECTOR& min, const VECTOR& max)
{
    // 絶対値がmin.xの方が小さかったら
    if (CollMath::Abs(min.x) <= CollMath::Abs(max.x))
    {
        // 距離が0より小さいとき符号を変える
        if (dis.x < 0)
        {
            dis.x = dis.x * -1.0f;
        }
    }
    else  // 違ったら
    {
        // 距離が0より大きいとき符号を変える
        if (dis.x > 0)
        {
            dis.x = dis.x * -1.0f;
        }
    }

    // 絶対値がmin.xの方が小さかったら
    if (CollMath::Abs(min.y) <= CollMath::Abs(max.y))
    {
        // 距離が0より小さいとき符号を変える
        if (dis.y < 0)
        {
            dis.y = dis.y * -1.0f;
        }
    }
    else  // 違ったら
    {
        // 距離が0より大きいとき符号を変える
        if (dis.y > 0)
        {
            dis.y = dis.y * -1.0f;
        }
    }

    // 絶対値がmin.xの方が小さかったら
    if (CollMath::Abs(min.z) <= CollMath::Abs(max.z))
    {
        // 距離が0より小さいとき符号を変える
        if (dis.z < 0)
        {
            dis.z = dis.z * -1.0f;
        }
    }
    else  // 違ったら
    {
        // 距離が0より大きいとき符号を変える
        if (dis.z > 0)
        {
            dis.z = dis.z * -1.0f;
        }
    }
}

//===============================================================================
// Sphere
//===============================================================================

// コンストラクタ 
// center 球の中心  radius 球の半径
Sphere::Sphere(const VECTOR& center, float radius)
    : m_center(center)
    , m_radius(radius)
{
}

// 位置をアップデートする(半径は保存されているもので計算)
// center 球の中心
void Sphere::UpdateSphere(const VECTOR& center)
{
    m_center = center;
}

// 半径を設定する
// radius 半径
void Sphere::Radius(float radius)
{
    m_radius = radius;
}

// SphereとBoxの当たり判定
// s (const)Sphereクラス変数  b (const)Boxクラス変数  info Collision情報
bool Intersect(const Sphere& s, const Box& b, CollisionInfo& info)
{
    // 全ての方向で中心から半分の長さを取る
    float otherRadiusX = b.m_max.x - b.m_center.x;
    float otherRadiusY = b.m_max.y - b.m_center.y;
    float otherRadiusZ = b.m_max.z - b.m_center.z;

    // 中心同士の距離を調べる
    float dis = CollMath::Distance(b.m_center, s.m_center);

    // 距離が一つでも相手の半径を下回ったら、当たったと判定
    auto result = otherRadiusX > dis ||
                  otherRadiusY > dis ||
                  otherRadiusZ > dis;
    return result;
}

// SphereとSphereの当たり判定
// s1 (const)Sphereクラス変数  s2 (const)Sphereクラス変数  info Collision情報
bool Intersect(const Sphere& s1, const Sphere& s2, CollisionInfo& info)
{
    // お互いの中心間の距離を測る
    double dis = CollMath::Distance(s1.m_center, s2.m_center);
    // その距離が半径より小さい場合
    if (dis < s1.m_radius)
    {
        return true;
    }
    return false;
}

// SphereとWallの当たり判定
// s (const)Sphereクラス変数  w (const)Wallクラス変数  info Collision情報
bool Intersect(const Sphere& s, const Wall& w, CollisionInfo& info)
{
    info.m_fixVec = VGet(0.0f, 0.0f, 0.0f);
    // Wall側はBoxでの当たり判定を行う
    return Intersect(s, *w.m_pWallBox, info);
}

// SphereとWorldの当たり判定
// s (const)Sphereクラス変数  w (const)Worldクラス変数  info Collision情報
bool Intersect(const Sphere& s, const World& w, CollisionInfo& info)
{
    bool result = false;

    // Worldの外に出ていたら、当たったとみなす
    result = w.m_pSphere->m_radius < CollMath::Distance(w.m_pSphere->m_center, s.m_center);

    return result;
}

// SphereとGroundの当たり判定
// s (const)Sphereクラス変数  g (const)Groundクラス変数  info Collision情報
bool Intersect(const Sphere& s, const Ground& g, CollisionInfo& info)
{
    // 地面の範囲に存在し、なおかつ地面より下にいる場合当たったとみなす
    bool result = g.m_center.x - g.m_sideSize < s.m_center.x&& g.m_center.x + g.m_sideSize > s.m_center.x &&
        g.m_center.y + g.m_upSize > s.m_center.y - s.m_radius;

    return result;
}

// SphereとBoxの押し戻し量計算
// sphere (const)
void calcCollisionFixVec(const Sphere& sphere, const Box& box, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);
    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = box.m_max.x - (sphere.m_center.x - sphere.m_radius);
    float dx2 = box.m_min.x - (sphere.m_center.x + sphere.m_radius);
    float dy1 = box.m_max.y - (sphere.m_center.y - sphere.m_radius);
    float dy2 = box.m_min.y - (sphere.m_center.y + sphere.m_radius);
    float dz1 = box.m_max.z - (sphere.m_center.z - sphere.m_radius);
    float dz2 = box.m_min.z - (sphere.m_center.z + sphere.m_radius);

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
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
    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = (sphere2.m_center.x - sphere2.m_radius) - (sphere1.m_center.x + sphere1.m_radius);
    float dx2 = (sphere2.m_center.x + sphere2.m_radius) - (sphere1.m_center.x - sphere1.m_radius);
    float dy1 = (sphere2.m_center.y - sphere2.m_radius) - (sphere1.m_center.y + sphere1.m_radius);
    float dy2 = (sphere2.m_center.y + sphere2.m_radius) - (sphere1.m_center.y - sphere1.m_radius);
    float dz1 = (sphere2.m_center.z - sphere2.m_radius) - (sphere1.m_center.z + sphere1.m_radius);
    float dz2 = (sphere2.m_center.z + sphere2.m_radius) - (sphere1.m_center.z - sphere1.m_radius);

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
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

    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = wa.m_max.x - (sphere.m_center.x - sphere.m_radius);
    float dx2 = wa.m_min.x - (sphere.m_center.x + sphere.m_radius);
    float dy1 = wa.m_max.y - (sphere.m_center.y - sphere.m_radius);
    float dy2 = wa.m_min.y - (sphere.m_center.y + sphere.m_radius);
    float dz1 = wa.m_max.z - (sphere.m_center.z - sphere.m_radius);
    float dz2 = wa.m_min.z - (sphere.m_center.z + sphere.m_radius);

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
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
    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = (wor.m_center.x + wor.m_radius) - sphere.m_center.x;
    float dx2 = (wor.m_center.x - wor.m_radius) - sphere.m_center.x;
    float dy1 = (wor.m_center.y + wor.m_radius) - sphere.m_center.y;
    float dy2 = (wor.m_center.y - wor.m_radius) - sphere.m_center.y;
    float dz1 = (wor.m_center.z + wor.m_radius) - sphere.m_center.z;
    float dz2 = (wor.m_center.z - wor.m_radius) - sphere.m_center.z;

    // 押し戻し量は距離から出す
    float tmp = CollMath::Distance(world.m_pSphere->m_center, sphere.m_center) - world.m_pSphere->m_radius;
    VECTOR dis = VGet(tmp, tmp, tmp);

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        // 押し戻し量の符号を位置関係から判定する
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.x = dis.x;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        // 押し戻し量の符号を位置関係から判定する
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.y = dis.y;
    }
    else
    {
        // 押し戻し量の符号を位置関係から判定する
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.z = dis.z;
    }
}

//===============================================================================
// Box
//===============================================================================
Box::Box(const VECTOR& center, const VECTOR& boxScale)
{
    // もらった大きさを半分にして最大の点と最小の点を決める
    VECTOR scale = VGet(boxScale.x / 2.0f, boxScale.y / 2.0f, boxScale.z / 2.0f);
    m_min = VGet(center.x - scale.x, center.y - scale.y, center.z - scale.z);
    m_max = VGet(center.x + scale.x, center.y + scale.y, center.z + scale.z);

    m_center = center;
    m_scale = boxScale;
    CalcVertex();
}
void Box::CalcVertex()
{
    // 箱の上側4点
    m_vertex[0] = VGet(m_min.x, m_min.y, m_max.z);
    m_vertex[1] = VGet(m_max.x, m_min.y, m_max.z);
    m_vertex[2] = VGet(m_min.x, m_max.y, m_max.z);
    m_vertex[3] = VGet(m_max.x, m_max.y, m_max.z);

    // 箱の下側4点VECTOR
    m_vertex[4] = VGet(m_min.x, m_min.y, m_min.z);
    m_vertex[5] = VGet(m_max.x, m_min.y, m_min.z);
    m_vertex[6] = VGet(m_min.x, m_max.y, m_min.z);
    m_vertex[7] = VGet(m_max.x, m_max.y, m_min.z);
}
float Box::MinDistSq(const VECTOR& point) const
{
    // それぞれの軸での差をとる
    float dx = CollMath::Max(m_min.x - point.x, 0.0f);
    dx = CollMath::Max(dx, point.x - m_max.x);
    float dy = CollMath::Max(m_min.y - point.y, 0.0f);
    dy = CollMath::Max(dy, point.y - m_max.y);
    float dz = CollMath::Max(m_min.z - point.z, 0.0f);
    dz = CollMath::Max(dy, point.z - m_max.z);
    // 3次元空間での距離の二乗の公式より
    return dx * dx + dy * dy + dz * dz;
}
void Box::UpdateMinMax(const VECTOR& center)
{
    // もらった大きさを半分にして最大の点と最小の点を決める
    VECTOR scale = VGet(m_scale.x / 2.0f, m_scale.y / 2.0f, m_scale.z / 2.0f);
    m_min = VGet(center.x - scale.x, center.y - scale.y, center.z - scale.z);
    m_max = VGet(center.x + scale.x, center.y + scale.y, center.z + scale.z);

    m_center = center;

    CalcVertex();
}
void Box::Scaling(float x, float y, float z)
{
    // もらった大きさに補正をかける
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
    // 一つもtrueがなければ、二つは衝突している
    return !result;
}
bool Intersect(const Box& b, const Sphere& s, CollisionInfo& info)
{
    // 全ての方向で中心から半分の長さを取る
    float otherRadiusX = b.m_max.x - b.m_center.x;
    float otherRadiusY = b.m_max.y - b.m_center.y;
    float otherRadiusZ = b.m_max.z - b.m_center.z;

    // 中心同士の距離を測る
    float dis = CollMath::Distance(b.m_center, s.m_center);

    // 距離が一つでも相手の半径を下回ったら、当たったと判定
    auto result = otherRadiusX > dis ||
        otherRadiusY > dis ||
        otherRadiusZ > dis;
    return result;
}
bool Intersect(const Box& b, const Wall& w, CollisionInfo& info)
{
    // めり込み戻りベクトル初期化
    info.m_fixVec = VGet(0, 0, 0);

    // WallはBoxでの当たり判定を行う
    return Intersect(b, *w.m_pWallBox, info);
}

bool Intersect(const Box& b, const Ground& g, CollisionInfo& info)
{
    // 地面の範囲に存在し、なおかつ地面より下にいる場合当たったとみなす
    bool result = g.m_center.x - g.m_sideSize < b.m_center.x&& g.m_center.x + g.m_sideSize > b.m_center.x &&
        g.m_center.y + g.m_upSize > b.m_min.y;

    return result;
}
bool Intersect(const Box& b, const World& w, CollisionInfo& info)
{
    bool result = true;

    // Worldの外にいる場合は当たったとみなす
    result = w.m_pSphere->m_radius < CollMath::Distance(w.m_pSphere->m_center, b.m_center);

    return result;
}

void calcCollisionFixVec(const Box& box1, const Box& box2, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);
    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = box2.m_min.x - box1.m_max.x;
    float dx2 = box2.m_max.x - box1.m_min.x;
    float dy1 = box2.m_min.y - box1.m_max.y;
    float dy2 = box2.m_max.y - box1.m_min.y;
    float dz1 = box2.m_min.z - box1.m_max.z;
    float dz2 = box2.m_max.z - box1.m_min.z;

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
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
    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = (sphere.m_center.x - sphere.m_radius) - box.m_max.x;
    float dx2 = (sphere.m_center.x + sphere.m_radius) - box.m_min.x;
    float dy1 = (sphere.m_center.y - sphere.m_radius) - box.m_max.y;
    float dy2 = (sphere.m_center.y + sphere.m_radius) - box.m_min.y;
    float dz1 = (sphere.m_center.z - sphere.m_radius) - box.m_max.z;
    float dz2 = (sphere.m_center.z + sphere.m_radius) - box.m_min.z;

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
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
    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = wa.m_min.x - box.m_max.x;
    float dx2 = wa.m_max.x - box.m_min.x;
    float dy1 = wa.m_min.y - box.m_max.y;
    float dy2 = wa.m_max.y - box.m_min.y;
    float dz1 = wa.m_min.z - box.m_max.z;
    float dz2 = wa.m_max.z - box.m_min.z;

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
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
    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = (wor.m_center.x + wor.m_radius) - box.m_center.x;
    float dx2 = (wor.m_center.x - wor.m_radius) - box.m_center.x;
    float dy1 = (wor.m_center.y + wor.m_radius) - box.m_center.y;
    float dy2 = (wor.m_center.y - wor.m_radius) - box.m_center.y;
    float dz1 = (wor.m_center.z + wor.m_radius) - box.m_center.z;
    float dz2 = (wor.m_center.z - wor.m_radius) - box.m_center.z;

    float tmp = CollMath::Distance(world.m_pSphere->m_center, box.m_center) - world.m_pSphere->m_radius;
    VECTOR dis = VGet(tmp, tmp, tmp);

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
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

    // 壁面の表面ベクトルを求める
    VECTOR wallLine = VSub(end, start);
    VECTOR nomalizedWallLine = wallLine;
    nomalizedWallLine = CollMath::Normalize(nomalizedWallLine);

    // 壁面の平面方程式
    m_normal = VCross(CollMath::m_unitZ, nomalizedWallLine);
    m_planeD = -1.0f * VDot(m_normal, start);

    // 壁面の4点を求める(start点の下→上→end点の上→下の順)
    VECTOR zMax = VGet(0.0f, 0.0f, start.z + wallHeight);

    m_wallVertex[0] = start;
    m_wallVertex[1] = VAdd(start, zMax);
    m_wallVertex[2] = VAdd(end, zMax);
    m_wallVertex[3] = end;

    mScale.x = 100.0f;
    mScale.y = CollMath::Length(VSub(end, start));
    mScale.z = wallHeight;

    // 表示回転角と回転方向
    VECTOR sgnVec = VCross(CollMath::m_unitX, nomalizedWallLine);
    float zAngle = acosf(VDot(CollMath::m_unitX, nomalizedWallLine)) - CollMath::m_piOver2;

    m_zRotate = sgnVec.z > 0 ? zAngle : -zAngle + CollMath::m_pi;
    CalcBox();
}
void Wall::CalcBox()
{
    // x,y,zの最大値　最小値を調べる
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
    // めり込み戻りベクトル初期化
    info.m_fixVec = VGet(0, 0, 0);

    return Intersect(b, *w.m_pWallBox, info);
}
bool Intersect(const Wall& w, const Sphere& s, CollisionInfo& info)
{
    info.m_fixVec = VGet(0.0f, 0.0f, 0.0f);

    // WallはBoxの当たり判定を行う
    return Intersect(s, *w.m_pWallBox, info);
}

void calcCollisionFixVec(const Wall& wall, const Box& box, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Box& wa = *wall.m_pWallBox;

    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = box.m_min.x - wa.m_max.x;
    float dx2 = box.m_max.x - wa.m_min.x;
    float dy1 = box.m_min.y - wa.m_max.y;
    float dy2 = box.m_max.y - wa.m_min.y;
    float dz1 = box.m_min.z - wa.m_max.z;
    float dz2 = box.m_max.z - wa.m_min.z;

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
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

    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = (sphere.m_center.x - sphere.m_radius) - wa.m_max.x;
    float dx2 = (sphere.m_center.x + sphere.m_radius) - wa.m_min.x;
    float dy1 = (sphere.m_center.y - sphere.m_radius) - wa.m_max.y;
    float dy2 = (sphere.m_center.y + sphere.m_radius) - wa.m_min.y;
    float dz1 = (sphere.m_center.z - sphere.m_radius) - wa.m_max.z;
    float dz2 = (sphere.m_center.z + sphere.m_radius) - wa.m_min.z;

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
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
    // 地面の範囲に存在し、なおかつ地面より下にいる場合当たったとみなす
    bool result = g.m_center.x - g.m_sideSize < b.m_center.x&& g.m_center.x + g.m_sideSize > b.m_center.x &&
        g.m_center.y + g.m_upSize > b.m_min.y;
    
    return result;
}

bool Intersect(const Ground& g, const Sphere& s, CollisionInfo& info)
{
    // 地面の範囲に存在し、なおかつ地面より下にいる場合当たったとみなす
    bool result = g.m_center.x - g.m_sideSize < s.m_center.x&& g.m_center.x + g.m_sideSize > s.m_center.x &&
        g.m_center.y + g.m_upSize > s.m_center.y - s.m_radius;

    return result;
}
void calcCollisionFixVec(const Ground& ground, const Box& box, VECTOR& calcFixVec)
{
    // 地面の下にいる分だけ補正をかける
    float dis = (ground.m_center.y + ground.m_upSize) - box.m_min.y;
    calcFixVec.y = dis;
}
void calcCollisionFixVec(const Ground& ground, const Sphere& sphere, VECTOR& calcFixVec)
{
    // 地面の下にいる分だけ補正をかける
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

    // Worldの外に出ていたら、当たったとみなす
    result = w.m_pSphere->m_radius < CollMath::Distance(w.m_pSphere->m_center, b.m_center);

    return result;
}
bool Intersect(const World& w, const Sphere& s, CollisionInfo& info)
{
    bool result = false;

    // Worldの外に出ていたら、当たったとみなす
    result = w.m_pSphere->m_radius < CollMath::Distance(w.m_pSphere->m_center, s.m_center);

    return result;
}

void calcCollisionFixVec(const World& world, const Box& box, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Sphere& wor = *world.m_pSphere;

    calcFixVec = VGet(0, 0, 0);
    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = (wor.m_center.x + wor.m_radius) - box.m_center.x;
    float dx2 = (wor.m_center.x - wor.m_radius) - box.m_center.x;
    float dy1 = (wor.m_center.y + wor.m_radius) - box.m_center.y;
    float dy2 = (wor.m_center.y - wor.m_radius) - box.m_center.y;
    float dz1 = (wor.m_center.z + wor.m_radius) - box.m_center.z;
    float dz2 = (wor.m_center.z - wor.m_radius) - box.m_center.z;

    // 半径を超えた分だけ引き戻し量を決める
    float tmp = CollMath::Distance(world.m_pSphere->m_center, box.m_center) - world.m_pSphere->m_radius;
    VECTOR dis = VGet(tmp, tmp, tmp);

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        // 押し戻し量の符号を位置関係から判定する
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.x = dis.x;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        // 押し戻し量の符号を位置関係から判定する
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.y = dis.y;
    }
    else
    {
        // 押し戻し量の符号を位置関係から判定する
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.z = dis.z;
    }
}
void calcCollisionFixVec(const World& world, const Sphere& sphere, VECTOR& calcFixVec)
{
    calcFixVec = VGet(0, 0, 0);

    Sphere& wor = *world.m_pSphere;

    calcFixVec = VGet(0, 0, 0);
    // 位置が最小の点と最大の点の全ての距離パターンを調べる
    float dx1 = (wor.m_center.x + wor.m_radius) - sphere.m_center.x;
    float dx2 = (wor.m_center.x - wor.m_radius) - sphere.m_center.x;
    float dy1 = (wor.m_center.y + wor.m_radius) - sphere.m_center.y;
    float dy2 = (wor.m_center.y - wor.m_radius) - sphere.m_center.y;
    float dz1 = (wor.m_center.z + wor.m_radius) - sphere.m_center.z;
    float dz2 = (wor.m_center.z - wor.m_radius) - sphere.m_center.z;

    // 半径を超えた分だけ引き戻し量を決める
    float tmp = CollMath::Distance(world.m_pSphere->m_center, sphere.m_center) - world.m_pSphere->m_radius;
    VECTOR dis = VGet(tmp, tmp, tmp);

    // dx, dy, dz には それぞれ1,2のうち絶対値が小さい方をセットする
    float dx = (CollMath::Abs(dx1) < CollMath::Abs(dx2)) ? dx1 : dx2;
    float dy = (CollMath::Abs(dy1) < CollMath::Abs(dy2)) ? dy1 : dy2;
    float dz = (CollMath::Abs(dz1) < CollMath::Abs(dz2)) ? dz1 : dz2;

    // x, y, zのうち最も差が小さい軸で位置を調整
    if (CollMath::Abs(dx) <= CollMath::Abs(dy) && CollMath::Abs(dx) <= CollMath::Abs(dz))
    {
        // 押し戻し量の符号を位置関係から判定する
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.x = dis.x;
    }
    else if (CollMath::Abs(dy) <= CollMath::Abs(dx) && CollMath::Abs(dy) <= CollMath::Abs(dz))
    {
        // 押し戻し量の符号を位置関係から判定する
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.y = dis.y;
    }
    else
    {
        // 押し戻し量の符号を位置関係から判定する
        CollMath::CheckDistance(dis, VGet(dx2, dy2, dz2), VGet(dx1, dy1, dz1));
        calcFixVec.z = dis.z;
    }
}