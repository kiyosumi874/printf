#pragma once

// �Փˏ��
class CollisionInfo
{
public:
	CollisionInfo()
	{
		m_collisionPoint = VGet(0.0f, 0.0f, 0.0f);
		m_fixVec = VGet(0.0f, 0.0f, 0.0f);
		m_hitNormal = VGet(0.0f, 0.0f, 0.0f);
	}

	VECTOR m_collisionPoint; // �Փ˓_
	VECTOR m_fixVec;         // �����߂��x�N�g��
	VECTOR m_hitNormal;      // �Փ˓_�ł̖@��

	enum class CollisionType
	{
		Begin,
		Box = Begin,
		Sphere,
		Wall,
		World,
		Ground,
		End
	};
	CollisionType m_collType;  // �I�u�W�F�N�g�������Ă���R���C�_�[�̎��
};

// ����
class Sphere
{
public:
	// @param �R���X�g���N�^
	// center �����蔻��̒��S  radius ���S����̔��a
	Sphere(const VECTOR& center, float radius);

	// @param �R���C�_�[�̈ʒu�̍X�V
	// center �����蔻��̒��S
	void UpdateSphere(const VECTOR& center);

	// @param ���a�̑傫���̍X�V
	// radius ���S����̔��a
	void Radius(float radius);

	VECTOR m_center;                                                  // ���S�ʒu
	float m_radius;                                                    // ���a
};

// �{�b�N�X(Box)
class Box
{
public:
	// @param �R���X�g���N�^
	// pos �����蔻��̒��S  boxScale box�̃T�C�Y
	Box(const VECTOR& pos, const VECTOR& boxScale);

	// @param ���f���ǂݍ��ݎ��̍ŏ��ő�̓_�����߂�̂Ɏg�p          
	// point �����蔻��̒��S
	void InitMinMax(const VECTOR& point) { m_min = m_max = point; }
	// @param �{�b�N�X��8���_���Čv�Z����֐�
	void CalcVertex();
	// @param �_�Ƃ̍ŏ����������߂�
	// point �����蔻��̒��S
	float MinDistSq(const VECTOR& point) const;
	// @param �R���C�_�[�ʒu�̍X�V����
	// center �����蔻��̒��S
	void UpdateMinMax(const VECTOR& center);
	// @param �T�C�Y�ݒ聕�ύX
	// x x���̑傫��  y y���̑傫��  z ���̑傫�� (�T�C�Y���قȂ�ꍇ)
	void Scaling(float x, float y, float z);
	// @param �T�C�Y�ݒ聕�ύX
	// scale �傫��(�S�Ă̕����ɃT�C�Y������)
	void Scaling(float scale);

	VECTOR m_center;                                                  // �{�b�N�X�̒��S
	VECTOR m_min;                                                     // �{�b�N�X�ŏ����W
	VECTOR m_max;                                                     // �{�b�N�X�ő���W 
	VECTOR m_vertex[8];                                               // �{�b�N�X�̒��_

	VECTOR m_scale;                                                   // �{�b�N�X�̃T�C�Y
};

// �ǂ̓����蔻��(Box�łƂ�)
class Wall
{
public:
	// @param �R���X�g���N�^
	// b Box�N���X�̃|�C���^
	Wall(const Box* b);
	// @param �f�X�g���N�^
	~Wall() { delete m_pWallBox; }

	// @param �ǂ̏������
	// start �ǂ̊J�n�_  end �ǂ̏I���_  wallHeight �ǂ̍���
	void CreateWall(const VECTOR& start, const VECTOR& end, float wallHeight);

	// @param Box�̒��_��ݒ聕�C��
	void    CalcBox();

	Box* m_pWallBox;          // Box�N���X�̃|�C���^�ϐ�
	VECTOR m_normal;          // �ǖ@��
	VECTOR m_start;           // �ǂ̊J�n�_
	VECTOR m_end;             // �ǂ̏I���_
	VECTOR m_wallVertex[4];   // �ǂ̒��_
	VECTOR mScale;            // �\���px,y,z�X�P�[�����O�W�� 

	float  m_planeD;          // �ǖʂ̕��ʕ�������d�l
	float  m_zRotate;         // �\���pz����]
};

class Ground
{
public:
	// @param �R���X�g���N�^
	// center �R���C�_�[�̒��S�ʒu  upSize ���S����㑤�̑傫��  downSize ���S���牺���̑傫��  sideSize ���̑傫��
	Ground(const VECTOR& center, const float upSize, const float downSize, const float sideSize);
	// @param �f�X�g���N�^
	~Ground() {};

	VECTOR m_center;    // �n�ʂ̒��S
	float m_upSize;     // ���S����㑤�̑傫��
	float m_downSize;   // ���S���牺���̑傫��
	float m_sideSize;   // ���̑傫��
};

// ���E�̋�؂�𔻒肷�铖���蔻��(���̂łƂ�)
class World
{
public:
	// @param �R���X�g���N�^
	// s Sphere�N���X�̃|�C���^
	World(const Sphere* s);
	// @param �f�X�g���N�^
	~World() { delete m_pSphere; }

	Sphere* m_pSphere;  // Sphere�N���X�̃|�C���^�ϐ�
};

