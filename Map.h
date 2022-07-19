#pragma once

/* �}�b�v�����N���X */
class Map
{
public:
	// �R���X�g���N�^
	Map();
	// �f�X�g���N�^
	~Map();

	/// <summary>
	/// json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
	/// </summary>
	/// <returns>true : �t�@�C�����J���� , false : �t�@�C�����J���Ȃ�����</returns>
	bool OpenFile();

	// ���𐶐�����
	void GroundCreate();
	// �v���C���[�𐶐�����
	void PlayerCreate();

	// �f�o�b�O�p
	std::vector<Ground*> mGround;
	void Draw();

private:
	/// <summary>
	/// �f�[�^�̓ǂݍ��ݏ���
	/// </summary>
	/// <param name="_mapData">�f�[�^</param>
	/// <param name="_fileName">�t�@�C����</param>
	/// <param name="_layerName">���C���[��</param>
	/// <returns>true : �ǂݍ��݊��� , false : �ǂݍ��ݎ��s</returns>
	bool ReadTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	/// <summary>
	/// �S�Ă�layer����Y��layer�̓Y�����𒲂ׂ�
	/// </summary>
	/// <param name="_layer">layer�S��</param>
	/// <param name="_layerName">�Y�����C���[��</param>
	/// <returns>-1 : �Ȃ�����</returns>
	int FindLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, std::string& _layerName);

	std::vector<std::vector<int>> m_groundMapDate; // ���̃}�b�v�f�[�^
	std::vector<std::vector<int>> m_playerMapDate; // ���̃}�b�v�f�[�^

	Size m_mapSize;                       // �}�b�v�f�[�^�T�C�Y(w,h)
	VECTOR m_objDistance;                 // �I�u�W�F�N�g���Ƃ̋���(x,y,z)

};