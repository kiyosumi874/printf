#include "pch.h"
#include "ModelManager.h"

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
}

void ModelManager::LoadGameModel()
{
	AssetManager::LoadModel(AssetManager::ModelName::Player, "data/character/man1.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::Player2, "data/character/man3.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::Player3, "data/character/woman2.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::Tomato, "data/Tomato/Tomato.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallFull, "data/Tomato/FullTomatoWall.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallOne, "data/Tomato/TomatoWall_one.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallTwo, "data/Tomato/TomatoWall_two.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallThree, "data/Tomato/TomatoWall_three.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::TomatoWallFour, "data/Tomato/TomatoWall_four.mv1");
}

void ModelManager::LoadResultModel()
{
	AssetManager::LoadModel(AssetManager::ModelName::Player, "data/character/man1.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::Player2, "data/character/man3.mv1");
	AssetManager::LoadModel(AssetManager::ModelName::Player3, "data/character/woman2.mv1");
}
