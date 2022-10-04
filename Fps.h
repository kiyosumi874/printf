#pragma once

class Fps
{
public:
	
	static void GetInstance()
	{
		if (!m_this)
		{
			m_this = new Fps;
		}
	}

	static void Terminate()
	{
		if (m_this)
		{
			delete m_this;
			m_this = nullptr;
		}
	}

	static bool GetFlag() { return m_this->m_flag; }

	static void Update();
	static void Draw();

private:
	Fps();
	~Fps();
	float m_fps;
	float m_frameTime;
	bool  m_flag;
	LARGE_INTEGER m_timeStart;
	LARGE_INTEGER m_timeEnd;
	LARGE_INTEGER m_timeFreq;

	static Fps* m_this;

};