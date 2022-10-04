#pragma once
#include "Component.h"

class Human : public ModelBase, public Component
{
public:
	Human();
	virtual ~Human() {};

	virtual void Start() {};
	virtual void Update() {};
	virtual void Draw() {};

	// �K���ĂԂ���
	void Init(const VECTOR& pos, const VECTOR& rotate, const VECTOR& scale);

	void SetTomatoWallPtr(std::vector<class TomatoWallManager*> tomatoWall);

	void GetPosition() { m_var.pos; }
	void GetRotate() { m_var.rotate; }
protected:
	AssetManager::ModelName m_modelName;

	class Transform* m_pTransform = nullptr;
	class Tag* m_pTag = nullptr;
	std::vector<class TomatoWallManager*> m_pTomatoWall;
	class Icon* m_pIcon = nullptr;  // �A�C�R���N���X
	class std::list<Object*> m_pTomato;

	const int m_bulletCapacity = 10; // ���̌��E������
	int m_bulletNum = m_bulletCapacity;        // ���̏�����

	enum Anim
	{
		None = -1,  // �������Ȃ�
		Idle,  // �~�܂�
		Run,   // ����
		Throw,  // ������
		Pick,  // �E��
	};

	int m_animType;  // ���݂̃A�j���[�V����������
	int m_beforeAnimType;  // �O�̃A�j���[�V����
	int m_animIndex;  // ���݂̃A�j���[�V�������L�^
	float m_animTime;  // �A�j���[�V�����̌o�ߎ���
	float m_animTotalTime;  // �A�j���[�V�����̑�����
	float m_animSpeed;  // ��̃A�j���[�V�����X�s�[�h
	float m_throwSpeed;  // ������X�s�[�h(�␳��������)
	float m_pickSpeed;  // �E���X�s�[�h(�␳��������)

	bool m_moveFlag;  // �����Ă��邩
	bool m_throwFlag;  // �g�}�g�𓊂�����
	bool m_pickFlag;  // �g�}�g���E������

	virtual void Animation() {};  // �A�j���[�V��������
	virtual void ChangeAnimation() {};  // �A�j���[�V�����ύX����

	double GetDistance(VECTOR& pos1, VECTOR& pos2);
	float GetSize(float v1, float v2);
};
