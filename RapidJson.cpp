#include "pch.h"

bool OpenJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName)
{
	// json�t�@�C�����J���邩
	std::ifstream file(_inFileName);
	// �t�@�C�����J���Ȃ�������
	if (!file)
	{
		return false;
	}

	// filestream�Ƀt�@�C�����������荞��
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();

	// �t�@�C���������json������ɕϊ�
	rapidjson::StringStream jsonStr(contents.c_str());

	// �t�@�C�������
	file.close();

	// ��̓I�u�W�F�N�g�쐬
	_inputDocument.ParseStream(jsonStr);

	// jsonObject�Ƃ��ēǂ߂Ȃ�������
	if (!_inputDocument.IsObject())
	{
		return false;
	}

	return true;
}

bool IsExistMember(const rapidjson::Document& _inputDocument, const char* _memberName)
{
	rapidjson::Value::ConstMemberIterator itr;
	itr = _inputDocument.FindMember(_memberName);

	if (itr == _inputDocument.MemberEnd())
	{
		return false;
	}

	return true;
}

bool IsExistMemberAndValue(const rapidjson::Document& _inputDocument, const char* _memberName, const char* _matchValue)
{
	// �����o�[�����݂��Ȃ�������
	if (!IsExistMember(_inputDocument, _memberName))
	{
		return false;
	}

	std::string findValueString;
	findValueString = std::string(_matchValue);

	// �l����v���Ȃ�������
	if (findValueString != _inputDocument[_memberName].GetString())
	{
		return false;
	}

	return true;
}

bool IsExistArrayName(const rapidjson::Document& _inputDocument, const char* _memberName)
{
	rapidjson::Value::ConstMemberIterator itr;
	itr = _inputDocument.FindMember(_memberName);

	if (itr == _inputDocument.MemberEnd())
	{
		return false;
	}

	return _inputDocument[_memberName].IsArray();
}

float ForceGetFloat(const rapidjson::Value& _val)
{
	std::string tmp;
	tmp = _val.GetString();

	return static_cast<float>(atof(tmp.c_str()));
}
