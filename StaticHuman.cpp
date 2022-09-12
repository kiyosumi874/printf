#include "pch.h"
#include "StaticHuman.h"
#include "Object.h"
#include "Transform.h"
#include "ModelManager.h"

StaticHuman::StaticHuman()
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	// 3Dモデルの読み込み
	ModelManager model;
	srand(rand() % 100);
	int modelNum = rand() % MODEL_NUM;
	m_modelHandle = model.GetModelData(modelNum);
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;

	// アニメーション準備
	m_animType = Anim::Idle;
	m_animIndex = MV1AttachAnim(m_modelHandle, m_animType);
	m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animType);
	m_animTime = 0.0f;
}

StaticHuman::~StaticHuman()
{
	MV1DeleteModel(m_modelHandle);
}

void StaticHuman::Start()
{
}

void StaticHuman::Update()
{
	// 3Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_pParent->GetComponent<Transform>()->position);

	// 向きに合わせてモデルを回転
	MATRIX rotYMat = MGetRotY(180.0f * DX_PI_F / 180.0f);
	VECTOR negativeVec = VTransform(m_dir, rotYMat);

	// モデルに回転をセットする
	MV1SetRotationZYAxis(m_modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// アニメーション処理
	m_animTime += 0.3f;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}
	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);
}

void StaticHuman::Draw()
{
	// 3Dモデルの描画
	SetUseLighting(false);
	MV1DrawModel(m_modelHandle);
	SetUseLighting(true);
}
