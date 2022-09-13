#pragma once
#include <vector>

// �Q�[���I�u�W�F�N�g�E�����蔻��̎�ޕʃ^�O
// �K�v�Ȃ��̂�Begin��End�̊Ԃ�255�܂Œ�`�ł���
enum class ObjectTag : unsigned char
{
	Begin,			// Tag�̊J�n�}�[�J�[�iBegin����O�ɒ�`���Ȃ����Ɓj

	Team1 = Begin,
	Player1Bullet,
	Team2,
	Player2Bullet,
	Team3,
	EnemyBullet,
	tomato,
	TomatoWall,
	Ground,
	Camera1,
	Camera2,
	Effect,

	End				// Tag�̏I���}�[�J�[�iEnd����ɒ�`���Ȃ����Ɓj
};

// for( ObjectTag &tag : ObjectTagAll )�őSTag�v�f�̃��[�v�ɂł���
constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Team1,
	ObjectTag::Player1Bullet,
	ObjectTag::Team2,
	ObjectTag::Player2Bullet,
	ObjectTag::Team3,
	ObjectTag::EnemyBullet,
	ObjectTag::TomatoWall,
	ObjectTag::Ground,
	ObjectTag::Camera1,
	ObjectTag::Camera2,
	ObjectTag::Effect
};