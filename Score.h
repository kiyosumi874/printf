#pragma once

class Score
{
private:
	static Score* m_score;
	int m_team1;		// チーム1のスコア
	int m_team2;		// チーム2のスコア
	int m_team3;		// チーム3のスコア
	int m_1PBulletNum;	// 1Pの弾数
	int m_2PBulletNum;	// 2Pの弾数

	Score();
	~Score();

public:
	Score(const Score&) = delete;				// コピーコンストラクタをdelete指定
	Score& operator=(const Score&) = delete;	// コピー代入演算子も　delete指定
	Score(Score&&) = delete;					// ムーブコンストラクタを delete指定
	Score& operator=(Score&&) = delete;			// ムーブ代入演算子も delete指定

	static void GetInstance()	// 生成
	{
		if (!m_score)
		{
			m_score = new Score;
		}
	}

	static void Terminate()		// 解放
	{
		if (m_score)
		{
			delete m_score;
			m_score = nullptr;
		}
	}

	static void ScoreInit()		// スコアの初期化
	{
		m_score->m_team1 = 0;
		m_score->m_team2 = 0;
		m_score->m_team3 = 0;
	}

	static void AddTeam1Score()	// チーム1のスコア加算
	{
		m_score->m_team1 += 5;
	}

	static void AddTeam2Score()	// チーム2のスコア加算
	{
		m_score->m_team2 += 5;
	}

	static void AddTeam3Score()	// チーム3のスコア加算
	{
		m_score->m_team3 += 5;
	}

	static const int GetTeam1Score()	// チーム1のスコア
	{
		return m_score->m_team1;
	}

	static const int GetTeam2Score()	// チーム2のスコア加算
	{
		return m_score->m_team2;
	}

	static const int GetTeam3Score()	// チーム3のスコア加算
	{
		return m_score->m_team3;
	}

	static const int Get1PBulletNum()	// 1Pの弾数を取得
	{
		return m_score->m_1PBulletNum;
	}

	static const int Get2pBulletNum()	// 2Pの弾数を取得
	{
		return m_score->m_2PBulletNum;
	}
	
	static void Set1PBulletNum(const int bulletNum)	// 1Pの弾数をセット
	{
		m_score->m_1PBulletNum = bulletNum;
	}

	static void Set2PBulletNum(const int bulletNum)	// 2Pの弾数をセット
	{
		m_score->m_2PBulletNum = bulletNum;
	}
};