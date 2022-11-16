#include "pch.h"
#include "PlayerCPU.h"
#include "Tomato.h"
#include "TomatoWallManager.h"
#include "Object.h"
#include "Tag.h"
#include "Transform.h"
#include "Icon.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PickEffect.h"

PlayerCPU::PlayerCPU()
	: Human()
	, m_movePhaseTime(50)
	, m_shotPhaseTime(200.0f)
{
	m_speed = VGet(1.0f, 1.0f, 1.0f);
	m_velocity = VGet(0.0f, 0.0f, 0.0f);
	m_dir = VGet(0.0f, 0.0f, 0.0f);
	m_avoidDir = VGet(1.0f, 1.0f, 1.0f);
	m_tomatoDir = VGet(0.0f, 0.0f, 0.0f);
	m_moveValue = VGet(0.0f, 0.0f, 0.0f);
	m_avoidVelocity = VGet(0.0f, 0.0f, 0.0f);

	m_moveType = Type::RandomMove;
	m_aimTargetFlag = false;
	m_moveTime = 0;

	// アニメーション準備
	m_animType = Anim::Idle;
	m_beforeAnimType = m_animType;
	m_animTime = 0.0f;
	m_animSpeed = 0.3f;
	m_throwSpeed = 1.2f;
	m_pickSpeed = 1.2f;
	m_moveFlag = true;
	m_pickFlag = false;
	m_throwFlag = false;
}

PlayerCPU::~PlayerCPU()
{
}

void PlayerCPU::Start()
{
	if (m_pTransform == nullptr)
	{
		m_pTransform = m_pParent->GetComponent<Transform>();
	}
	if (m_pTag == nullptr)
	{
		m_pTag = m_pParent->GetComponent<Tag>();
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

	if (m_pTag->tag == ObjectTag::Team1)
	{
		m_modelName = AssetManager::ModelName::Team1;
	}
	if (m_pTag->tag == ObjectTag::Team2)
	{
		m_modelName = AssetManager::ModelName::Team2;
	}
}

void PlayerCPU::Update()
{
	// エネミーの行動パターンを調べる
	CheckMovePattern();

	// アニメーションの処理
	Animation();

	// トマトの処理
	ProcessTomato();

	if (m_moveFlag)
	{
		m_var.rotate = m_dir;
		// 3Dモデルの回転設定
		MV1SetRotationXYZ(m_var.handle, m_var.rotate);

		// 3Dモデルのポジション設定
		m_pTransform->position = VAdd(m_pTransform->position, m_velocity);
	}

	m_var.pos = m_pTransform->position;
	MV1SetPosition(m_var.handle, m_var.pos);

	m_pIcon->SetOwnerPosition(m_var.pos);
	// 座標が足元にあるため、高さをモデルの半分の位置に補正をかけてます
	m_pBox->UpdatePosition(VGet(m_var.pos.x, m_var.pos.y + m_pBox->GetWorldBox()->m_scale.y / 2.0f, m_var.pos.z));
	m_pSphere->UpdatePosition(m_var.pos);

	m_pBox->CleanCollisionTag();
	m_pSphere->CleanCollisionTag();
}

void PlayerCPU::Draw()
{
	SetUseLighting(false);
	// 3Dモデルの描画
	MV1DrawModel(m_var.handle);
	m_pIcon->Draw();
	SetUseLighting(true);
}

void PlayerCPU::SetAimTargetPtr(class Object* target)
{
	m_pTarget.push_back(target);
	// 処理が重いので最初からTransform変数をゲットしておく
	m_pTargetTf.push_back(target->GetComponent<Transform>());
}

// @detail トマトの処理関連をまとめたもの
void PlayerCPU::ProcessTomato()
{
	// トマトを投げる
	if (m_animType != Anim::Throw)
	{
		m_shotTime++;
	}
	// 敵が近づいていたり、離れていたら投げるのをキャンセルする
	if (m_shotTime > m_shotPhaseTime && m_moveType == Type::AimTarget && m_bulletNum > 0)
	{
		m_shotFlag = true;
		m_moveFlag = false;
		if (m_animTime == 0.0f && m_animType == Anim::Throw)
		{
			for (auto tomato : m_pTomato)
			{
				if (tomato->GetActive())
				{
					continue;
				}
				if (m_animTime == 0.0f)
				{
					m_bulletNum--;
					m_shotTime = 0.0f;
				}
				// 消えているトマトをアクティブにする
				tomato->ShotTomato(m_pTransform->position, m_tomatoDir, m_pTag);
				break;
			}
		}
	}
}

// @detail 標的がいる方向に正面を向ける
// @param aimTargetPos
void PlayerCPU::RotateTowardTarget(VECTOR& aimTargetPos)
{
	VECTOR subVector = VSub(aimTargetPos, m_pTransform->position);
	double angle = atan2(subVector.x, subVector.z);
	m_dir = VGet(0.0f, angle + DX_PI_F, 0.0f);
	// トマトを自分の向きに合わせて発射
	m_tomatoDir = VAdd(VGet(0.0f, 0.0f, 0.0f), VGet(sin(angle), 0, cos(angle)));
}

void PlayerCPU::Animation()
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
		m_beforeAnimType = m_animType;
		m_animTime = 0.0f;
		if (!m_moveFlag)
		{
			m_moveFlag = true;
			m_shotFlag = false;
			m_pickFlag = false;
		}
	}
	ChangeAnimation();
	// アニメーション処理
	if (m_animType != m_beforeAnimType)
	{
		MV1DetachAnim(m_var.handle, m_animIndex);
		m_animIndex = MV1AttachAnim(m_var.handle, m_animType);
		m_animTotalTime = MV1GetAnimTotalTime(m_var.handle, m_animType);
		m_animTime = 0.0f;
		m_beforeAnimType = m_animType;
	}

	MV1SetAttachAnimTime(m_var.handle, m_animIndex, m_animTime);
}

