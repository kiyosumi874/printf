#pragma once

// �Փˏ��
struct CollisionInfo
{
	VECTOR m_collisionPoint;	// �Փ˓_
	VECTOR m_fixVec;			// �����߂��x�N�g��
	VECTOR m_hitNormal;			// �Փ˓_�ł̖@��
};

// ����
struct Sphere
{
	Sphere(const VECTOR& center, float radius);
	bool Contains(const VECTOR& point) const;

	VECTOR m_center;
	float m_radius;
};

// ����
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

// �����s�{�b�N�X
struct AABB
{
	AABB();
	AABB(const VECTOR& min, const VECTOR& max);

	// �{�b�N�X��8���_���Čv�Z����֐�

	VECTOR m_min;
	VECTOR m_max;
	VECTOR m_vertex[8];

	bool m_isRotaTable;
};