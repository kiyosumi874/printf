#pragma once
#include <list>
#include "Object.h"
#include "Tag.h"

class Collider : public Component
{
public:
	Collider();
	~Collider();

	void Init(std::list<Object*>* objectLists);		// �V�[���̃I�u�W�F�N�g���X�g���Q�Ɠn���ł݂�
	void Update();
	void CollisionCheck();
	void Shot(VECTOR position, VECTOR dir, Tag* tag);
	double GetDistance(VECTOR& pos1, VECTOR& pos2);
	const bool& Getflag() const { return flag; }
	const ObjectTag& GetTag()const { return tag; }

	bool flag;
	float width;
	ObjectTag tag;
private:
	std::list<Object*>* copyObjectList;
	class HitEffect* m_HitEffect;
};

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