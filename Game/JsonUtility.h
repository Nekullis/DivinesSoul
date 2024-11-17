//----------------------------------------------------------------------
// @filename JsonUtility.h
// @author: Nara Mitsuki
// @explanation
// json�N���X
// json��������悤�ɂ��邽�߂̃N���X
//----------------------------------------------------------------------
#pragma once
#include "nlohmann/json.hpp"
#include <fstream>

class JsonUtility
{
public:
	JsonUtility();
	virtual ~JsonUtility();

	void Init() { json = nullptr; }
	// �ǂݍ��݁E��������
	// ���̃N���X��json�f�[�^�ɊO����json�t�@�C����ǂݍ��� 
	nlohmann::json Import(const std::string& filepath); 
	// json�f�[�^�̒��̈�v�f���w�肵�������o�ϐ��ɑ��
	template <typename T>
	void Read(const std::string& jmem, T &mem);

	// ���̃N���X�ŕύX���ꂽ�f�[�^�����̃N���X�ŕێ����Ă���json�f�[�^�ɏ㏑���������͒ǉ�����
	void strWrite(const std::string& jdata);  //     std::string jdata = R"({ ~�ʏ��json�t�@�C���̋L�q~ })"; �@�@�������ċL�q����
	template <typename T>
	void jsonWrite(const std::string& name, const T& variable); // ���̃N���X�ŕۗL���Ă���json�t�@�C���Ɉ�v�f���㏑���������͒ǉ�
	void Save(const std::string& filename);

	nlohmann::json Getjson() { return json; }  // Import�Œ��ځA�O��json�^�̃f�[�^�ɓn�������Ȃ������炱������g���Ă�������
	// �ȉ��͎����I�Ȋ֐��Ȃ̂Ō�X�ύX�܂��͍폜���邱��
	//template <typename T>
	//void ReadToMap(const std::string jmem, std::map<std::string,T> &mem); // map�R���e�i��json�f�[�^������

protected:
	// ����ێ����邽�߂̃t�@�C��(�ǂݏ����o�����p�Ȃ̂ŃZ�[�u����O�ɓǂ݂����Ēu�������f�[�^������ΕʂɈڂ��Ă���)
	nlohmann::json json; 

};

template <typename T>
void JsonUtility::jsonWrite(const std::string& name, const T& variable) {
	// ���̃N���X�ŕۗL���Ă���json�t�@�C���ɗv�f���㏑���������͒ǉ�
	json[name] = variable;
}

template <typename T>
void JsonUtility::Read(const std::string& jmem,  T &mem) {
	// ���̃N���X�ŕۗL���Ă���json�t�@�C���ɂ���jmem�Ɠ����̃f�[�^��n��
	json.at(jmem).get_to(mem);
}

//template <typename T>
//void JsonUtility::ReadToMap(const std::string jmem, std::map<std::string, T>& mem) {
//	T any;
//	json.at(jmem).get_to(any);
//	mem.push_back(any);
//}