// @detail アニメーションを変更する関数
void PlayerCPU::ChangeAnimation()
{
	// 移動できるなら
	// 今動いているのか、止まっているのかを判断
	if (m_shotFlag)
	{
		m_animType = Anim::Throw;
		return;
	}
	if (m_pickFlag)
	{
		m_animType = Anim::Pick;
		return;
	}

	bool result = true;
	if (m_velocity.x != 0.0f)
	{
		result = false;
	}
	if (m_velocity.z != 0.0f)
	{
		result = false;
	}
	switch (result)
	{
	case true:
		m_animType = Anim::Idle;
		return;
	case false:
		m_animType = Anim::Run;
		return;
	}
}

// @detail 行動パターンをチェックして実行する
void PlayerCPU::CheckMovePattern()
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);
	// 球がなかったら、集めに行く
	if (m_bulletNum <= 0)
	{
		m_moveType = Type::CollectTomato;
	}

	switch (m_moveType)
	{
	case Type::CollectTomato:   // トマトを集める行動パターン
		CheckTomatoWallMovePattern();
		break;
	case Type::AimTarget:      // ターゲットに対する行動パターン(ターゲット発見状態)
		CheckTargetMovePattern();
		break;
	default:                    // ランダムな行動パターン(ターゲット未発見状態)
		CheckRandomMovePattern();
		break;
	}
}

// @detail ターゲットに対する行動パターンの処理
void PlayerCPU::CheckTargetMovePattern()
{
	int objNum = FindTargetNearby();
	VECTOR tPos = m_pTargetTf[objNum]->position;

	if (m_moveType != Type::EscapeTarget)
	{
		double dis = GetDistance(tPos, m_pTransform->position);

		if (dis < m_targetRangeMax)
		{
			// ターゲットを追いかける
			MoveFoundTarget(tPos);
		}
		else
		{
			m_moveType = Type::RandomMove;
		}
	}
	else  // ターゲットから逃げる処理
	{
		MoveEscapeTarget(tPos);
	}
}

int PlayerCPU::FindTargetNearby()
{
	int objectNum = -1;
	float distance = 0;
	float tmp = 0;
	int i = 0;
	for (auto target : m_pTarget)
	{
		// どのキャラクターが一番近いかを調べる
		VECTOR gPos = m_pTargetTf[i]->position;
		tmp = GetDistance(gPos, m_pTransform->position);

		// tmpが負の値なら正の値に変える
		if (tmp < 0.0f)
		{
			tmp = tmp * -1.0f;
		}

		// 距離が一番近いオブジェクト番号を保存する
		if (distance > tmp || distance == 0.0f)
		{
			distance = tmp;
			objectNum = i;

			if (distance < m_targetRangeMax && m_moveType != Type::EscapeTarget)
			{
				m_moveType = Type::AimTarget;
			}

			// tmpが0だったら一番近いのでfor文を抜ける
			if (tmp == 0.0f)
			{
				break;
			}
		}
		i++;
	}

	return objectNum;
}

