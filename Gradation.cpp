#include "pch.h"

Gradation::Gradation()
{
	// ˆ—–³‚µ
}

Gradation::~Gradation()
{
	// ˆ—–³‚µ
}

void Gradation::Start()
{
	m_var.Init(AssetManager::UseImage(AssetManager::ImageName::Gradation), 0, 0, 1920, 1080, 255.0f);
}

void Gradation::Update()
{
	// ˆ—–³‚µ
}

void Gradation::Draw()
{
	DrawGraph(m_var.x, m_var.y, m_var.handle, TRUE);
}
