#include "pch.h"
#include "Player1.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"
#include "Tomato.h"
#include "TomatoWallManager.h"
#include "Score.h"
#include "Icon.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

Player1::Player1()
	: Human()
	, m_rotateNow(false)
{
	m_modelName = AssetManager::ModelName::Team1;

	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;

	// アニメーション準備
	m_animTime = 0.0f;
	m_animSpeed = 0.3f;
	m_throwSpeed = 1.2f;
	m_pickSpeed = 1.2f;
	m_moveFlag = true;
	m_throwFlag = false;
	m_pickFlag = false;
}

Player1::~Player1()
{
}

void Player1::Start()
{
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
	}
	if (m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	if (m_pBox == nullptr)
	{
		m_pBox = m_pParent->GetCollider<BoxCollider>();
		m_pBox->Init(m_var.pos, m_pBox->SetOwner(this), m_pTag, CollisionInfo::CollisionType::Box);
		m_pBox->SetOnCollisionFlag(true);
	}
	if (m_pSphere == nullptr)
	{
		m_pSphere = m_pParent->GetCollider<SphereCollider>();
		m_pSphere->Init(m_var.pos, m_pSphere->SetOwner(this), m_pTag, CollisionInfo::CollisionType::Sphere);
		m_pSphere->SetOnCollisionFlag(true);
	}
}

void Player1::Update()
{
	Rotate();	// 回転
	Input();	// 入力
	// アニメーション処理
	Animation();

	m_var.pos = m_pTransform->position;
	// 移動処理
	if (m_moveFlag)
	{
		m_pTransform->position = VAdd(m_pTransform->position, m_velocity);
		m_var.pos = m_pTransform->position;

		// 3Dモデルのポジション設定
		MV1SetPosition(m_var.handle, m_var.pos);
	}

	// 向きに合わせてモデルを回転
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_dir, rotYMat);

	// モデルに回転をセットする
	MV1SetRotationZYAxis(m_var.handle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	m_pIcon->SetOwnerPosition(m_var.pos);
	m_pBox->UpdatePosition(VGet(m_var.pos.x, m_var.pos.y + m_pBox->GetWorldBox()->m_scale.y / 2.0f, m_var.pos.z));
	m_pSphere->UpdatePosition(m_var.pos);
	m_pBox->CleanCollisionTag();
	m_pSphere->CleanCollisionTag();
}

void Player1::Draw()
{
	// 3Dモデルの描画
	SetUseLighting(false);
	MV1DrawModel(m_var.handle);
	m_pIcon->Draw();
	SetUseLighting(true);
}

void Player1::Input()
{
	m_inputVector = VGet(0.0f, 0.0f, 0.0f); // 押した合計座標取得用変数
	// 前後左右
	VECTOR front = { 0.0f,0.0f,1.0f };
	VECTOR rear = { 0.0f,0.0f,-1.0f };
	VECTOR left = { 1.0f,0.0f,0.0f };
	VECTOR right = { -1.0f,0.0f,0.0f };

	float addRad = 1.58f;	// 加算する角度
	bool input = false;		// 入力したか判定用

	XINPUT_STATE inputState;

	// 1Pの操作
	if (m_pTag->tag == ObjectTag::Team1)
	{
		// 入力状態を取得
		GetJoypadXInputState(DX_INPUT_PAD1, &inputState);

		if (CheckHitKey(KEY_INPUT_D) || inputState.ThumbRX > 2000.0f)
		{
			m_pTransform->rotate.y += 0.02f;
		}
		if (CheckHitKey(KEY_INPUT_A) || inputState.ThumbRX < -2000.0f)
		{
			m_pTransform->rotate.y -= 0.02f;
		}

		// 前に進む
		if (Input::IsPress1P(BUTTON_ID_UP))
		{
			front.x = sinf(m_pTransform->rotate.y);
			front.z = cosf(m_pTransform->rotate.y);
			m_inputVector = VAdd(front, m_inputVector);
			input = true;
		}

		// 後ろに進む
		if (Input::IsPress1P(BUTTON_ID_DOWN))
		{
			rear.x = sinf(m_pTransform->rotate.y) * -1.0f;
			rear.z = cosf(m_pTransform->rotate.y) * -1.0f;
			m_inputVector = VAdd(rear, m_inputVector);
			input = true;
		}

		// 右に進む
		if (Input::IsPress1P(BUTTON_ID_LEFT))
		{
			right.x = sinf(m_pTransform->rotate.y - addRad);
			right.z = cosf(m_pTransform->rotate.y - addRad);
			m_inputVector = VAdd(right, m_inputVector);
			input = true;
		}

		// 左に進む
		if (Input::IsPress1P(BUTTON_ID_RIGHT))
		{
			left.x = sinf(m_pTransform->rotate.y + addRad);
			left.z = cosf(m_pTransform->rotate.y + addRad);
			m_inputVector = VAdd(left, m_inputVector);
			input = true;
		}

		// トマト生成(Playerの回転処理が終わった後生成(上だとプレイヤーの向きにならず少しずれる))
		if (Input::IsDown1P(BUTTON_ID_R) && m_bulletNum > 0 && !m_throwFlag)
		{
			for (auto& tomato : m_pTomato)
			{
				if (tomato->GetActive())
				{
					continue;
				}
				m_throwFlag = true;
				m_animType = Anim::Throw;
				m_moveFlag = false;
				m_bulletNum--;
				VECTOR dir = VGet(0.0f, 0.0f, 0.0f);
				dir.x = m_pTransform->position.x + sinf(m_pTransform->rotate.y) * -30.0f;
				dir.z = m_pTransform->position.z + cosf(m_pTransform->rotate.y) * -30.0f;
				dir = VSub(m_pTransform->position, dir);
				// 方向を正規化
				dir = VNorm(dir);
				// 消えているトマトをアクティブにする
				tomato->ShotTomato(m_pTransform->position, dir, m_pTag);
				break;
			}
		}

		// トマトを限界まで持っていないとき、トマトの壁からトマトを回収
		if (Input::IsDown1P(BUTTON_ID_B) && m_bulletNum < m_bulletCapacity)
		{
			TomatoCollect();
		}

		Score::Set2PBulletNum(m_bulletNum);
	}

	// 入力有（加速）・入力無（減速）
	if (input)
	{
		// 左右・前後同時押しなどで入力ベクトルが0の時は無視
		if (VSquareSize(m_inputVector) < 0.5f)
		{
			return;
		}

		// 方向を正規化
		m_inputVector = VNorm(m_inputVector);

		// 入力方向は現在向いている向きと異なるか
		if (IsNearAngle(m_inputVector, m_dir))
		{
			m_dir = m_inputVector;
		}
		else
		{
			m_rotateNow = true;
			m_aimDir = m_inputVector;
		}

		m_velocity = m_inputVector;
	}
	else
	{
		m_velocity.x = m_velocity.x * 0.9f;
		m_velocity.z = m_velocity.z * 0.9f;
	}
}

