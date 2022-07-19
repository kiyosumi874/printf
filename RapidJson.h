#pragma once
/* json関連 */

/// <summary>
/// jsonファイルのオープン
/// </summary>
/// <param name="_inputDocument">rapidJsonオブジェクト</param>
/// <param name="_inFileName">開きたいJsonファイルパス</param>
/// <returns>treu : ファイルが開けた , false : ファイルが開けなかった</returns>
bool OpenJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName);

/// <summary>
/// Doc内にそのメンバーは存在するか
/// </summary>
/// <param name="_inputDocument">rapidJsonオブジェクト</param>
/// <param name="_memberName">メンバ名</param>
/// <returns>treu : 存在した , false : 存在しなかった</returns>
bool IsExistMember(const rapidjson::Document& _inputDocument, const char* _memberName);

/// <summary>
/// そのメンバーが存在し、かつ値が一致するか？
/// </summary>
/// <param name="_inputDocument">rapidJsonオブジェクト</param>
/// <param name="_memberName">メンバ名</param>
/// <param name="_matchValue">調べたいメンバ名にマッチする値</param>
/// <returns>treu : 一致した , false : 一致しなかった</returns>
bool IsExistMemberAndValue(const rapidjson::Document& _inputDocument, const char* _memberName, const char* _matchValue);

/// <summary>
/// ドキュメントにメンバ名が含まれるか
/// </summary>
/// <param name="_inputDocument">ドキュメント</param>
/// <param name="_memberName">メンバ名</param>
/// <returns>treu : 含まれる , false : 含まれない</returns>
bool IsExistArrayName(const rapidjson::Document& _inputDocument, const char* _memberName);

/// <summary>
/// Value値を強制的にfloat値として取得
/// </summary>
/// <param name="_val">Value値</param>
/// <returns>JSON値(float型)</returns>
float ForceGetFloat(const rapidjson::Value& _val);