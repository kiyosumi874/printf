#include "pch.h"
#include "Player.h"
#include "Tomato.h"
#include "TomatoWall.h"
#include "ModelManager.h"

Player::Player(ObjectTag tag, VECTOR position)
	: m_angle(0.0f)
	, m_rotateNow(false)
	, m_bulletNum(10)
	, m_bulletCapacity(10)
{
	m_position = position;
	m_tag = tag;

	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3Dモデルの読み込み
	ModelManager* model = new ModelManager();
	srand(rand() % 100);
	int modelNum = rand() % MODEL_NUM;
	m_modelHandle = model->GetModelData(modelNum);
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;

	// アニメーション準備
	m_animType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
	m_animTime = 0.0f;

	// ?G?t?F?N?g?????
	m_effect = new Effect("data/effect/hit/ToonHit.efkefc");
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

	// アニメーション処理
	ChangeAnimation();
	m_animTime += 0.3f;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}
	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);

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
	SetUseLighting(false);
	MV1DrawModel(m_modelHandle);
	// トマト描画
	for (int i = 0; i < m_tomatos.size(); i++)
	{
		m_tomatos[i]->Draw();
	}
	SetUseLighting(true);
	DrawFormatString(200, 0, GetColor(255, 255, 255), "PlayerBulletNum:%d", m_bulletNum);
#ifdef _DEBUG

#endif // _DEBUG

}

void Player::Input()
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
	if (m_tag == ObjectTag::Team1)
	{
		// 入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD2, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_angle += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_angle -= 0.01f;
		}

		// 前に進む
		if (Input::IsPress2P(BUTTON_ID_UP))
		{
			front.x = sinf(m_angle);
			front.z = cosf(m_angle);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// 後ろに進む
		if (Input::IsPress2P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_angle) * -1.0f;
			rear.z = cosf(m_angle) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// 右に進む
		if (Input::IsPress2P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_angle - addRad);
			right.z = cosf(m_angle - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// 左に進む
		if (Input::IsPress2P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_angle + addRad);
			left.z = cosf(m_angle + addRad);
			inputVec = VAdd(left, inputVec);
			input = true;
		}
	}

	// 2Pの操作
	if (m_tag == ObjectTag::Team2)
	{
		// 入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD1, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_angle += 0.01f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_angle -= 0.01f;
		}

		// 前に進む
		if (Input::IsPress1P(BUTTON_ID_UP))
		{
			front.x = sinf(m_angle);
			front.z = cosf(m_angle);
			inputVec = VAdd(front, inputVec);
			input = true;
		}

		// 後ろに進む
		if (Input::IsPress1P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_angle) * -1.0f;
			rear.z = cosf(m_angle) * -1.0f;
			inputVec = VAdd(rear, inputVec);
			input = true;
		}

		// 右に進む
		if (Input::IsPress1P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_angle - addRad);
			right.z = cosf(m_angle - addRad);
			inputVec = VAdd(right, inputVec);
			input = true;
		}

		// 左に進む
		if (Input::IsPress1P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_angle + addRad);
			left.z = cosf(m_angle + addRad);
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
		m_moveFlag = true;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}

	// トマト生成(Playerの回転処理が終わった後生成(上だとプレイヤーの向きにならず少しずれる))
	if (Input::IsDown1P(BUTTON_ID_R) && m_bulletNum > 0)
	{
		m_bulletNum--;
		//m_tomatos.push_back(new Tomato(m_position, m_dir));
		
    
		m_effect->PlayEffect(m_position);
	}

	// トマトを限界まで持っていないとき、トマトの壁からトマトを回収
	if (Input::IsDown1P(BUTTON_ID_B) && m_bulletNum < m_bulletCapacity)
	{
		TomatoCollect();
	}
}

void Player::Rotate()
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

// @detail トマト回収処理
void Player::TomatoCollect()
{
	int objectNum = 0;
	float distance = 0;
	for (int i = 0; i < m_tomatoWall.size(); i++)
	{
		// そのトマトの壁にトマトはあるのか
		if (m_tomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// どのトマトの壁かを調べる
			VECTOR gPos = m_tomatoWall[i]->GetPosition();
			distance = GetDistance(gPos, m_position);

			// 距離が負の値なら正の値に変える
			if (distance < 0.0f)
			{
				distance = distance * -1.0f;
			}

			// 範囲に入っているトマトの壁からトマトを回収
			if (distance < m_tomatoWall[i]->GetWidthDistance())
			{
				m_bulletNum++;
				m_tomatoWall[i]->DecreaseAllTomatoNum();
				break;
			}
		}
	}
}

void Player::ChangeAnimation()
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

// @detail 自身と他のオブジェクトの距離を出す
double Player::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}