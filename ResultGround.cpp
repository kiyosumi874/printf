#include "pch.h"
#include "ResultGround.h"

ResultGround::ResultGround()
    : m_rotate(0.0f)
{
	// 処理なし
}

ResultGround::~ResultGround()
{
	// 処理なし
}

void ResultGround::Start()
{
	// 初期化（使うモデル、ポジション、回転率、拡大率）
	m_var.Init(AssetManager::UseModel(AssetManager::ModelName::Ground), VGet(0.0f, -1.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f));
	MV1SetScale(m_var.handle, m_var.scale);         // 拡大率
	MV1SetRotationXYZ(m_var.handle, m_var.rotate);  // 回転率
	MV1SetPosition(m_var.handle, m_var.pos);        // ポジション
}

void ResultGround::Update()
{
	// 処理なし
}

void ResultGround::Draw()
{
	// 床の描画
	MV1DrawModel(m_var.handle);
}
