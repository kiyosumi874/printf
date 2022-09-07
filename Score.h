#pragma once

class Score
{
private:
	static Score* m_score;
	int m_team1;	// チーム1のスコア
	int m_team2;	// チーム2のスコア
	int m_team3;	// チーム3のスコア

	Score();
	~Score();

public:
	Score(const Score&) = delete;				// コピーコンストラクタをdelete指定
	Score& operator=(const Score&) = delete;	// コピー代入演算子も　delete指定
	Score(Score&&) = delete;					// ムーブコンストラクタを delete指定
	Score& operator=(Score&&) = delete;			// ムーブ代入演算子も delete指定

	static void GetInstance()
	{
		if (!m_score)
		{
			m_score = new Score;
		}
	}

	static void Terminate()
	{
		if (m_score)
		{
			delete m_score;
			m_score = nullptr;
		}
	}

	static void AddTeam1Score()
	{
		m_score->m_team1 += 10;
	}

	static void AddTeam2Score()
	{
		m_score->m_team2 += 10;
	}

	static void AddTeam3Score()
	{
		m_score->m_team3 += 10;
	}

	static const int GetTeam1Score()
	{
		return m_score->m_team1;
	}

	static const int GetTeam2Score()
	{
		return m_score->m_team2;
	}

	static const int GetTeam3Score()
	{
		return m_score->m_team3;
	}
	
};