#include "pch.h"
#include "Image.h"

// コンストラクタ
Image::Image()
{
}

// デストラクタ
Image::~Image()
{
	DeleteGraph(m_graphHandle);
}

void Image::Init(const VECTOR& pos, const VECTOR& extendRate, double angle, const char* fileName, bool transFlag, bool turnFlagX, bool turnFlagY)
{
	m_pos = pos;
	m_extendRate = extendRate;
	m_angle = angle * DX_PI / 180.0;
	m_addAngle = 0.0;
	m_alpha = 255.0f;
	m_graphHandle = LoadGraph(fileName);
	m_transFlag = transFlag;
	m_turnFlagX = turnFlagX;
	m_turnFlagY = turnFlagY;
	m_isDraw = true;
}

// 更新処理
void Image::Update()
{
	if (m_isDraw) { m_angle += m_addAngle; }
}

// 描画処理
void Image::Draw()
{
	if (m_isDraw)
	{ 
		if (m_alpha != 255.0f)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_alpha));
			DrawRotaGraph3F(m_pos.x, m_pos.y, 0.0f, 0.0f, m_extendRate.x, m_extendRate.y, m_angle, m_graphHandle, m_transFlag, m_turnFlagX, m_turnFlagY);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		else
		{
			DrawRotaGraph3F(m_pos.x, m_pos.y, 0.0f, 0.0f, m_extendRate.x, m_extendRate.y, m_angle, m_graphHandle, m_transFlag, m_turnFlagX, m_turnFlagY);
		}

	}
	
}
