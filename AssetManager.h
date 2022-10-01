#pragma once
#include <unordered_map>
#include "DxLib.h"
#undef LoadImage() // windowsÇÃLoadImageÇîjâÛÇ∑ÇÈÇΩÇﬂ
#pragma warning(disable:26812) // enumÇÃåxçêÇè¡Ç∑
using namespace std;

class AssetManager
{
public:
	enum ImageName
	{
		Logo,
		TransitionButton,
		Gradation
	};

	enum ModelName
	{
		Player,
		Player2,
		Player3,
		Tomato,
		TomatoWallFull,
		TomatoWallOne,
		TomatoWallTwo,
		TomatoWallThree,
		TomatoWallFour,
		Ground,
		SkyDome
	};

	static void LoadImage(ImageName name, const char* str)
	{
		m_images.insert(make_pair(name, LoadGraph(str)));
	}

	static void LoadModel(ModelName name, const char* str)
	{
		m_models.insert(make_pair(name, MV1LoadModel(str)));
	}

	static void Terminate()
	{
		for (const auto& it : m_images)
		{
			DeleteGraph(it.second);
		}

		for (const auto& it : m_models)
		{
			MV1DeleteModel(it.second);
		}

		m_images.clear();
		m_models.clear();
	}

	static int UseImage(ImageName name)
	{
		return m_images[name];
	}

	static int UseModel(ModelName name)
	{
		return m_models[name];
	}

private:
	static unordered_map<ImageName, int> m_images;
	static unordered_map<ModelName, int> m_models;
};