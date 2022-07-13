#include "pch.h"

bool OpenJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName)
{
	// jsonファイルを開けるか
	std::ifstream file(_inFileName);
	// ファイルが開けなかったら
	if (!file)
	{
		return false;
	}

	// filestreamにファイル文字列を取り込む
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();

	// ファイル文字列をjson文字列に変換
	rapidjson::StringStream jsonStr(contents.c_str());

	// ファイルを閉じる
	file.close();

	// 解析オブジェクト作成
	_inputDocument.ParseStream(jsonStr);

	// jsonObjectとして読めなかったら
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
	// メンバーが存在しなかったら
	if (!IsExistMember(_inputDocument, _memberName))
	{
		return false;
	}

	std::string findValueString;
	findValueString = std::string(_matchValue);

	// 値が一致しなかったら
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
