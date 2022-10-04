#include "pch.h"

Gradation::Gradation()
{
	// 処理無し
}

Gradation::~Gradation()
{
	// 処理無し
}

void Gradation::Start()
{
	m_var.Init(AssetManager::UseImage(AssetManager::ImageName::Gradation), 0, 0, 1920, 1080, 255.0f);
}

void Gradation::Update()
{
	// 処理無し
}

void Gradation::Draw()
{
	DrawGraph(m_var.x, m_var.y, m_var.handle, TRUE);
}
