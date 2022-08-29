#include "pch.h"
#include "Human.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"

Human::Human()
	: m_rotateNow(false)
{
	m_pTransform = nullptr;
	m_pTag = nullptr;

	m_modelHandle = MV1LoadModel("data/character/man1.mv1");
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;
}

Human::~Human()
{
}

void Human::Update()
{
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if(m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	Rotate();	// 回転
	Input();	// 入力

	// 移動処理
	auto pos = m_pTransform->position;
	pos = VAdd(pos, m_velocity);

	// 3Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, pos);
	
	// 3Dモデルの大きさを設定
	MV1SetScale(m_modelHandle, m_pTransform->scale);

	// 向きに合わせてモデルを回転
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_dir, rotYMat);

	// モデルに回転をセットする
	MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void Human::Draw()
{
	MV1DrawModel(m_modelHandle);
	auto pos = m_pTransform->position;
	DrawSphere3D(pos, 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

void Human::Input()
{
	// 前後左右
	VECTOR front = { 0.0f,0.0f,1.0f };
	VECTOR rear = { 0.0f,0.0f,-1.0f };
	VECTOR left = { 1.0f,0.0f,0.0f };
	VECTOR right = { -1.0f,0.0f,0.0f };

	VECTOR inputVec = VGet(0.0f, 0.0f, 0.0f);	// 押した合計座標取得用変数

	float addRad = 1.58f;	// 加算する角度
	bool input = false;		// 入力したか判定用

	XINPUT_STATE inputState;
	auto angle = m_pTransform->rotate.y;

	// 1Pの操作
	if (m_pTag->tag == ObjectTag::Player1)
	{
		// 入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD2, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			angle += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			angle -= 0.01f;
		}

		// 前に進む
		if (Input::IsPress2P(BUTTON_ID_UP))
		{
			front.x = sinf(angle);
			front.z = cosf(angle);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// 後ろに進む
		if (Input::IsPress2P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(angle) * -1.0f;
			rear.z = cosf(angle) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// 右に進む
		if (Input::IsPress2P(BUTTON_ID_LEFT))
		{
			right.x = sinf(angle - addRad);
			right.z = cosf(angle - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// 左に進む
		if (Input::IsPress2P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(angle + addRad);
			left.z = cosf(angle + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}
	}

	// 2Pの操作
	if (m_pTag->tag == ObjectTag::Player2)
	{
		// 入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD1, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			angle += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			angle -= 0.01f;
		}

		// 前に進む
		if (Input::IsPress1P(BUTTON_ID_UP))
		{
			front.x = sinf(angle);
			front.z = cosf(angle);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// 後ろに進む
		if (Input::IsPress1P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(angle) * -1.0f;
			rear.z = cosf(angle) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// 右に進む
		if (Input::IsPress1P(BUTTON_ID_LEFT))
		{
			right.x = sinf(angle - addRad);
			right.z = cosf(angle - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// 左に進む
		if (Input::IsPress1P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(angle + addRad);
			left.z = cosf(angle + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}
	}

	// 入力有（加速）・入力無（減速）
	if (input)
	{
		// 左右・前後同時押しなどで入力ベクトルが0の時は無視
		if (VSquareSize(inputVec) < 0.5f)
		{
			return;
		}

		// 方向を正規化
		inputVec = VNorm(inputVec);

		// 入力方向は現在向いている向きと異なるか
		if (IsNearAngle(inputVec, m_dir))
		{
			m_dir = inputVec;
		}
		else
		{
			m_rotateNow = true;
			m_aimDir = inputVec;
		}

		m_velocity = inputVec;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}
}

void Human::Rotate()
{
	if (m_rotateNow)
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
}

bool Human::IsNearAngle(const VECTOR& v1, const VECTOR& v2)
{
	float dot = VDot(v1, v2);
	if (dot < 0.99f)
	{
		return true;
	}
	return false;
}

float Human::CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
{
	VECTOR axis;
	axis = VCross(nowVec, dirVec);
	if (axis.y < 0.0f)
	{
		return -1.0f;
	}
	return 1.0f;
}

VECTOR Human::RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity)
{
	// 角速度（度数）をラジアン角に変換、右回りか左回りかを調べる
	float rotRadian = (DX_PI_F * degreeVelocity / 180.0f);
	rotRadian *= CalcRotationDirectionYAxis(nowVec, aimVec);

	// Y軸回転行列を作成する
	MATRIX yRotMat = MGetRotY(rotRadian);

	// Y軸回転する
	VECTOR rotVec;
	rotVec = VTransform(nowVec, yRotMat);
	return rotVec;
}