// @detail ターゲットに合わせて動く処理
// @param object ターゲットのゲームオブジェクト
void PlayerCPU::MoveFoundTarget(const VECTOR& targetPos)
{
	VECTOR& tPos = const_cast<VECTOR&>(targetPos);
	double distance = GetDistance(tPos, m_pTransform->position);
	if (distance > m_targetMoveRangeMax)  // 標的が離れていたら近づく
	{
		if (targetPos.x - m_pTransform->position.x >= 0.0f)
		{
			m_velocity = VAdd(m_velocity, VGet(m_speed.x / 2.0f, 0.0f, 0.0f));
		}
		else
		{
			m_velocity = VAdd(m_velocity, VGet(-m_speed.x / 2.0f, 0.0f, 0.0f));
		}

		if (targetPos.z - m_pTransform->position.z >= 0.0f)
		{
			m_velocity = VAdd(m_velocity, VGet(0.0f, 0.0f, m_speed.z / 2.0f));
		}
		else
		{
			m_velocity = VAdd(m_velocity, VGet(0.0f, 0.0f, -m_speed.z / 2.0f));
		}
	}
	else if (distance < m_targetMoveRangeMin)  // 標的が近づいてきたら離れる
	{
		if (targetPos.x - m_pTransform->position.x >= 0.0f)
		{
			m_velocity = VAdd(m_velocity, VGet(-m_speed.x / 2.0f, 0.0f, 0.0f));
		}
		else
		{
			m_velocity = VAdd(m_velocity, VGet(m_speed.x, 0.0f, 0.0f));
		}

		if (targetPos.z - m_pTransform->position.z >= 0.0f)
		{
			m_velocity = VAdd(m_velocity, VGet(0.0f, 0.0f, -m_speed.z / 2.0f));
		}
		else
		{
			m_velocity = VAdd(m_velocity, VGet(0.0f, 0.0f, m_speed.z / 2.0f));
		}
	}

	// 標的の方向に回転
	RotateTowardTarget(tPos);
}

// @detail ターゲットから逃げる処理
void PlayerCPU::MoveEscapeTarget(const VECTOR& targetPos)
{
	VECTOR& tPos = const_cast<VECTOR&>(targetPos);

	// トマトの壁がないのか探す
	int objectNum = FindTomatoWallNearby();
	float distance = 0;

	switch (objectNum)
	{
	default:    // トマトを回収しに行く
		MoveCollectTomato(m_pTomatoWall[objectNum]);
		break;
	case -1:
		// トマトの壁がない間は逃げる
		double distance = GetDistance(tPos, m_pTransform->position);

		// 指定の範囲まで逃げ切る
		if (distance < m_targetEscapeRange)
		{
			if (tPos.x - m_pTransform->position.x >= 0.0f)
			{
				m_velocity.x -= m_speed.x;
			}
			else
			{
				m_velocity.x += m_speed.x;
			}

			if (tPos.z - m_pTransform->position.z >= 0.0f)
			{
				m_velocity.z -= m_speed.z;
			}
			else
			{
				m_velocity.z += m_speed.z;
			}

			m_velocity = VGet(m_velocity.x * m_avoidDir.x, m_velocity.y * m_avoidDir.y, m_velocity.z * m_avoidDir.z);

			// 進んでいる方向を向く
			VECTOR aimVec = VAdd(m_pTransform->position, m_velocity);
			RotateTowardTarget(aimVec);
		}
		else  // ターゲットから逃げる範囲を出たらターゲットのほうを向く
		{
			RotateTowardTarget(tPos);
		}
		break;
	}
}

// @detail トマトを回収する行動パターンを実行する
void PlayerCPU::CheckTomatoWallMovePattern()
{
	int tmp = FindTomatoWallNearby();
	switch (tmp)
	{
	case -1:  // トマトの壁がなかった
		// 弾を持っているなら逃げず行動パターンを再抽選
		if (m_bulletNum == 0)
		{
			m_moveType = Type::EscapeTarget;
		}
		else
		{
			m_moveType = Type::RandomMove;
		}
		break;
	default:  // トマトの壁があった(-1以外)
		if (m_bulletNum > 5)
		{
			int objNum = FindTargetNearby();
			VECTOR tPos = m_pTarget[objNum]->GetComponent<Transform>()->position;
			double tmp = GetDistance(tPos, m_pTransform->position);

			// 敵が近くにいたらランダム行動を終了
			if (tmp < m_targetRangeMax)
			{
				m_moveType = Type::AimTarget;
				return;  // その後の処理は行わない
			}
		}
		MoveCollectTomato(m_pTomatoWall[tmp]);
		break;
	}

	/*AvoidTomatoWall(m_pTomatoWall[objectNum]);*/
}