void Player1::Rotate()
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

void Player1::Animation()
{
	// アニメーション処理
	if (m_animType == Anim::Throw)
	{
		m_animTime += m_throwSpeed;
	}
	else if (m_animType == Anim::Pick)
	{
		m_animTime += m_pickSpeed;
	}
	else
	{
		m_animTime += m_animSpeed;
	}

	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
		if (m_pickFlag)
		{
			m_pickFlag = false;
			m_animType = Anim::None;
			m_moveFlag = true;
		}
		if (m_throwFlag)
		{
			m_throwFlag = false;
			m_animType = Anim::None;
			m_moveFlag = true;
		}
	}
	ChangeAnimation();

	MV1SetAttachAnimTime(m_var.handle, m_animIndex, m_animTime);
}

void Player1::ChangeAnimation()
{
	// 移動できるアニメーションなら
	// 今動いているのか、止まっているのかを判断
	if (m_moveFlag)
	{
		VECTOR nowPosition = MV1GetPosition(m_var.handle);
		if (m_inputVector.x == 0.0f &&
			m_inputVector.y == 0.0f &&
			m_inputVector.z == 0.0f)
		{
			m_animType = Anim::Idle;
		}
		else
		{
			m_animType = Anim::Run;
		}
	}

	// アニメーション処理
	if (m_animType != m_beforeAnimType)
	{
		MV1DetachAnim(m_var.handle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_var.handle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_var.handle, m_animType);
		m_animTime = 0.0f;
		m_beforeAnimType = m_animType;
	}
}

void Player1::TomatoCollect()
{
	int objectNum = 0;
	float distance = 0;
	int i = 0;
	auto pos = m_pTransform->position;
	for (auto tomatowall : m_pTomatoWall)
	{
		// その壁にトマトはあるのか
		if (tomatowall[i].GetAllTomatoNum() != 0)
		{
			// どのトマトの壁かを調べる
			VECTOR gPos = tomatowall[i].GetPosition();
			distance = GetDistance(gPos, pos);

			// 距離が負の値なら正の値に変える
			if (distance < 0.0f)
			{
				distance = distance * -1.0f;
			}
		}

		// 範囲に入っているトマトの壁からトマトを回収
		if (distance < tomatowall[i].GetWidthDistance() && !m_pickFlag)
		{
			m_pickFlag = true;
			m_moveFlag = false;
			m_animType = Anim::Pick;
			m_bulletNum++;
			tomatowall[i].DecreaseAllTomatoNum();
			break;
		}
	}
}

void Player1::OnCollisionEnter(ColliderComponent* ownColl, ColliderComponent* otherColl)
{
	if (otherColl->GetTag() != nullptr)
	{
		if (otherColl->GetTag()->tag == ObjectTag::Tomato && ownColl->GetCollisionType() == CollisionInfo::CollisionType::Box)
		{
			if (otherColl->GetParentTag()->tag == m_pTag->tag)
			{
				return;
			}
			else
			{

			}
		}
	}

	if (ownColl->GetCollisionType() == CollisionInfo::CollisionType::Box)
	{
		// 座標が足元にあるため、高さをモデルの半分の位置に補正をかけてます
		m_pTransform->position = VAdd(m_pTransform->position, ownColl->GetCollisionInfo().m_fixVec);
	}
}

bool Player1::IsNearAngle(const VECTOR& v1, const VECTOR& v2)
{
	float dot = VDot(v1, v2);
	if (dot < 0.99f)
	{
		return true;
	}
	return false;
}

float Player1::CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec)
{
	VECTOR axis;
	axis = VCross(nowVec, dirVec);
	if (axis.y < 0.0f)
	{
		return -1.0f;
	}
	return 1.0f;
}

VECTOR Player1::RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVelocity)
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
