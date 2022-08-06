#pragma once

// 衝突情報
struct CollisionInfo
{
	VECTOR m_collisionPoint;	// 衝突点
	VECTOR m_fixVec;			// 押し戻しベクトル
	VECTOR m_hitNormal;			// 衝突点での法線
};

// 球体
struct Sphere
{
	Sphere(const VECTOR& center, float radius);
	bool Contains(const VECTOR& point) const;

	VECTOR m_center;
	float m_radius;
};

// 線分
struct Line
{
	Line();
	Line(const VECTOR& start, const VECTOR& end);

	VECTOR m_lineStart;
	VECTOR m_lineEnd;
	VECTOR m_normalizeDirection;
	float  m_lineLength;
	bool   m_rotaTable;
};

// 軸並行ボックス
struct AABB
{
	AABB();
	AABB(const VECTOR& min, const VECTOR& max);

	// ボックスの8頂点を再計算する関数

	VECTOR m_min;
	VECTOR m_max;
	VECTOR m_vertex[8];

	bool m_isRotaTable;
};