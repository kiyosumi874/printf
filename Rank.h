#pragma once
#include "Component.h"

class Rank : public Component
{
public:
	Rank();
	~Rank();

	void Init(int index);
	void Start();
	void Update();
	void Draw();

private:
	class Image* m_pImage;

	VECTOR m_position;
	VECTOR m_scale;

	int m_index;

	bool m_flag;
};