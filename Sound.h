#pragma once
#include <unordered_map>
#include <DxLib.h>

class Sound
{
public:
	enum Kind
	{
		Throw,
		CountDown
	};
	static void Load(int kind, const char* str)
	{
		sounds.insert(std::make_pair(kind, LoadSoundMem(str)));
	}

	static void Play(int kind)
	{
		auto itr = sounds.find(kind);
		PlaySoundMem(itr->second, DX_PLAYTYPE_BACK);
	}

	// ‰¹‘S‰ð•ú
	static void InitSound()
	{
		InitSoundMem();
		sounds.clear();
	}

private:
	static std::unordered_multimap<int,int> sounds;
};