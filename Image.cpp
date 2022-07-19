#include "pch.h"
#include "Image.h"

// �R���X�g���N�^
Image::Image(const VECTOR& pos, const VECTOR& extendRate, double angle, const char* fileName, bool transFlag, bool turnFlagX = false, bool turnFlagY = false)
{
	m_pos = pos;
	m_extendRate = extendRate;
	m_angle = angle * DX_PI / 180.0;
	m_addAngle = 0.0;
	m_graphHandle = LoadGraph(fileName);
	m_transFlag = transFlag;
	m_turnFlagX = turnFlagX;
	m_turnFlagY = turnFlagY;
}

// �f�X�g���N�^
Image::~Image()
{
	DeleteGraph(m_graphHandle);
}

// �X�V����
void Image::Update()
{
	m_angle += m_addAngle;
}

// �`�揈��
void Image::Draw()
{
	DrawRotaGraph3F(m_pos.x, m_pos.y, 0.0f, 0.0f, m_extendRate.x, m_extendRate.y, m_angle, m_graphHandle, m_transFlag, m_turnFlagX, m_turnFlagY);
}
