#include "pch.h"
#include "Icon.h"
#include "Tag.h"

Icon::Icon(Tag* tag)
{
	m_noIconFlag = false;
	if (tag->tag == ObjectTag::Team1)
	{
		m_modelHandle = MV1LoadModel("data/Icon/Red.mv1");
	}
	else if (tag->tag == ObjectTag::Team2)
	{
		m_modelHandle = MV1LoadModel("data/Icon/Blue.mv1");
	}
	else if (tag->tag == ObjectTag::Team3)
	{
		m_modelHandle = MV1LoadModel("data/Icon/Green.mv1");
	}
	else  // ‚Ç‚ê‚É‚à“–‚Ä‚Í‚Ü‚ç‚È‚¢‚È‚çA‚±‚êˆÈ~‚Ìˆ—‚ðs‚í‚È‚¢‚æ‚¤‚É‚·‚é
	{
		m_noIconFlag = true;
	}
}

Icon::~Icon()
{
	MV1DeleteModel(m_modelHandle);
}

void Icon::Init(VECTOR& position)
{
	if (!m_noIconFlag)
	{
		m_animIndex = MV1AttachAnim(m_modelHandle, 0);
		m_animTotalTime = MV1GetAnimTotalTime(m_modelHandle, m_animIndex);
		m_animSpeed = 0.5f;
		m_animTime = 0.0f;

		m_correctionVector = VGet(0.0f, 20.0f, 0.0f);
		MV1SetScale(m_modelHandle, VGet(0.7f, 0.7f, 0.7f));

		VECTOR pos = VAdd(position, m_correctionVector);
		MV1SetPosition(m_modelHandle, pos);
	}
}

void Icon::Update(VECTOR& position)
{
	if (!m_noIconFlag)
	{
		VECTOR pos = VAdd(position, m_correctionVector);
		MV1SetPosition(m_modelHandle, pos);

		Animation();
	}
}

void Icon::Draw()
{
	if (!m_noIconFlag)
	{
		MV1DrawModel(m_modelHandle);
	}
}

void Icon::Animation()
{
	m_animTime += m_animSpeed;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}

	MV1SetAttachAnimTime(m_modelHandle, m_animIndex, m_animTime);
}