bool Intersect(const Box& b1, const Box& b2, CollisionInfo& info);                                     
bool Intersect(const Box& b, const Sphere& s, CollisionInfo& info);                                    // @param Box��Sphere�Ƃ̓����蔻��
bool Intersect(const Box& b, const Wall& w, CollisionInfo& info);                                      // @param Box��Wall�̓����蔻��
bool Intersect(const Box& b, const Ground& g, CollisionInfo& info);                                    // @param Box��Ground�̓����蔻��
bool Intersect(const Box& b, const World& w, CollisionInfo& info);                                     // @param Box��World�̓����蔻��
bool Intersect(const Sphere& s, const Box& b, CollisionInfo& info);                                    // @param Sphere��Box�Ƃ̓����蔻��
bool Intersect(const Sphere& s1, const Sphere& s2, CollisionInfo& info);                               // @param Sphere���m�̓����蔻��
bool Intersect(const Sphere& s, const Wall& w, CollisionInfo& info);                                   // @param Sphere��Wall�̓����蔻��
bool Intersect(const Sphere& s, const Ground& g, CollisionInfo& info);                                 // @param Sphere��Ground�̓����蔻��
bool Intersect(const Sphere& s, const World& w, CollisionInfo& info);                                  // @param Sphere��World�̓����蔻��
bool Intersect(const Wall &w, const Box& b, CollisionInfo& info);                                      // @param Box��Wall�̓����蔻��
bool Intersect(const Wall& w, const Sphere& s, CollisionInfo& info);                                   // @param Sphere��Wall�̓����蔻��
bool Intersect(const Ground& g, const Box& b, CollisionInfo& info);                                    // @param Ground��Box�̓����蔻��
bool Intersect(const Ground& g, const Sphere& s, CollisionInfo& info);                                 // @param Ground��Sphere�̓����蔻��
bool Intersect(const World& w, const Box& b, CollisionInfo& info);                                     // @param Box��World�̓����蔻��
bool Intersect(const World& w, const Sphere& s, CollisionInfo& info);                                  // @param World��Sphere�̓����蔻��

void calcCollisionFixVec(const Box& box1, const Box& box2, VECTOR& calcFixVec);              // Box�̂߂荞��(Box)�����ǂ��ʂ��v�Z
void calcCollisionFixVec(const Box& box, const Sphere& sphere, VECTOR& calcFixVec);          // Box�̂߂荞��(Sphere)��߂��ʂ��v�Z
void calcCollisionFixVec(const Box& box, const Wall& wall, VECTOR& calcFixVec);              // Box�̂߂荞��(Wall)��߂��ʂ��v�Z
void calcCollisionFixVec(const Box& box, const World& world, VECTOR& calcFixVec);            // Box�̂߂荞��(World)��߂��ʂ��v�Z
void calcCollisionFixVec(const Sphere& sphere, const Box& box, VECTOR& calcFixVec);          // Sphere�̂߂荞��(Box)��߂��ʂ��v�Z
void calcCollisionFixVec(const Sphere& sphere1, const Sphere& sphere2, VECTOR& calcFixVec);  // Sphere�̂߂荞��(Sphere)��߂��ʂ��v�Z
void calcCollisionFixVec(const Sphere& sphere, const Wall& wall, VECTOR& calcFixVec);        // Sphere�̂߂荞��(Wall)��߂��ʂ��v�Z
void calcCollisionFixVec(const Sphere& sphere, const World& world, VECTOR& calcFixVec);      // Sphere�̂߂荞��(World)��߂��ʂ��v�Z
void calcCollisionFixVec(const Wall& wall, const Box& box, VECTOR& calcFixVec);              // Wall�̂߂荞��(Box)��߂��ʂ��v�Z
void calcCollisionFixVec(const Wall& wall, const Sphere& sphere, VECTOR& calcFixVec);        // Wall�̂߂荞��(Sphere)��߂��ʂ��v�Z
void calcCollisionFixVec(const Ground& ground, const Box& box, VECTOR& calcFixVec);          // Ground�̂߂荞��(Box)��߂��ʂ��v�Z
void calcCollisionFixVec(const Ground& ground, const Sphere& sphere, VECTOR& calcFixVec);    // Ground�̂߂荞��(Sphere)��߂��ʂ��v�Z
void calcCollisionFixVec(const World& world, const Box& box, VECTOR& calcFixVec);            // World�̂߂荞��(Box)��߂��ʂ��v�Z
void calcCollisionFixVec(const World& world, const Sphere& sphere, VECTOR& calcFixVec);      // World�̂߂荞��(Sphere)��߂��ʂ��v�Z

// �����蔻��Ɏg�������w�֐�
namespace CollMath
{
	const float m_pi = 3.1415926535f;
	const float m_twoPi = m_pi * 2.0f;
	const float m_piOver2 = m_pi / 2.0f;
	const float m_infinity = std::numeric_limits<float>::infinity();
	const float m_negInfinity = -std::numeric_limits<float>::infinity();
	const VECTOR m_unitX = VGet(1.0f, 0.0f, 0.0f);
	const VECTOR m_unitY = VGet(0.0f, 1.0f, 0.0f);
	const VECTOR m_unitZ = VGet(0.0f, 0.0f, 1.0f);

	template <typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template <typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template <typename T>
	double Distance(const T& a, const T& b)
	{
		double x = a.x - b.x;
		double y = a.y - b.y;
		double z = a.z - b.z;
		return sqrt(x * x + y * y + z * z);
	}

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	// Length squared of vector
	inline float LengthSq(const VECTOR& v)
	{
		return (v.x * v.x + v.y * v.y + v.z * v.z);
	}

	// Length of vector
	inline float Length(const VECTOR& v)
	{
		return (Sqrt(LengthSq(v)));
	}

	inline VECTOR Normalize(const VECTOR& v)
	{
		VECTOR vec = VGet(0.0f, 0.0f, 0.0f);
		float length = Length(v);
		vec.x /= length;
		vec.y /= length;
		vec.z /= length;
		return vec;
	}

	void CheckDistance(VECTOR& dis, const VECTOR& min, const VECTOR& max);
}