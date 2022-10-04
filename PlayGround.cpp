#include "pch.h"
#include "ModelBase.h"
#include "Component.h"

PlayGround::PlayGround()
	: m_Pos(VGet(0.0f, -10.0f, 0.0f))
	, m_Scale(VGet(5.0f, 1.0f, 5.0f))
{
	// 初期化（使うモデル、ポジション、回転率、拡大率）
	m_var.Init(AssetManager::UseModel(AssetManager::ModelName::Ground), m_Pos, VGet(0.0f, 0.0f, 0.0f), m_Scale);
	MV1SetScale(m_var.handle, m_var.scale);         // 拡大率
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);  // 回転率
	MV1SetPosition(m_var.handle, m_var.pos);        // ポジション
}

PlayGround::~PlayGround()
{
	// 処理無し
}

void PlayGround::Start()
{
	// 処理無し
}

void PlayGround::Update()
{
	// 処理無し
}

void PlayGround::Draw()
{
	// 床の描画
	MV1DrawModel(m_var.handle);
}
