#pragma once

// 衝突情報
class CollisionInfo
{
public:
	CollisionInfo()
	{
		m_collisionPoint = VGet(0.0f, 0.0f, 0.0f);
		m_fixVec = VGet(0.0f, 0.0f, 0.0f);
		m_hitNormal = VGet(0.0f, 0.0f, 0.0f);
	}

	VECTOR m_collisionPoint; // 衝突点
	VECTOR m_fixVec;         // 押し戻しベクトル
	VECTOR m_hitNormal;      // 衝突点での法線

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
	CollisionType m_collType;  // オブジェクトが持っているコライダーの種類
};

// 球体
class Sphere
{
public:
	// @param コンストラクタ
	// center 当たり判定の中心  radius 中心からの半径
	Sphere(const VECTOR& center, float radius);

	// @param コライダーの位置の更新
	// center 当たり判定の中心
	void UpdateSphere(const VECTOR& center);

	// @param 半径の大きさの更新
	// radius 中心からの半径
	void Radius(float radius);

	VECTOR m_center;                                                  // 中心位置
	float m_radius;                                                    // 半径
};

// ボックス(Box)
class Box
{
public:
	// @param コンストラクタ
	// pos 当たり判定の中心  boxScale boxのサイズ
	Box(const VECTOR& pos, const VECTOR& boxScale);

	// @param モデル読み込み時の最小最大の点を求めるのに使用          
	// point 当たり判定の中心
	void InitMinMax(const VECTOR& point) { m_min = m_max = point; }
	// @param ボックスの8頂点を再計算する関数
	void CalcVertex();
	// @param 点との最小距離を求める
	// point 当たり判定の中心
	float MinDistSq(const VECTOR& point) const;
	// @param コライダー位置の更新処理
	// center 当たり判定の中心
	void UpdateMinMax(const VECTOR& center);
	// @param サイズ設定＆変更
	// x x軸の大きさ  y y軸の大きさ  z 軸の大きさ (サイズが異なる場合)
	void Scaling(float x, float y, float z);
	// @param サイズ設定＆変更
	// scale 大きさ(全ての方向にサイズが同じ)
	void Scaling(float scale);

	VECTOR m_center;                                                  // ボックスの中心
	VECTOR m_min;                                                     // ボックス最小座標
	VECTOR m_max;                                                     // ボックス最大座標 
	VECTOR m_vertex[8];                                               // ボックスの頂点

	VECTOR m_scale;                                                   // ボックスのサイズ
};

// 壁の当たり判定(Boxでとる)
class Wall
{
public:
	// @param コンストラクタ
	// b Boxクラスのポインタ
	Wall(const Box* b);
	// @param デストラクタ
	~Wall() { delete m_pWallBox; }

	// @param 壁の情報を作る
	// start 壁の開始点  end 壁の終了点  wallHeight 壁の高さ
	void CreateWall(const VECTOR& start, const VECTOR& end, float wallHeight);

	// @param Boxの頂点を設定＆修正
	void    CalcBox();

	Box* m_pWallBox;          // Boxクラスのポインタ変数
	VECTOR m_normal;          // 壁法線
	VECTOR m_start;           // 壁の開始点
	VECTOR m_end;             // 壁の終了点
	VECTOR m_wallVertex[4];   // 壁の頂点
	VECTOR mScale;            // 表示用x,y,zスケーリング係数 

	float  m_planeD;          // 壁面の平面方程式のd値
	float  m_zRotate;         // 表示用z軸回転
};

class Ground
{
public:
	// @param コンストラクタ
	// center コライダーの中心位置  upSize 中心から上側の大きさ  downSize 中心から下側の大きさ  sideSize 横の大きさ
	Ground(const VECTOR& center, const float upSize, const float downSize, const float sideSize);
	// @param デストラクタ
	~Ground() {};

	VECTOR m_center;    // 地面の中心
	float m_upSize;     // 中心から上側の大きさ
	float m_downSize;   // 中心から下側の大きさ
	float m_sideSize;   // 横の大きさ
};

// 世界の区切りを判定する当たり判定(球体でとる)
class World
{
public:
	// @param コンストラクタ
	// s Sphereクラスのポインタ
	World(const Sphere* s);
	// @param デストラクタ
	~World() { delete m_pSphere; }

	Sphere* m_pSphere;  // Sphereクラスのポインタ変数
};

