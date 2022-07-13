#include "pch.h"

Map::Map()
	: m_objDistance(VGet(100.0f, 0.0f, 100.0f))
{
	m_mapSize.w, m_mapSize.h = 0;
}

Map::~Map()
{
}

bool Map::OpenFile()
{
	// データの読み込み
	if (!ReadTiledJson(m_groundMapDate, "Map/Map.json", "Ground"))
	{
		return true;
	}

	m_mapSize.w = m_groundMapDate[0].size();
	m_mapSize.h = m_groundMapDate.size();

	return false;
}

void Map::GroundCreate()
{
	// 奥行
	for (float iz = 0; iz < m_mapSize.h; ++iz)
	{
		// 横幅
		for (float ix = 0; ix < m_mapSize.w; ++ix)
		{
			// 割り当てられている数字
			const unsigned int name = m_groundMapDate[(int)iz][(int)ix];

			// ポジション
			const VECTOR objPos = VECTOR(VGet(-m_objDistance.x * ix, 0.0f, m_objDistance.z * iz));

			// 割り当てられている数字が1だったら
			if (name == 1)
			{
				mGround.emplace_back(new Ground(objPos));
				//new Ground(objPos); // 床の生成
			}

			
		}

	}
}

bool Map::ReadTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	// RapidJsonドキュメントとして開けるか？
	rapidjson::Document doc;
	if (!OpenJsonFile(doc, _fileName))
	{
		return false;
	}
	// 開いたdocumentのtypeはmapか？
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}
	// 開いたdocumentにlayerはあるか？
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}

	// layer数を取得
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	// layer名から該当layerの添え字を調べる
	std::string layerNameString(_layerName);
	int layerIndex = FindLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	// layer内にデータはあるか？
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("レイヤー名:%sにマップデータがありません\n", _layerName);
		return false;
	}

	// レイヤーよりrapidjson配列作成
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	// ユーザー配列確保　行方向、列方向の順番にサイズ確保
	_mapData.resize(height);
	for (auto& mapItr : _mapData)
	{
		mapItr.resize(width);
	}

	// ユーザー配列（２次元）にデータをコピー
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			//なぜかIDが+1ずれているので補正する
			_mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}

	return true;
}

int Map::FindLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, std::string& _layerName)
{
	int layerSize = _layer.Size();
	int i;

	std::string layerNameString(_layerName);

	for (i = 0; i < layerSize; ++i)
	{
		std::string currentLayerName = _layer[i]["name"].GetString();
		// 現在のレイヤー名(デバック)@
		printf("%s\n", currentLayerName.c_str());

		if (layerNameString == currentLayerName)
		{
			break;
		}
	}
	if (i == layerSize)
	{
		return -1;
	}

	return i;
}

void Map::Draw()
{
	for (auto ground : mGround)
	{
		ground->Draw();
	}
}
