#include "pch.h"

Logo::Logo()
{
	// ˆ—–³‚µ
}

Logo::~Logo()
{
	// ˆ—–³‚µ
}

void Logo::Init()
{
	m_var.InitImageVar(AssetManager::UseImage(AssetManager::ImageName::Logo), -60, -60, 1200 * 2 / 3, 844 * 2 / 3, 255.0f);
}

void Logo::Update()
{
	// ˆ—–³‚µ
}

void Logo::Draw()
{
	DrawExtendGraph(m_var.x, m_var.y, m_var.x + m_var.width, m_var.y + m_var.height, m_var.handle, TRUE);
}
