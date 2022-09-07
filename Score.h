#pragma once

class Score
{
private:
	static Score* m_score;
	int m_team1;	// �`�[��1�̃X�R�A
	int m_team2;	// �`�[��2�̃X�R�A
	int m_team3;	// �`�[��3�̃X�R�A

	Score();
	~Score();

public:
	Score(const Score&) = delete;				// �R�s�[�R���X�g���N�^��delete�w��
	Score& operator=(const Score&) = delete;	// �R�s�[������Z�q���@delete�w��
	Score(Score&&) = delete;					// ���[�u�R���X�g���N�^�� delete�w��
	Score& operator=(Score&&) = delete;			// ���[�u������Z�q�� delete�w��

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