#include "pch.h"
#include "Human.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"
#include "Collider.h"
#include "ModelManager.h"
#include "Tomato.h"

Human::Human()
	: m_rotateNow(false)
	, m_moveFlag(false)
{
	m_pTransform = nullptr;
	m_pTag = nullptr;

	m_modelHandle = MV1LoadModel("data/character/man1.mv1");
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3Dモデルの読み込み
	//ModelManager* model = new ModelManager();
	//srand(rand() % 100);
	//int modelNum = rand() % MODEL_NUM;
	//m_modelHandle = model->GetModelData(modelNum);
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;

	// アニメーション準備
	m_animType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
	m_animTime = 0.0f;
}

Human::~Human()
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

void Human::Start()
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
	m_pTransform->position;
	m_pTransform->position = VAdd(m_pTransform->position, m_velocity);

	// 3Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_pTransform->position);

	// 向きに合わせてモデルを回転
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_dir, rotYMat);

	// モデルに回転をセットする
	MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// アニメーション処理
	ChangeAnimation();
	m_animTime += 0.3f;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}
	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);

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

void Human::Draw()
{
	// 3Dモデルの描画
	SetUseLighting(false);
	MV1DrawModel(m_modelHandle);
	// トマト描画
	//for (int i = 0; i < m_tomatos.size(); i++)
	//{
	//	m_tomatos[i]->Draw();
	//}
	SetUseLighting(true);
	auto pos = m_pTransform->position;
	int t = 0;
	auto collider = m_pParent->GetComponent<Collider>();
	if (collider->Getflag()) 
	{ 
		if (collider->tag == ObjectTag::Enemy) { t = 1; }
		if (collider->tag == ObjectTag::tomato) { t = 2; }
		if (collider->tag == ObjectTag::Player2) { t = 3; }
	}
	printfDx("x:%f y:%f z:%f flag:%d\n", pos.x, pos.y, pos.z, t);
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

	m_moveFlag = false;

	// 1Pの操作
	if (m_pTag->tag == ObjectTag::Player1)
	{
		// 入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD2, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_pTransform->rotate.y += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_pTransform->rotate.y -= 0.01f;
		}

		// 前に進む
		if (Input::IsPress2P(BUTTON_ID_UP))
		{
			front.x = sinf(m_pTransform->rotate.y);
			front.z = cosf(m_pTransform->rotate.y);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// 後ろに進む
		if (Input::IsPress2P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_pTransform->rotate.y) * -1.0f;
			rear.z = cosf(m_pTransform->rotate.y) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// 右に進む
		if (Input::IsPress2P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_pTransform->rotate.y - addRad);
			right.z = cosf(m_pTransform->rotate.y - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// 左に進む
		if (Input::IsPress2P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_pTransform->rotate.y + addRad);
			left.z = cosf(m_pTransform->rotate.y + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}

		// トマト生成(Playerの回転処理が終わった後生成(上だとプレイヤーの向きにならず少しずれる))
		if (Input::IsDown2P(BUTTON_ID_R)/* && m_bulletNum > 0*/)
		{
			//m_bulletNum--;
			auto pos = m_pParent->GetComponent<Transform>()->position;
			m_pParent->GetComponent<Collider>()->Shot(pos, m_dir, m_pParent->GetComponent<Tag>());
			//m_effect->PlayEffect(m_position);
		}
	}

	// 2Pの操作
	if (m_pTag->tag == ObjectTag::Player2)
	{
		// 入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD1, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_pTransform->rotate.y += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_pTransform->rotate.y -= 0.01f;
		}

		// 前に進む
		if (Input::IsPress1P(BUTTON_ID_UP))
		{
			front.x = sinf(m_pTransform->rotate.y);
			front.z = cosf(m_pTransform->rotate.y);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// 後ろに進む
		if (Input::IsPress1P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_pTransform->rotate.y) * -1.0f;
			rear.z = cosf(m_pTransform->rotate.y) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// 右に進む
		if (Input::IsPress1P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_pTransform->rotate.y - addRad);
			right.z = cosf(m_pTransform->rotate.y - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// 左に進む
		if (Input::IsPress1P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_pTransform->rotate.y + addRad);
			left.z = cosf(m_pTransform->rotate.y + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}

		// トマト生成(Playerの回転処理が終わった後生成(上だとプレイヤーの向きにならず少しずれる))
		if (Input::IsDown1P(BUTTON_ID_R)/* && m_bulletNum > 0*/)
		{
			//m_bulletNum--;
			auto pos = m_pParent->GetComponent<Transform>()->position;
			m_pParent->GetComponent<Collider>()->Shot(pos, m_dir, m_pParent->GetComponent<Tag>());
			//m_effect->PlayEffect(m_position);
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
		m_moveFlag = true;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}

	if (m_pParent->GetComponent<Collider>()->flag)
	{
		m_pTransform->position = VSub(m_pTransform->position, VScale(inputVec, 2.5f));
		m_velocity = VGet(0.0f, 0.0f, 0.0f);
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

void Human::ChangeAnimation()
{
	// アニメーション処理
	if (!m_moveFlag && m_animType != Anim::Idle)  // 止まるアニメーション
	{
		m_animTime = 0.0f;
		m_animType = Anim::Idle;
		MV1DetachAnim(m_modelHandle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
		m_animTime = 0.0f;
	}
	else if (m_moveFlag && m_animType != Anim::Run)  // 走るアニメーション
	{
		m_animTime = 0.0f;
		m_animType = Anim::Run;
		MV1DetachAnim(m_modelHandle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
		m_animTime = 0.0f;
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
