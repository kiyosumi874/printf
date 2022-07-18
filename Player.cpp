#include "pch.h"
#include "Player.h"
#include "Tomato.h"

Player::Player(ObjectTag tag, VECTOR position)
	: m_rotateNow(false)
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3Dモデルの読み込み
	m_modelHandle = MV1LoadModel("data/player/hackadoll.pmx");

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
	m_position = VAdd(m_position, m_velocity);

	// 3Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_position);

	// トマト処理
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Update();
	}
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		// トマトの生存時間が5.0fを超えると削除
		if (m_tomatos[i]->GetTime() > 5.0f)
		{
			delete(m_tomatos[i]);
			m_tomatos.erase(std::cbegin(m_tomatos) + i);
			m_tomatos.shrink_to_fit();
		}
	}
}

void Player::Draw()
{
	// 3Dモデルの描画
	MV1DrawModel(m_modelHandle);

	// トマト描画
	for(int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Draw();
	}
}

void Player::Input()
{
	// トマト生成
	if (Input::IsDown1P(BUTTON_ID_B))
	{
		m_tomatos.push_back(new Tomato(m_position, m_dir));
	}

	// 前後左右
	VECTOR L_front = { 0.0f,0.0f,1.0f };
	VECTOR L_rear = { 0.0f,0.0f,-1.0f };
	VECTOR L_left = { -1.0f,0.0f,0.0f };
	VECTOR L_right = { 1.0f,0.0f,0.0f };

	VECTOR L_inputVec = VGet(0.0f, 0.0f, 0.0f);	// 押した合計座標取得用変数

	bool L_input = false;	// 入力したか判定用

	// 前に進む
	if (CheckHitKey(KEY_INPUT_UP))
	{
		L_inputVec = VAdd(L_front, L_inputVec);
		L_input = true;
	}

	// 後ろに進む
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		L_inputVec = VAdd(L_rear, L_inputVec);
		L_input = true;
	}

	// 右に進む
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		L_inputVec = VAdd(L_right, L_inputVec);
		L_input = true;
	}

	// 左に進む
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		L_inputVec = VAdd(L_left, L_inputVec);
		L_input = true;
	}

	// 入力有（加速）・入力無（減速）
	if (L_input)
	{
		// 左右・前後同時押しなどで入力ベクトルが0の時は無視
		if (VSquareSize(L_inputVec) < 0.5f)
		{
			return;
		}

		// 方向を正規化
		L_inputVec = VNorm(L_inputVec);

		m_velocity = VAdd(m_velocity, L_inputVec);
		if (m_velocity.x > 2.0f) { m_velocity.x = 2.0f; }
		if (m_velocity.x < -2.0f) { m_velocity.x = -2.0f; }
		if (m_velocity.z > 2.0f) { m_velocity.z = 2.0f; }
		if (m_velocity.z < -2.0f) { m_velocity.z = -2.0f; }
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}
}

void Player::Rotate()
{
}
