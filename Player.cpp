#include "pch.h"
#include "Player.h"

Player::Player(ObjectTag tag, VECTOR position)
	: m_rotateNow(false)
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3Dモデルの読み込み
	m_modelHandle = MV1LoadModel("data/Player/IronMan.mv1");

	m_dir = VGet(1.0f, 0.0f, 0.0f);
	m_aimDir = m_dir;
}

Player::~Player()
{
	MV1DeleteModel(m_modelHandle);
}

void Player::Update()
{
	Rotate();
	Input();

	// 移動処理
	VAdd(m_position, m_velocity);

	// 3Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_position);
}

void Player::Draw()
{
	// 3Dモデルの描画
	MV1DrawModel(m_modelHandle);
}

void Player::Input()
{
	// 前後左右
	VECTOR L_front = { 0.0f,0.0f,1.0f };
	VECTOR L_rear = { 0.0f,0.0f,-1.0f };
	VECTOR L_left = { -1.0f,0.0f,0.0f };
	VECTOR L_right = { 1.0f,0.0f,0.0f };

	VECTOR L_inputVec = VGet(0.0f, 0.0f, 0.0f);	// 押した合計座標取得用変数

	bool L_input = false;	// 入力したか判定用

	// 前に進む
	if (Input::IsPress(PAD_ID_UP))
	{
		L_inputVec = VAdd(L_front, L_inputVec);
		L_input = true;
	}

	// 後ろに進む
	if (Input::IsPress(PAD_ID_DOWN))
	{
		L_inputVec = VAdd(L_rear, L_inputVec);
		L_input = true;
	}

	// 右に進む
	if (Input::IsPress(PAD_ID_RIGHT))
	{
		L_inputVec = VAdd(L_right, L_inputVec);
		L_input = true;
	}

	// 左に進む
	if (Input::IsPress(PAD_ID_LEFT))
	{
		L_inputVec = VAdd(L_left, L_inputVec);
		L_input = true;
	}

	// 入力有（加速）・入力無（減速）
	if (L_input)
	{

	}
}

void Player::Rotate()
{
}
