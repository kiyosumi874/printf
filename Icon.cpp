#include "pch.h"
#include "Icon.h"
#include "Tag.h"

Icon::Icon(Tag* tag)
{
	m_noIconFlag = false;
	m_pTag = tag;
}

Icon::~Icon()
{
}

void Icon::Update(VECTOR& position)
{
	if (!m_noIconFlag)
	{
		m_var.pos = VAdd(position, m_correctionVector);
		MV1SetPosition(m_var.handle, m_var.pos);

		Animation();
	}
}

void Icon::Draw()
{
	if (!m_noIconFlag)
	{
		MV1DrawModel(m_var.handle);
	}
}

void Icon::Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale)
{
	if (m_pTag->tag == ObjectTag::Team1)
	{
		m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Icon1)), pos, rotate, scale);
	}
	else if (m_pTag->tag == ObjectTag::Team2)
	{
		m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Icon2)), pos, rotate, scale);
	}
	else if (m_pTag->tag == ObjectTag::Team3)
	{
		m_var.Init(MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::Icon3)), pos, rotate, scale);
	}
	else  // ‚Ç‚ê‚É‚à“–‚Ä‚Í‚Ü‚ç‚È‚¢‚È‚çA‚±‚êˆÈ~‚Ìˆ—‚ðs‚í‚È‚¢‚æ‚¤‚É‚·‚é
	{
		m_noIconFlag = true;
	}

	if (!m_noIconFlag)
	{
		m_animIndex = MV1AttachAnim(m_var.handle, 0);
		m_animTotalTime = MV1GetAnimTotalTime(m_var.handle, m_animIndex);
		m_animSpeed = 0.5f;
		m_animTime = 0.0f;

		m_correctionVector = VGet(0.0f, 20.0f, 0.0f);
		MV1SetScale(m_var.handle, m_var.scale);

		m_var.pos = VAdd(m_var.pos, m_correctionVector);
		MV1SetPosition(m_var.handle, m_var.pos);
	}
}

void Icon::Animation()
{
	m_animTime += m_animSpeed;
	if (m_animTime > m_animTotalTime)
	{
		m_animTime = 0.0f;
	}

	MV1SetAttachAnimTime(m_var.handle, m_animIndex, m_animTime);
}
