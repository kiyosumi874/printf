#include "pch.h"
#include "TomatoWall.h"

// @detail �R���X�g���N�^
TomatoWall::TomatoWall(ObjectTag tag, VECTOR position)
	: m_allTomatoNum(100)
	, m_revivalTime(2000)
	, m_time(0)
	, m_modelPatternIndex(0)
	, m_modelChangeNum{99, 50, 30, 10}
{
	// AssetManager���烂�f���f�[�^��������Ă���
	m_modelPatternHandle[0] = MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::TomatoWallFull));
	m_modelPatternHandle[1] = MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::TomatoWallOne));
	m_modelPatternHandle[2] = MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::TomatoWallTwo));
	m_modelPatternHandle[3] = MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::TomatoWallThree));
	m_modelPatternHandle[4] = MV1DuplicateModel(AssetManager::UseModel(AssetManager::ModelName::TomatoWallFour));

	m_tag = tag;
	m_position = position;
	m_size = VGet(0.035f, 0.035f, 0.035f);

	m_modelHandle = m_modelPatternHandle[0];
	MV1SetPosition(m_modelHandle, m_position);
	MV1SetScale(m_modelHandle, m_size);
}

// @detail �f�X�g���N�^
TomatoWall::~TomatoWall()
{
	MV1DeleteModel(m_modelHandle);
	for (int i = 0; i < m_modelPattern; i++)
	{
		MV1DeleteModel(m_modelPatternHandle[i]);
	}
}

// @detail �X�V����
void TomatoWall::Update()
{
	// ����MAX��0�ł͂Ȃ��A���f�����ŏI�i�K����Ȃ�������
	// �w��̌��ɗ��������f����ς���
	if (m_allTomatoNum != 100 && m_allTomatoNum != 0 && m_modelPatternIndex < 4 &&
		m_allTomatoNum <= m_modelChangeNum[m_modelPatternIndex])
	{
		m_modelPatternIndex++;
		MV1DeleteModel(m_modelHandle);
		m_modelHandle = m_modelPatternHandle[m_modelPatternIndex];
		MV1SetPosition(m_modelHandle, m_position);
		MV1SetScale(m_modelHandle, m_size);
	}

	// ���ׂẴg�}�g���Ȃ��Ȃ�����A���Ԃ������畜��
	if (m_allTomatoNum == 0)
	{
		m_time++;
		if (m_time > m_revivalTime)
		{
			m_allTomatoNum = 100;
			m_modelPatternIndex = 0;
			m_modelHandle = m_modelPatternHandle[m_modelPatternIndex];
			MV1SetPosition(m_modelHandle, m_position);
			MV1SetScale(m_modelHandle, m_size);
			m_time = 0;
		}
	}
}

// @detail �`�揈��
void TomatoWall::Draw()
{
	// �S���Ȃ��Ȃ�����`�悵�Ȃ�
	if (m_allTomatoNum != 0)
	{
		MV1DrawModel(m_modelHandle);
	}
	//DrawFormatString(800, 0, GetColor(255, 255, 255), "TomatoWallNum:%d", m_allTomatoNum);
}
