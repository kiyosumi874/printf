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
}

Collider::~Collider()
{
}

void Collider::Init(std::list<Object*>* objectLists)
{
	copyObjectList = objectLists;
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
	for (auto obj : *copyObjectList)
	{
		if (self == obj) { continue; }	// �����ȊO�̃I�u�W�F�N�g�Ɣ��肷�邽��
		Transform* trans = nullptr;
		trans = obj->GetComponent<Transform>();
		if (trans == nullptr) { continue; }	// Transform���R���|�[�l���g���Ă��Ȃ����̂Ɣ���͂��Ȃ�
		auto L_tag = obj->GetComponent<Tag>();
		if (L_tag == nullptr) { continue; } // Tag���R���|�[�l���g���Ă��Ȃ����̂Ɣ��肵�Ȃ�
		float distance = 0.0f;
		distance = GetDistance(selfPosition, trans->position);

		// ���������̒l�Ȃ琳�̒l�ɕς���
		if (distance < 0.0f)
		{
			distance = distance * -1.0f;
		}

		if (distance < width)
		{
			if (L_tag->tag == ObjectTag::tomato)	// ���������̂̓g�}�g������
			{
				auto tomato = obj->GetComponent<Tomato>();
				tag = tomato->m_tag->tag;	// ���ꂪ�������g�}�g�H�i���������l�̃^�O�͂���Ȃ��Ǝv���B������l�����R���C�_�[���R���|�[�l���g������j
				if (selfTag->tag == tag)	// �������������g�}�g�������̂Ŗ���
				{
					continue;
				}
				// �����ɃJ�v�Z���������X�R�A�Ǘ��N���X���Ăׂ΂����Ǝv��
				if (tag == ObjectTag::Team1) { Score::AddTeam1Score(); }
				if (tag == ObjectTag::Team2) { Score::AddTeam2Score(); }
				if (tag == ObjectTag::Team3) { Score::AddTeam3Score(); }
			}
			flag = true;
			break;
		}
		flag = false;
	}
}

void Collider::Shot(VECTOR position, VECTOR dir, Tag* tag)
{
	Object* obj = new Object;
	obj->AddComponent<Transform>();
	auto L_tag = obj->AddComponent<Tag>();
	L_tag->tag = ObjectTag::tomato;
	obj->AddComponent<Tomato>()->Init(position, dir, tag);
	copyObjectList->push_front(obj);
}

double Collider::GetDistance(VECTOR& pos1, VECTOR& pos2)
{
	double tmp1 = pos1.x - pos2.x;
	double tmp2 = pos1.z - pos2.z;
	return sqrt(tmp1 * tmp1 + tmp2 * tmp2);
}
