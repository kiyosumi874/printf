#pragma once
#include <stdexcept>

// �Q�[���I�u�W�F�N�g�E�����蔻��̎�ޕʃ^�O
// �K�v�Ȃ��̂�Begin��End�̊Ԃ�255�܂Œ�`�ł���

enum class Tag : unsigned char
{
	Begin,			// Tag�̊J�n�}�[�J�[�iBegin����O�ɒ�`���Ȃ����Ɓj

	Player = Begin,
	PlayerBullet,
	Enemy,
	EnemyBullet,
	Ground,
	Camera,
	Effect,

	End				// Tag�̏I���}�[�J�[�iEnd����ɒ�`���Ȃ����Ɓj
};

// �O�u�C���N�������g
Tag& operator ++(Tag& rhs);