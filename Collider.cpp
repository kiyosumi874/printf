#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "Transform.h"
#include "Human.h"
#include "Tomato.h"
#include "Score.h"

Collider::Collider()
	: flag(false)
	, tag(ObjectTag::End)
	, width(0.0f)
{
	// GtFNgÌ¶¬
	m_HitEffect = new HitEffect();
}

Collider::~Collider()
{
	// GtFNgÌí
	delete m_HitEffect;
}

void Collider::Update()
{
	CollisionCheck();
}

void Collider::CollisionCheck()
{
	auto self = m_pParent;
	auto selfPosition = self->GetComponent<Transform>()->position;
	auto selfTag = self->GetComponent<Tag>();
	for (auto obj : m_pObjectLists)
	{
		if (self == obj) { continue; }	// èªåä»¥å¤ã®ãªãã¸ã§ã¯ãã¨å¤å®ãããã
		Transform* trans = nullptr;
		trans = obj->GetComponent<Transform>();
		if (trans == nullptr) { continue; }	// Transformãã³ã³ãã¼ãã³ããã¦ããªããã®ã¨å¤å®ã¯ããªã
		auto L_tag = obj->GetComponent<Tag>();
		if (L_tag == nullptr) { continue; } // Tagãã³ã³ãã¼ãã³ããã¦ããªããã®ã¨å¤å®ããªã
		float distance = 0.0f;
		distance = GetDistance(selfPosition, trans->position);

		// è·é¢ãè² ã®å¤ãªãæ­£ã®å¤ã«å¤ãã
		if (distance < 0.0f)
		{
			distance = distance * -1.0f;
		}

		if (distance < width)
		{
			if (L_tag->tag == ObjectTag::tomato)	// å½ãã£ãã®ã¯ãããã ã£ã
			{
				auto tomato = obj->GetComponent<Tomato>();

				tag = tomato->GetTag()->tag;	// ã ããæãããããï¼ï¼å½ãã£ãäººã®ã¿ã°ã¯ãããªãã¨æããå½ã¦ãäººã ãã³ã©ã¤ãã¼ãã³ã³ãã¼ãã³ããããï¼

				if (selfTag->tag == tag)	// èªåãæãããããã ã£ãã®ã§ç¡è¦
				{
					continue;
				}
				// ããã«ã«ãã»ã«åããã¹ã³ã¢ç®¡çã¯ã©ã¹ãå¼ã¹ã°ããã¨æã
				if (tag == ObjectTag::Team1) { Score::AddTeam1Score(); }
				else if (tag == ObjectTag::Team2) { Score::AddTeam2Score(); }
				else if (tag == ObjectTag::Team3) { Score::AddTeam3Score(); }

				// GtFNgð`æ·é
				m_HitEffect->Draw(tomato->GetPosition(), tomato->GetDir());

				/*if (!m_HitEffect->m_DrawFlag)
				{
					m_HitEffect->m_DrawFlag = true;
					m_HitEffect->Update(tomato->GetPosition(),tomato->GetDir());
				}*/
			}
			flag = true;
			break;
		}
		flag = false;
	}
}

void Collider::SetBulletObject(Object* obj)
{
	copyObjectList.push_front(obj);
}

double Collider::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}
