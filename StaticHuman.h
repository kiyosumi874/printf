#pragma once
#include "Component.h"

class StaticHuman : public Component
{
public:
	StaticHuman();
	~StaticHuman();

	void Start();
	void Update();
	void Draw();

private:
	class Icon* m_icon;  // �A�C�R���N���X

	VECTOR m_dir;			// ����
	VECTOR m_aimDir;		// �ڕW����
	VECTOR m_velocity;		// ���x

	int m_modelHandle;		// ���f���n���h��

	enum Anim
	{
		Idle,
		Run,
	};

	int m_animType;  // ���݂̃A�j���[�V����������
	int m_animIndex;  // ���݂̃A�j���[�V�������L�^
	float m_animTime;  // �A�j���[�V�����̌o�ߎ���
	float m_animTotalTime;  // �A�j���[�V�����̑�����
};
