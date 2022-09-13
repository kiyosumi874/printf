#pragma once

class Score
{
private:
	static Score* m_score;
	int m_team1;		// �`�[��1�̃X�R�A
	int m_team2;		// �`�[��2�̃X�R�A
	int m_team3;		// �`�[��3�̃X�R�A
	int m_1PBulletNum;	// 1P�̒e��
	int m_2PBulletNum;	// 2P�̒e��

	Score();
	~Score();

public:
	Score(const Score&) = delete;				// �R�s�[�R���X�g���N�^��delete�w��
	Score& operator=(const Score&) = delete;	// �R�s�[������Z�q���@delete�w��
	Score(Score&&) = delete;					// ���[�u�R���X�g���N�^�� delete�w��
	Score& operator=(Score&&) = delete;			// ���[�u������Z�q�� delete�w��

	static void GetInstance()	// ����
	{
		if (!m_score)
		{
			m_score = new Score;
		}
	}

	static void Terminate()		// ���
	{
		if (m_score)
		{
			delete m_score;
			m_score = nullptr;
		}
	}

	static void AddTeam1Score()	// �`�[��1�̃X�R�A���Z
	{
		m_score->m_team1 += 5;
	}

	static void AddTeam2Score()	// �`�[��2�̃X�R�A���Z
	{
		m_score->m_team2 += 5;
	}

	static void AddTeam3Score()	// �`�[��3�̃X�R�A���Z
	{
		m_score->m_team3 += 5;
	}

	static const int GetTeam1Score()	// �`�[��1�̃X�R�A
	{
		return m_score->m_team1;
	}

	static const int GetTeam2Score()	// �`�[��2�̃X�R�A���Z
	{
		return m_score->m_team2;
	}

	static const int GetTeam3Score()	// �`�[��3�̃X�R�A���Z
	{
		return m_score->m_team3;
	}

	static const int Get1PBulletNum()	// 1P�̒e�����擾
	{
		return m_score->m_1PBulletNum;
	}

	static const int Get2pBulletNum()	// 2P�̒e�����擾
	{
		return m_score->m_2PBulletNum;
	}
	
	static void Set1PBulletNum(const int bulletNum)	// 1P�̒e�����Z�b�g
	{
		m_score->m_1PBulletNum = bulletNum;
	}

	static void Set2PBulletNum(const int bulletNum)	// 2P�̒e�����Z�b�g
	{
		m_score->m_2PBulletNum = bulletNum;
	}
};