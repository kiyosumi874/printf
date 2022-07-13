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
	// �f�[�^�̓ǂݍ���
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
	// ���s
	for (float iz = 0; iz < m_mapSize.h; ++iz)
	{
		// ����
		for (float ix = 0; ix < m_mapSize.w; ++ix)
		{
			// ���蓖�Ă��Ă��鐔��
			const unsigned int name = m_groundMapDate[(int)iz][(int)ix];

			// �|�W�V����
			const VECTOR objPos = VECTOR(VGet(-m_objDistance.x * ix, 0.0f, m_objDistance.z * iz));

			// ���蓖�Ă��Ă��鐔����1��������
			if (name == 1)
			{
				mGround.emplace_back(new Ground(objPos));
				//new Ground(objPos); // ���̐���
			}

			
		}

	}
}

bool Map::ReadTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	// RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!OpenJsonFile(doc, _fileName))
	{
		return false;
	}
	// �J����document��type��map���H
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}
	// �J����document��layer�͂��邩�H
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}

	// layer�����擾
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	// layer������Y��layer�̓Y�����𒲂ׂ�
	std::string layerNameString(_layerName);
	int layerIndex = FindLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	// layer���Ƀf�[�^�͂��邩�H
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", _layerName);
		return false;
	}

	// ���C���[���rapidjson�z��쐬
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	// ���[�U�[�z��m�ہ@�s�����A������̏��ԂɃT�C�Y�m��
	_mapData.resize(height);
	for (auto& mapItr : _mapData)
	{
		mapItr.resize(width);
	}

	// ���[�U�[�z��i�Q�����j�Ƀf�[�^���R�s�[
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			//�Ȃ���ID��+1����Ă���̂ŕ␳����
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
		// ���݂̃��C���[��(�f�o�b�N)@
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
