#include "pch.h"

Gradation::Gradation()
{
	// ��������
}

Gradation::~Gradation()
{
	// ��������
}

void Gradation::Start()
{
	m_var.Init(AssetManager::UseImage(AssetManager::ImageName::Gradation), 0, 0, 1920, 1080, 255.0f);
}

void Gradation::Update()
{
	// ��������
}

void Gradation::Draw()
{
	DrawGraph(m_var.x, m_var.y, m_var.handle, TRUE);
}
