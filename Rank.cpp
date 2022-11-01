#include "pch.h"
#include "Rank.h"
#include "Object.h"
#include "Image.h"

Rank::Rank()
	: m_index(0)
	, m_pImage(nullptr)
	, m_position(VGet(0.0f,0.0f,0.0f))
	, m_scale(VGet(0.0f,0.0f,0.0f))
	, m_flag(false)
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
		img->Init(VGet(850.0f, 120.0f, 0.0f), VGet(0.7f, 0.7f, 0.7f), 0.0f, "data/rank/hukidasi.png");
		img->SetAlpha(230);
		m_pImage = m_pParent->AddComponent<Image>();
		m_pImage->Init(m_position = VGet(880.0f, 160.0f, 0.0f), m_scale = VGet(0.5f, 0.5f, 0.5f), 0.0f, "data/rank/ranking_1.png");

		m_index = 1;
	}
		break;
	case 2:
	{
		auto img = m_pParent->AddComponent<Image>();
		img->Init(VGet(380.0f, 140.0f, 0.0f), VGet(0.6f, 0.6f, 0.6f), 0.0f, "data/rank/hukidasi.png");
		img->SetAlpha(230);
		m_pImage = m_pParent->AddComponent<Image>();
		m_pImage->Init(m_position = VGet(410.0f, 170.0f, 0.0f), m_scale = VGet(0.4f, 0.4f, 0.4f), 0.0f, "data/rank/ranking_2.png");

		m_index = 2;
	}
		break;
	case 3:
	{
		auto img = m_pParent->AddComponent<Image>();
		img->Init(VGet(1380.0f, 120.0f, 0.0f), VGet(0.55f, 0.55f, 0.55f), 0.0f, "data/rank/hukidasi.png");
		img->SetAlpha(230);
		m_pImage = m_pParent->AddComponent<Image>();
		m_pImage->Init(m_position = VGet( 1420.0f, 170.0f, 0.0f), m_scale = VGet(0.3f, 0.3f, 0.3f), 0.0f, "data/rank/ranking_3.png");

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
		auto posX = m_position.x;
		auto posY = m_position.y;
		posX = posX + (posY * (1.5f - size)) - posY;
		posY = posY * (1.5f - size);
		if (size < 0.4f)
		{
			m_flag = true;
		}
		if (size > 0.55f)
		{
			m_flag = false;
		}
		if (m_flag)
		{
			size += 0.0015f;
		}
		else
		{
			size -= 0.0015f;
		}

		m_scale = VGet(size, size, size);
		m_pImage->SetExtendRate(m_scale);
		m_pImage->SetPos(VGet(posX, posY, m_position.z));
	}

	if (m_index == 2)
	{
		auto size = m_scale.x;
		auto posX = m_position.x;
		auto posY = m_position.y;
		posX = posX + (posY * (1.5f - size)) - posY - 10;
		posY = posY * (1.5f - size);
		if (size < 0.3f)
		{
			m_flag = true;
		}
		if (size > 0.40f)
		{
			m_flag = false;
		}
		if (m_flag)
		{
			size += 0.001f;
		}
		else
		{
			size -= 0.001f;
		}

		m_scale = VGet(size, size, size);
		m_pImage->SetExtendRate(m_scale);
		m_pImage->SetPos(VGet(posX, posY, m_position.z));
	}

	//if (m_index == 3)
	//{
	//	auto size = m_scale.x;
	//	auto posX = m_position.x;
	//	auto posY = m_position.y;
	//	posX = posX + (posY * (1.5f - size)) - posY - 30;
	//	posY = posY * (1.5f - size);
	//	if (size < 0.2f)
	//	{
	//		m_flag = true;
	//	}
	//	if (size > 0.35f)
	//	{
	//		m_flag = false;
	//	}
	//	if (m_flag)
	//	{
	//		size += 0.001f;
	//	}
	//	else
	//	{
	//		size -= 0.001f;
	//	}

	//	m_scale = VGet(size, size, size);
	//	m_pImage->SetExtendRate(m_scale);
	//	m_pImage->SetPos(VGet(posX, posY, m_position.z));
	//}
}

void Rank::Draw()
{
}
