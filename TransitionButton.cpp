#include "pch.h"

TransitionButton::TransitionButton()
	: m_alphaFlag(false)
{
	// 処理無し
}

TransitionButton::~TransitionButton()
{
	// 処理無し
}

void TransitionButton::Start()
{
	m_var.Init(AssetManager::UseImage(AssetManager::ImageName::TransitionButton), SCREEN_WIDTH - 830, 950, 799, 96, 100.0f);
}

void TransitionButton::Update()
{
	if (260.0f < m_var.alpha)
	{
		m_alphaFlag = true;
	}
	if (80.0f > m_var.alpha)
	{
		m_alphaFlag = false;
	}
	if (m_alphaFlag)
	{
		m_var.alpha -= 1.0f;
	}
	else
	{
		m_var.alpha += 1.0f;
	}
}

void TransitionButton::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_var.alpha);
	DrawExtendGraph(m_var.x, m_var.y, m_var.x + m_var.width, m_var.y + m_var.height, m_var.handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255.0f);
}
