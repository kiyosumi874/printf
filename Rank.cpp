#include "pch.h"
#include "Rank.h"
#include "Object.h"
#include "Image.h"

Rank::Rank()
	: m_index(0)
	, m_pImage(nullptr)
	, m_scale(VGet(0.0f,0.0f,0.0f))
{
}

Rank::~Rank()
{
}

void Rank::Init(int index)
{
	switch (index)
	{
	case 1:
	{
		auto img = m_pParent->AddComponent<Image>();
		img->Init(VGet(850.0f, 130.0f, 0.0f), VGet(0.7f, 0.7f, 0.7f), 0.0f, "data/rank/hukidasi.png");
		img->SetAlpha(230);
		m_pImage = m_pParent->AddComponent<Image>();
		m_pImage->Init(VGet(880.0f, 160.0f, 0.0f), m_scale = VGet(0.5f, 0.5f, 0.5f), 0.0f, "data/rank/ranking_1.png");

		m_index = 1;
	}
		break;
	case 2:
	{
		auto img = m_pParent->AddComponent<Image>();
		img->Init(VGet(380.0f, 140.0f, 0.0f), VGet(0.6f, 0.6f, 0.6f), 0.0f, "data/rank/hukidasi.png");
		img->SetAlpha(230);
		m_pImage = m_pParent->AddComponent<Image>();
		m_pImage->Init(VGet(410.0f, 180.0f, 0.0f), VGet(0.4f, 0.4f, 0.4f), 0.0f, "data/rank/ranking_2.png");

		m_index = 2;
	}
		break;
	case 3:
	{
		auto img = m_pParent->AddComponent<Image>();
		img->Init(VGet(1380.0f, 120.0f, 0.0f), VGet(0.55f, 0.55f, 0.55f), 0.0f, "data/rank/hukidasi.png");
		img->SetAlpha(230);
		m_pImage = m_pParent->AddComponent<Image>();
		m_pImage->Init(VGet(1420.0f, 170.0f, 0.0f), VGet(0.3f, 0.3f, 0.3f), 0.0f, "data/rank/ranking_3.png");

		m_index = 3;
	}
		break;
	default:
		break;
	}
}

void Rank::Start()
{
}

void Rank::Update()
{
	if (m_index == 1)
	{
		auto size = m_scale.x;
		if (size > 0.4f)
		{
			size = 0.5f;
		}
		if (size > 0.5f)
		{

		}

		m_scale = VGet(size, size, size);
		m_pImage->SetExtendRate(m_scale);
	}
}

void Rank::Draw()
{
}