int PlayerCPU::FindTomatoWallNearby()
{
	int objectNum = -1;
	float distance = 0;
	float tmp = 0;
	for (int i = 0; i < m_pTomatoWall.size(); i++)
	{
		// そのトマトの壁にトマトはあるのか
		if (m_pTomatoWall[i]->GetAllTomatoNum() != 0)
		{
			// どのトマトの壁が一番近いかを調べる
			VECTOR gPos = m_pTomatoWall[i]->GetPosition();
			tmp = GetDistance(gPos, m_pTransform->position);

			// tmpが負の値なら正の値に変える
			if (tmp < 0.0f)
			{
				tmp = tmp * -1.0f;
			}

			// 距離が一番近いオブジェクト番号を保存する
			if (distance > tmp || distance == 0.0f)
			{
				distance = tmp;
				objectNum = i;

				// tmpが0だったら一番近いのでfor文を抜ける
				if (tmp == 0.0f)
				{
					break;
				}
			}
		}
	}

	return objectNum;
}

// @detail トマトを回収しに行く処理
// @param object 一番近いトマトの壁オブジェクト
void PlayerCPU::MoveCollectTomato(TomatoWallManager* object)
{
	// どのトマトの壁が一番近いかを調べる
	VECTOR gPos = object->GetPosition();
	float distance = GetDistance(gPos, m_pTransform->position);

	if (distance > object->GetWidthDistance() + 1)  // トマトの壁に当たっていなかったら
	{
		if (gPos.x - m_pTransform->position.x >= 0.0f)
		{
			m_velocity = VAdd(m_velocity, VGet(m_speed.x / 2.0f, 0.0f, 0.0f));
		}
		else
		{
			m_velocity = VAdd(m_velocity, VGet(-m_speed.x / 2.0f, 0.0f, 0.0f));
		}

		if (gPos.z - m_pTransform->position.z >= 0.0f)
		{
			m_velocity = VAdd(m_velocity, VGet(0.0f, 0.0f, m_speed.z / 2.0f));
		}
		else
		{
			m_velocity = VAdd(m_velocity, VGet(0.0f, 0.0f, -m_speed.z / 2.0f));
		}

		// 標的の方向に回転
		VECTOR aimVec = VAdd(m_pTransform->position, m_velocity);
		RotateTowardTarget(aimVec);
	}
	else
	{
		if (m_bulletNum == m_bulletCapacity)
		{
			m_hitTomatoWallFlag = false;
			m_moveType = Type::RandomMove;
		}
		else if (m_bulletNum < m_bulletCapacity)
		{
			m_pickFlag = true;
			m_moveFlag = false;
			if (m_animTime == 0.0f && m_animType == Anim::Pick)
			{
				m_pPickEffect->PlayEffect();
				m_pPickEffect->UpdatePosition(VAdd(m_pTransform->position, VGet(0.0f, 20.0f, 0.0f)));
				m_bulletNum++;
				object->DecreaseAllTomatoNum();
			}
		}
	}
}

void PlayerCPU::CheckRandomMovePattern()
{
	int objNum = FindTargetNearby();
	VECTOR tPos = m_pTarget[objNum]->GetComponent<Transform>()->position;
	double tmp = GetDistance(tPos, m_pTransform->position);

	// 敵が近くにいたらランダム行動を終了
	if (tmp < m_targetRangeMax)
	{
		m_moveType = Type::AimTarget;
		return;  // その後の処理は行わない
	}

	// 標的の方向に移動するか乱数決定
	if (m_moveType == Type::RandomMove)
	{
		m_moveTime = 0;
		m_towardDir = VGet(0.0f, 0.0f, 0.0f);
		srand(rand() % 100);
		m_randomNum = rand() % 4;
		m_moveValue.x = rand() % 3 - 1;
		m_moveValue.z = rand() % 3 - 1;
	}

	// 徘徊行動パターンを多めにする
	if (m_randomNum % 2 == 0)
	{
		m_moveType = Type::Wandering;
		MoveWandering();
	}
	else
	{
		switch (m_randomNum)
		{
		case 1:
			m_moveType = Type::TrackingTarget;
			MoveTrackingTarget(tPos);  // ターゲットを追跡
			break;
		case 3:
			MoveTomato();  // トマトを集めに行く
			break;
		}
	}

	m_moveTime++;
	// 行動時間が終わったら次の行動パターンを抽選
	if (m_moveTime > m_movePhaseTime)
	{
		m_moveType = Type::RandomMove;
	}
}

