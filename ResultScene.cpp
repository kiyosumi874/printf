#include "pch.h"
#include "Object.h"
#include "Image.h"
#include "StaticHuman.h"
#include "Transform.h"
#include "Tag.h"
#include "StillProjector.h"
#include "Rank.h"
#include "Score.h"
#include "ResultScoreUI.h"
#include "SkyDome.h"
#include "ResultTomato.h"

VECTOR tier1Pos = VGet(-4.0f, 0.0f, -25.0f);
VECTOR tier2Pos = VGet(-24.0f, 0.0f, -20.0f);
VECTOR tier3Pos = VGet(20.0f, 0.0f, -15.0f);
ResultScene::ResultScene(const MODE& mode)
	: Scene(mode)
	, m_transition(Transition::START)
	, m_tagScene(TAG_SCENE::TAG_NONE)
{
	Object* ob = new Object;
	auto proj = ob->AddComponent<StillProjector>();
	m_pObjectLists.push_back(ob);

	// skyDome
	{
		Object* obj = new Object;
		obj->AddComponent<SkyDome>();
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		obj->AddComponent<ResultGround>();
		m_pColliderLists.push_back(obj);
		m_pObjectLists.push_back(obj);
	}

	auto T1 = Score::GetTeam1Score();
	auto T2 = Score::GetTeam2Score();
	auto T3 = Score::GetTeam3Score();
	// ScoreUI
	{
		Object* object = nullptr;
		for (int i = 0; i < 3; i++)
		{
			object = new Object;
			object->AddComponent<Transform>()->position = VGet(300 * i + 700, 840.0f, 0.0f);
			m_scoreUICon[i] = object->AddComponent<ResultScoreUI>();
			m_pObjectLists.push_back(object);
		}
	}
	// 順位ごとに並べる処理(人とスコア)
	if (T1 > T2)
	{
		m_scoreUICon[1]->CheckIsStart(0);
		if (T1 > T3)
		{
			if (T2 > T3)
			{
				// ①→②→③
				RankOrderInit(RankOrder::one);
				m_scoreUICon[0]->CheckIsStart(1);
				m_scoreUICon[2]->CheckIsStart(2);
			}
			else
			{
				// ①→③→②
				RankOrderInit(RankOrder::two);
				m_scoreUICon[0]->CheckIsStart(2);
				m_scoreUICon[2]->CheckIsStart(1);
			}
		}
		else
		{
			// ③→①→②
			RankOrderInit(RankOrder::five);
			m_scoreUICon[1]->CheckIsStart(2);
			m_scoreUICon[0]->CheckIsStart(0);
			m_scoreUICon[2]->CheckIsStart(1);
		}
	}
	else if (T2 > T3)
	{
		m_scoreUICon[1]->CheckIsStart(1);
		if (T1 > T3)
		{
			// ②→①→③
			RankOrderInit(RankOrder::three);
			m_scoreUICon[0]->CheckIsStart(0);
			m_scoreUICon[2]->CheckIsStart(2);
		}
		else
		{
			// ②→③→①
			RankOrderInit(RankOrder::four);
			m_scoreUICon[0]->CheckIsStart(2);
			m_scoreUICon[2]->CheckIsStart(0);
		}
	}
	else
	{
		// ③→②→①
		RankOrderInit(RankOrder::six);
		m_scoreUICon[1]->CheckIsStart(2);
		m_scoreUICon[0]->CheckIsStart(0);
		m_scoreUICon[2]->CheckIsStart(1);
	}

	{
		Object* obj = new Object;
		auto img = obj->AddComponent<Image>();
		img->Init(VGet(850.0f, 150.0f, 0.0f), VGet(0.7f, 0.7f, 0.7f), 0.0f, "data/rank/hukidasi.png");
		img->SetAlpha(230);
		auto image = obj->AddComponent<Image>();
		image->Init(VGet(880.0f, 180.0f, 0.0f), VGet(0.5f, 0.5f, 0.5f), 0.0f, "data/rank/ranking_1.png");
		obj->AddComponent<Rank>();
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		auto img = obj->AddComponent<Image>();
		img->Init(VGet(380.0f, 160.0f, 0.0f), VGet(0.6f, 0.6f, 0.6f), 0.0f, "data/rank/hukidasi.png");
		img->SetAlpha(230);
		auto image = obj->AddComponent<Image>();
		image->Init(VGet(410.0f, 200.0f, 0.0f), VGet(0.4f, 0.4f, 0.4f), 0.0f, "data/rank/ranking_2.png");
		obj->AddComponent<Rank>();
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		auto img = obj->AddComponent<Image>();
		img->Init(VGet(1360.0f, 140.0f, 0.0f), VGet(0.55f, 0.55f, 0.55f), 0.0f, "data/rank/hukidasi.png");
		img->SetAlpha(230);
		auto image = obj->AddComponent<Image>();
		image->Init(VGet(1400.0f, 190.0f, 0.0f), VGet(0.3f, 0.3f, 0.3f), 0.0f, "data/rank/ranking_3.png");
		obj->AddComponent<Rank>();
		m_pObjectLists.push_back(obj);
	}

	// トマト生成
	for (auto i = 0; i < 6; i++)
	{
		Object* obj = new Object;
		auto tomato = obj->AddComponent<ResultTomato>();
		tomato->Init(VGet(i * -2, 5.0f, -20.0f), VGet(0.0f, 0.0f, 0.0f), VGet(0.02f, 0.02f, 0.02f));
		m_pObjectLists.push_back(obj);
	}

	// トランジションの処理
	{
		Object* obj = new Object;
		m_transitionImage[0] = obj->AddComponent<Image>();
		m_transitionImage[0]->Init(VGet(0.0f, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/black.png");
		m_pObjectLists.push_back(obj);
	}
	{
		Object* obj = new Object;
		m_transitionImage[1] = obj->AddComponent<Image>();
		m_transitionImage[1]->Init(VGet(SCREEN_WIDTH / 2, 0.0f, 0.0f), VGet(1.0f, 1.0f, 1.0f), 0.0f, "data/transition.png");
		m_pObjectLists.push_back(obj);
	}
}

ResultScene::~ResultScene()
{
	for (auto obj : m_pObjectLists)
	{
		delete obj;
	}
	m_pObjectLists.clear();
	m_pColliderLists.clear();
}

TAG_SCENE ResultScene::Update()
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_TITLE;
	}
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}
	switch (m_transition)
	{
	case ResultScene::Transition::START:
		UpdateTransitionStart();
		break;
	case ResultScene::Transition::PLAY:
		UpdateTransitionPlay();
		break;
	case ResultScene::Transition::OVER:
		break;
	case ResultScene::Transition::END:
		UpdateTransitionEnd();
		break;
	default:
		break;
	}
	return TAG_SCENE::TAG_NONE;
}

