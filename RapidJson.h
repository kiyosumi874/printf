#pragma once
/* json�֘A */

/// <summary>
/// json�t�@�C���̃I�[�v��
/// </summary>
/// <param name="_inputDocument">rapidJson�I�u�W�F�N�g</param>
/// <param name="_inFileName">�J������Json�t�@�C���p�X</param>
/// <returns>treu : �t�@�C�����J���� , false : �t�@�C�����J���Ȃ�����</returns>
bool OpenJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName);

/// <summary>
/// Doc���ɂ��̃����o�[�͑��݂��邩
/// </summary>
/// <param name="_inputDocument">rapidJson�I�u�W�F�N�g</param>
/// <param name="_memberName">�����o��</param>
/// <returns>treu : ���݂��� , false : ���݂��Ȃ�����</returns>
bool IsExistMember(const rapidjson::Document& _inputDocument, const char* _memberName);

/// <summary>
/// ���̃����o�[�����݂��A���l����v���邩�H
/// </summary>
/// <param name="_inputDocument">rapidJson�I�u�W�F�N�g</param>
/// <param name="_memberName">�����o��</param>
/// <param name="_matchValue">���ׂ��������o���Ƀ}�b�`����l</param>
/// <returns>treu : ��v���� , false : ��v���Ȃ�����</returns>
bool IsExistMemberAndValue(const rapidjson::Document& _inputDocument, const char* _memberName, const char* _matchValue);

/// <summary>
/// �h�L�������g�Ƀ����o�����܂܂�邩
/// </summary>
/// <param name="_inputDocument">�h�L�������g</param>
/// <param name="_memberName">�����o��</param>
/// <returns>treu : �܂܂�� , false : �܂܂�Ȃ�</returns>
bool IsExistArrayName(const rapidjson::Document& _inputDocument, const char* _memberName);

/// <summary>
/// Value�l�������I��float�l�Ƃ��Ď擾
/// </summary>
/// <param name="_val">Value�l</param>
/// <returns>JSON�l(float�^)</returns>
float ForceGetFloat(const rapidjson::Value& _val);