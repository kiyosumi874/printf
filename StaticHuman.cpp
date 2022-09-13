#include "pch.h"
#include "StaticHuman.h"
#include "Object.h"
#include "Transform.h"
#include "Tag.h"

StaticHuman::StaticHuman()
{
	m_velocity = VGet(0.0f, 0.0f, 0.0f);

	m_dir = VGet(0.0f, 0.0f, 1.0f);
	m_aimDir = m_dir;

	// �A�j���[�V��������
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
	// 3D���f���̓ǂݍ���
	auto tag = m_pParent->GetComponent<Tag>();
	if (tag->tag == ObjectTag::Team1) { m_modelHandle = MV1LoadModel("data/character/man1.mv1"); }
	if (tag->tag == ObjectTag::Team2) { m_modelHandle = MV1LoadModel("data/character/man3.mv1"); }
	if (tag->tag == ObjectTag::Team3) { m_modelHandle = MV1LoadModel("data/character/woman2.mv1"); }
	MV1SetScale(m_modelHandle, VGet(0.1f, 0.1f, 0.1f));
	// 3D���f���̃|�W�V�����ݒ�
	auto pos = m_pParent->GetComponent<Transform>();
	MV1SetPosition(m_modelHandle, pos->position);
}

void StaticHuman::Update()
{
	// 3D���f���̃|�W�V�����ݒ�
	auto pos = m_pParent->GetComponent<Transform>();
	MV1SetPosition(m_modelHandle, pos->position);

	// �A�j���[�V��������
	m_animTime += 0.3f;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}
	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);
}

void StaticHuman::Draw()
{
	// 3D���f���̕`��
	SetUseLighting(false);
	MV1DrawModel(m_modelHandle);
	SetUseLighting(true);
}
