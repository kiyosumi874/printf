#include "pch.h"
#include "Player.h"

Player::Player()
	: m_playerModelHandle(MV1LoadModel("data/Player/IronMan.mv1"))
{
}

Player::~Player()
{
}

void Player::Update()
{

}

void Player::Draw()
{
	MV1DrawModel(m_playerModelHandle);
}