bool Intersect(const Box& b1, const Box& b2, CollisionInfo& info);                                     
bool Intersect(const Box& b, const Sphere& s, CollisionInfo& info);                                    // @param BoxとSphereとの当たり判定
bool Intersect(const Box& b, const Wall& w, CollisionInfo& info);                                      // @param BoxとWallの当たり判定
bool Intersect(const Box& b, const Ground& g, CollisionInfo& info);                                    // @param BoxとGroundの当たり判定
bool Intersect(const Box& b, const World& w, CollisionInfo& info);                                     // @param BoxとWorldの当たり判定
bool Intersect(const Sphere& s, const Box& b, CollisionInfo& info);                                    // @param SphereとBoxとの当たり判定
bool Intersect(const Sphere& s1, const Sphere& s2, CollisionInfo& info);                               // @param Sphere同士の当たり判定
bool Intersect(const Sphere& s, const Wall& w, CollisionInfo& info);                                   // @param SphereとWallの当たり判定
bool Intersect(const Sphere& s, const Ground& g, CollisionInfo& info);                                 // @param SphereとGroundの当たり判定
bool Intersect(const Sphere& s, const World& w, CollisionInfo& info);                                  // @param SphereとWorldの当たり判定
bool Intersect(const Wall &w, const Box& b, CollisionInfo& info);                                      // @param BoxとWallの当たり判定
bool Intersect(const Wall& w, const Sphere& s, CollisionInfo& info);                                   // @param SphereとWallの当たり判定
bool Intersect(const Ground& g, const Box& b, CollisionInfo& info);                                    // @param GroundとBoxの当たり判定
bool Intersect(const Ground& g, const Sphere& s, CollisionInfo& info);                                 // @param GroundとSphereの当たり判定
bool Intersect(const World& w, const Box& b, CollisionInfo& info);                                     // @param BoxとWorldの当たり判定
bool Intersect(const World& w, const Sphere& s, CollisionInfo& info);                                  // @param WorldとSphereの当たり判定

void calcCollisionFixVec(const Box& box1, const Box& box2, VECTOR& calcFixVec);              // Boxのめり込み(Box)をもどす量を計算
void calcCollisionFixVec(const Box& box, const Sphere& sphere, VECTOR& calcFixVec);          // Boxのめり込み(Sphere)を戻す量を計算
void calcCollisionFixVec(const Box& box, const Wall& wall, VECTOR& calcFixVec);              // Boxのめり込み(Wall)を戻す量を計算
void calcCollisionFixVec(const Box& box, const World& world, VECTOR& calcFixVec);            // Boxのめり込み(World)を戻す量を計算
void calcCollisionFixVec(const Sphere& sphere, const Box& box, VECTOR& calcFixVec);          // Sphereのめり込み(Box)を戻す量を計算
void calcCollisionFixVec(const Sphere& sphere1, const Sphere& sphere2, VECTOR& calcFixVec);  // Sphereのめり込み(Sphere)を戻す量を計算
void calcCollisionFixVec(const Sphere& sphere, const Wall& wall, VECTOR& calcFixVec);        // Sphereのめり込み(Wall)を戻す量を計算
void calcCollisionFixVec(const Sphere& sphere, const World& world, VECTOR& calcFixVec);      // Sphereのめり込み(World)を戻す量を計算
void calcCollisionFixVec(const Wall& wall, const Box& box, VECTOR& calcFixVec);              // Wallのめり込み(Box)を戻す量を計算
void calcCollisionFixVec(const Wall& wall, const Sphere& sphere, VECTOR& calcFixVec);        // Wallのめり込み(Sphere)を戻す量を計算
void calcCollisionFixVec(const Ground& ground, const Box& box, VECTOR& calcFixVec);          // Groundのめり込み(Box)を戻す量を計算
void calcCollisionFixVec(const Ground& ground, const Sphere& sphere, VECTOR& calcFixVec);    // Groundのめり込み(Sphere)を戻す量を計算
void calcCollisionFixVec(const World& world, const Box& box, VECTOR& calcFixVec);            // Worldのめり込み(Box)を戻す量を計算
void calcCollisionFixVec(const World& world, const Sphere& sphere, VECTOR& calcFixVec);      // Worldのめり込み(Sphere)を戻す量を計算

// 当たり判定に使った数学関数
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