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
	m_var.Init(AssetManager::UseImage(AssetManager::ImageName::Gradation), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 255.0f);
}

void Gradation::Update()
{
	// 処理無し
}

void Gradation::Draw()
{
	DrawExtendGraph(m_var.x, m_var.y, m_var.width, m_var.height, m_var.handle, TRUE);
}