void ResultScene::Draw()
{
#ifdef _DEBUG
	printfDx("GameOverScene\n");
#endif // _DEBUG
	for (auto obj : m_pObjectLists)
	{
		obj->Draw();
	}
}

void ResultScene::UpdateTransitionStart()
{
	if (m_transitionImage[0] != nullptr)
	{
		m_transitionImage[0]->MovePos(VGet(-10.0f, 0.0f, 0.0f));
		m_transitionImage[1]->MovePos(VGet(-10.0f, 0.0f, 0.0f));
		if (m_transitionImage[1]->GetPos().x < -2540.0f)
		{
			m_transition = Transition::PLAY;
		}
	}
	else
	{
		m_transition = Transition::PLAY;
	}
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
}

void ResultScene::UpdateTransitionPlay()
{
	for (auto obj : m_pObjectLists)
	{
		obj->Update();
	}
}

void ResultScene::UpdateTransitionEnd()
{
}

void ResultScene::RankOrderInit(RankOrder num)
{
	switch (num)
	{
	case ResultScene::one:
	{
		Object* obj = new Object;
		auto pos = obj->AddComponent<Transform>();
		pos->position = tier1Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos2 = obj->AddComponent<Transform>();
		pos2->position = VAdd(tier1Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos3 = obj->AddComponent<Transform>();
		pos3->position = tier2Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos4 = obj->AddComponent<Transform>();
		pos4->position = VAdd(tier2Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos5 = obj->AddComponent<Transform>();
		pos5->position = tier3Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos6 = obj->AddComponent<Transform>();
		pos6->position = VAdd(tier3Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);
	}
	break;
	case ResultScene::two:
	{
		Object* obj = new Object;
		auto pos = obj->AddComponent<Transform>();
		pos->position = tier1Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos2 = obj->AddComponent<Transform>();
		pos2->position = VAdd(tier1Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos3 = obj->AddComponent<Transform>();
		pos3->position = tier2Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos4 = obj->AddComponent<Transform>();
		pos4->position = VAdd(tier2Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos5 = obj->AddComponent<Transform>();
		pos5->position = tier3Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos6 = obj->AddComponent<Transform>();
		pos6->position = VAdd(tier3Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);
	}
	break;
	case ResultScene::three:
	{
		Object* obj = new Object;
		auto pos = obj->AddComponent<Transform>();
		pos->position = tier1Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos2 = obj->AddComponent<Transform>();
		pos2->position = VAdd(tier1Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos3 = obj->AddComponent<Transform>();
		pos3->position = tier2Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos4 = obj->AddComponent<Transform>();
		pos4->position = VAdd(tier2Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos5 = obj->AddComponent<Transform>();
		pos5->position = tier3Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos6 = obj->AddComponent<Transform>();
		pos6->position = VAdd(tier3Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);
	}
	break;
	case ResultScene::four:
	{
		Object* obj = new Object;
		auto pos = obj->AddComponent<Transform>();
		pos->position = tier1Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos2 = obj->AddComponent<Transform>();
		pos2->position = VAdd(tier1Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos3 = obj->AddComponent<Transform>();
		pos3->position = tier2Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos4 = obj->AddComponent<Transform>();
		pos4->position = VAdd(tier2Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos5 = obj->AddComponent<Transform>();
		pos5->position = tier3Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos6 = obj->AddComponent<Transform>();
		pos6->position = VAdd(tier3Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);
	}
	break;
	case ResultScene::five:
	{
		Object* obj = new Object;
		auto pos = obj->AddComponent<Transform>();
		pos->position = tier1Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos2 = obj->AddComponent<Transform>();
		pos2->position = VAdd(tier1Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos3 = obj->AddComponent<Transform>();
		pos3->position = tier2Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos4 = obj->AddComponent<Transform>();
		pos4->position = VAdd(tier2Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos5 = obj->AddComponent<Transform>();
		pos5->position = tier3Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos6 = obj->AddComponent<Transform>();
		pos6->position = VAdd(tier3Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);
	}
	break;
	case ResultScene::six:
	{
		Object* obj = new Object;
		auto pos = obj->AddComponent<Transform>();
		pos->position = tier1Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos2 = obj->AddComponent<Transform>();
		pos2->position = VAdd(tier1Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team3;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos5 = obj->AddComponent<Transform>();
		pos5->position = tier2Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos6 = obj->AddComponent<Transform>();
		pos6->position = VAdd(tier2Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team2;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos3 = obj->AddComponent<Transform>();
		pos3->position = tier3Pos;
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);

		obj = new Object;
		auto pos4 = obj->AddComponent<Transform>();
		pos4->position = VAdd(tier3Pos, VGet(10.0f, 0.0f, 0.0f));
		obj->AddComponent<Tag>()->tag = ObjectTag::Team1;
		obj->AddComponent<StaticHuman>();
		m_pObjectLists.push_back(obj);
	}
	break;
	default:
		break;
	}
}
