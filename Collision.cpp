#include "pch.h"
#include "Collision.h"

Sphere::Sphere(const VECTOR& center, float radius)
{
}

bool Sphere::Contains(const VECTOR& point) const
{
	return false;
}

Line::Line()
{
}

Line::Line(const VECTOR& start, const VECTOR& end)
{
}

AABB::AABB()
{
}

AABB::AABB(const VECTOR& min, const VECTOR& max)
{
}
