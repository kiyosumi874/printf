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

	for (int i = 0; i < m_tomatos.size(); i++)
	{
		if (!m_tomatos[i])
		{
			delete(m_tomatos[i]);
		}
		m_tomatos.erase(std::cbegin(m_tomatos) + i);
		m_tomatos.shrink_to_fit();
	}
}

void Player::Update()
{
	Rotate();
	Input();

	// 移動処理
	m_position = VAdd(m_position, m_velocity);

	// 3Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_position);

	// 向きに合わせてモデルを回転
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_dir, rotYMat);

	// モデルに回転をセットする
	MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// トマト処理
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Update();
	}
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		// トマトの生存時間が5.0fを超えると削除
		if (m_tomatos[i]->GetTime() > 1.0f)
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

		// 入力方向は現在向いている向きと異なるか
		if (IsNearAngle(L_inputVec, m_dir))
		{
			m_dir = L_inputVec;
		}
		else
		{
			m_rotateNow = true;
			m_aimDir = L_inputVec;
		}

		m_velocity = L_inputVec;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}

	// トマト生成
	if (Input::IsDown1P(BUTTON_ID_B))
	{
		m_tomatos.push_back(new Tomato(m_position, m_dir));
	}
}

void Player::Rotate()
{
	// 回転が目標角度に到達すれば回転モード終了
	if (IsNearAngle(m_aimDir, m_dir))
	{
		m_dir = m_aimDir;
		m_rotateNow = false;
	}
	else
	{
		// 回転
		VECTOR interPolateDir;
		interPolateDir = RotateForAimVecYAxis(m_dir, m_aimDir, 10.0f);

		// 回転が目標角度を超えていないか
		VECTOR cross1, cross2;
		cross1 = VCross(m_dir, m_aimDir);
		cross2 = VCross(interPolateDir, m_aimDir);

		// 目標角度を超えたら終了
		if (cross1.y * cross2.y < 0.0f)
		{
			interPolateDir = m_aimDir;
			m_rotateNow = false;
		}
		// 目標ベクトルに10度だけ近づえた角度
		m_dir = interPolateDir;
	}
}
