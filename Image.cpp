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
		DrawRotaGraph3F(m_pos.x, m_pos.y, 0.0f, 0.0f, m_extendRate.x, m_extendRate.y, m_angle, m_graphHandle, m_transFlag, m_turnFlagX, m_turnFlagY);
	}
	
}
