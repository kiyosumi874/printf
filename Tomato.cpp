#include "pch.h"
#include "Tomato.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"

// @detail コンストラクタ
// @param position トマトを投げる人の位置
// @param dir 投げる人の向き
Tomato::Tomato()
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);  // 速さはまだ0
	m_startVelocity = VGet(20.0f, 1.0f, 20.0f);
	// AssetManagerからモデルデータをもらってくる
	m_modelHandle = MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Tomato));
	m_position = VGet(0.0f,0.0f,0.0f);

	m_time = 0.0f;
	m_gravity = 9.80665f;  // 平均重力
	m_deg = 30.0f;
	m_rad = m_deg * (DX_PI_F / 180.0f);

	m_dir = VGet(0.0f, 0.0f, 0.0f);

	// サイズ調整
	MV1SetScale(m_modelHandle, VGet(0.02f,0.02f,0.02f));
}

// @detail デストラクタ
Tomato::~Tomato()
{
	MV1DeleteModel(m_modelHandle);
}

//void Tomato::Init(VECTOR position, VECTOR dir)
//{
//}

void Tomato::Init(VECTOR position, VECTOR dir, Tag* tag)
{
	m_position = position;
	m_position = VAdd(m_position, VGet(0.0f, 15.0f, 0.0f));
	m_dir = dir;
	m_tag = tag;
}

// @detail 更新処理
void Tomato::Update()
{
	Move();
	m_position = VAdd(m_position, m_velocity);
	MV1SetPosition(m_modelHandle, m_position);
	auto pos = m_pParent->GetComponent<Transform>();
	pos->position = m_position;
}

// @detail 描画処理
void Tomato::Draw()
{
	MV1DrawModel(m_modelHandle);
}

// @detailトマトを投げてからの時間を返す
// @return m_time トマトを投げてからの時間
float Tomato::GetTime()
{
	return m_time;
}

// @detail 投げられた後の処理
void Tomato::Move()
{
	m_time += 0.01f;

	// 斜方投射公式による移動計算
	m_velocity.x = m_dir.x * (m_startVelocity.x * cos(m_rad) * m_time);
	m_velocity.y = m_startVelocity.y * sin(m_rad) * m_time - (0.5f * m_gravity * m_time * m_time);
	m_velocity.z = m_dir.z * (m_startVelocity.z * cos(m_rad) * m_time);
}
