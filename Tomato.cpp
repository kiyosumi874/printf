#include "pch.h"
#include <math.h>
#include "Tomato.h"

// @detail コンストラクタ
// @param position トマトを投げる人の位置
// @param dir 投げる人の向き
Tomato::Tomato(VECTOR& position, VECTOR& dir)
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);  // 速さはまだ0
	m_startVelocity = VGet(1.0f, 1.0f, 1.0f);
	m_modelHandle = MV1LoadModel("data/Tomato/Tomato.mv1");
	m_position = position;
	m_position = VAdd(m_position, VGet(0.0f, 10.0f, 0.0f));

	m_time = 0.0f;
	m_gravity = 9.80665f;  // 平均重力値で初期化
	m_deg = 20.0f;
	m_rad = m_deg * (DX_PI_F / 180.0f);
	m_dir = dir;

	// サイズ調整
	MV1SetScale(m_modelHandle, VGet(0.02f,0.02f,0.02f));
}

// @detail デストラクタ
Tomato::~Tomato()
{
	MV1DeleteModel(m_modelHandle);
}

// @detail 更新処理
void Tomato::Update()
{
	Move();
	m_position = VAdd(m_position, m_velocity);
	MV1SetPosition(m_modelHandle, m_position);
}

// @detail 描画処理
void Tomato::Draw()
{
	int result = MV1DrawModel(m_modelHandle);
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

	m_velocity.y = m_startVelocity.y * cos(m_rad) * m_time;
	m_velocity.z = m_startVelocity.z * sin(m_rad) * m_time - (0.5f * m_gravity * m_time * m_time);
}
