#pragma once
#include <vector>

// �Q�[���I�u�W�F�N�g�E�����蔻��̎�ޕʃ^�O
// �K�v�Ȃ��̂�Begin��End�̊Ԃ�255�܂Œ�`�ł���
enum class ObjectTag : unsigned char
{
	Begin,			// Tag�̊J�n�}�[�J�[�iBegin����O�ɒ�`���Ȃ����Ɓj

	Player1 = Begin,
	Player1Bullet,
	Player2,
	Player2Bullet,
	Enemy,
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
	ObjectTag::Player1,
	ObjectTag::Player1Bullet,
	ObjectTag::Player2,
	ObjectTag::Player2Bullet,
	ObjectTag::Enemy,
	ObjectTag::EnemyBullet,
	ObjectTag::TomatoWall,
	ObjectTag::Ground,
	ObjectTag::Camera1,
	ObjectTag::Camera2,
	ObjectTag::Effect
};