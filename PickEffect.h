#pragma once
#include "Component.h"

class PickEffect : public Component
{
public:
	PickEffect();
	~PickEffect();

	void Init(const char* filePath, const VECTOR& pos, const VECTOR& scale, const VECTOR& rotate);
	void Start() override;
	void Update() override;
	void Draw() override;
	void PlayEffect();
	void StopEffect();

	void UpdatePosition(const VECTOR& pos);
	void UpdateScale(const VECTOR& scale);
	void UpdateRotate(const VECTOR& rotate);
	void UpdateState(const VECTOR& pos, const VECTOR& scale, const VECTOR& rotate);
	void UpdateDrawFlag(bool flag) { m_drawFlag = flag; }

	int GetPlayFlag();
private:
	int m_effectHandle = -1;
	int m_playingEffect = -1;
	VECTOR m_pos;
	VECTOR m_scale;
	VECTOR m_rotate;

	bool m_drawFlag = false;
	bool m_nowPlayFlag = false;
};

