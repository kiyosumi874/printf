#include "pch.h"
#include "Tomato.h"

// @detail コンストラクタ
// @param tag オブジェクトの種類
// @param position オブジェクトの位置
Tomato::Tomato(ObjectTag tag, VECTOR position)
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);  // 速さはまだ0
	m_modelHandle = MV1LoadModel("data/Tomato/Tomato.mv1");

	m_time = 0.0f;
	m_gravity = 9.80665f;  // 平均重力値で初期化
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
	VAdd(m_position, m_velocity);
	MV1SetPosition(m_modelHandle, m_position);
}

// @detail 描画処理
void Tomato::Draw()
{
	MV1DrawModel(m_modelHandle);
}

// @detail 投げられた後の処理
void Tomato::Move()
{
	// GameObjectマージ後追加
}