void PlayerCPU::MoveTrackingTarget(const VECTOR& targetPos)
{
	if (targetPos.x > m_pTransform->position.x)
	{
		m_velocity.x += m_speed.x;
	}
	else if (targetPos.x < m_pTransform->position.x)
	{
		m_velocity.x -= m_speed.x;
	}

	if (targetPos.z > m_pTransform->position.z)
	{
		m_velocity.z += m_speed.z;
	}
	else if (targetPos.z < m_pTransform->position.z)
	{
		m_velocity.z -= m_speed.z;
	}

	// 進んでいる方向を向く
	VECTOR aimVec = VAdd(m_pTransform->position, m_velocity);
	RotateTowardTarget(aimVec);
}

void PlayerCPU::MoveWandering()
{
	m_velocity = m_moveValue;
	// 進んでいる方向を向く
	if (m_velocity.x != 0.0f || m_velocity.z != 0.0f)
	{
		// 進んでいる方向を向く
		VECTOR aimVec = VAdd(m_pTransform->position, m_velocity);
		RotateTowardTarget(aimVec);
	}
}

void PlayerCPU::MoveTomato()
{
	// 弾の数が限界まで持っていたら行動パターンを再抽選
	if (m_bulletNum == m_bulletCapacity)
	{
		m_moveTime = m_movePhaseTime + 1;
	}
	else
	{
		m_moveType = Type::CollectTomato;
	}
}

void PlayerCPU::OnCollisionEnter(ColliderComponent* ownColl, ColliderComponent* otherColl)
{
	if (otherColl->GetTag() != nullptr)
	{
		if (otherColl->GetTag()->tag == ObjectTag::World && ownColl->GetCollisionType() == CollisionInfo::CollisionType::Box ||
			otherColl->GetTag()->tag == ObjectTag::TomatoWall && ownColl->GetCollisionType() == CollisionInfo::CollisionType::Box)
		{
			VECTOR vecDir = CheckVectorDirection(ownColl->GetCollisionInfo().m_fixVec);
			if (vecDir.x != 0.0f)
			{
				switch (m_moveType)
				{
				case Type::Wandering:
					m_moveValue.x = m_moveValue.x * vecDir.x;
					break;
				default:
					m_avoidDir.x = m_moveValue.x * vecDir.x;
					break;
				}
			}
			if (vecDir.y != 0.0f)
			{
				switch (m_moveType)
				{
				case Type::Wandering:
					m_moveValue.y = m_moveValue.y * vecDir.y;
				default:
					m_avoidDir.y = m_moveValue.y * vecDir.y;
				}
			}
			if (vecDir.z != 0.0f)
			{
				switch (m_moveType)
				{
				case Type::Wandering:
					m_moveValue.z = m_moveValue.z * vecDir.z;
				default:
					m_avoidDir.z = m_moveValue.z * vecDir.z;
				}
			}

			if (otherColl->GetTag()->tag == ObjectTag::TomatoWall)
			{
				m_hitTomatoWallFlag = true;
			}
			m_pBox->SetOnCollisionTag(otherColl->GetTag());
		}
		if (otherColl->GetTag()->tag == ObjectTag::Tomato && ownColl->GetCollisionType() == CollisionInfo::CollisionType::Box)
		{
			if (otherColl->GetParentTag()->tag == m_pTag->tag)
			{
				return;
			}
			else
			{
				m_pBox->SetOnCollisionTag(otherColl->GetTag());
				return;
			}
		}
		if (otherColl->GetTag()->tag == ObjectTag::Team1 && ownColl->GetCollisionType() == CollisionInfo::CollisionType::Sphere)
		{
			m_pSphere->SetOnCollisionTag(otherColl->GetTag());
			Transform* tf = otherColl->GetOwner()->m_pParent->GetComponent<Transform>();
			m_targetPos = tf->position;
		}
	}
	if (ownColl->GetCollisionType() == CollisionInfo::CollisionType::Box)
	{
		// 座標が足元にあるため、高さをモデルの半分の位置に補正をかけてます
		m_pTransform->position = VAdd(m_pTransform->position, ownColl->GetCollisionInfo().m_fixVec);
	}
}

// @detail 自身と他のオブジェクトの距離を出す
double PlayerCPU::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}

float PlayerCPU::GetSize(float v1, float v2)
{
	float value = v1 - v2;
	if (value < 0)
	{
		value = value * -1.0f;
	}
	return value;
}
