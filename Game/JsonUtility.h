//----------------------------------------------------------------------
// @filename JsonUtility.h
// @author: Nara Mitsuki
// @explanation
// jsonクラス
// jsonを扱えるようにするためのクラス
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
	// 読み込み・書き込み
	// このクラスのjsonデータに外部のjsonファイルを読み込み 
	nlohmann::json Import(const std::string& filepath); 
	// jsonデータの中の一要素を指定したメンバ変数に代入
	template <typename T>
	void Read(const std::string& jmem, T &mem);

	// 他のクラスで変更されたデータをこのクラスで保持しているjsonデータに上書きもしくは追加する
	void strWrite(const std::string& jdata);  //     std::string jdata = R"({ ~通常のjsonファイルの記述~ })"; 　　をつくって記述する
	template <typename T>
	void jsonWrite(const std::string& name, const T& variable); // このクラスで保有しているjsonファイルに一要素を上書きもしくは追加
	void Save(const std::string& filename);

	nlohmann::json Getjson() { return json; }  // Importで直接、外のjson型のデータに渡したくなかったらこちらを使ってください
	// 以下は試験的な関数なので後々変更または削除すること
	//template <typename T>
	//void ReadToMap(const std::string jmem, std::map<std::string,T> &mem); // mapコンテナにjsonデータを入れる

protected:
	// 情報を保持するためのファイル(読み書き出し兼用なのでセーブする前に読みだして置きたいデータがあれば別に移しておく)
	nlohmann::json json; 

};

template <typename T>
void JsonUtility::jsonWrite(const std::string& name, const T& variable) {
	// このクラスで保有しているjsonファイルに要素を上書きもしくは追加
	json[name] = variable;
}

template <typename T>
void JsonUtility::Read(const std::string& jmem,  T &mem) {
	// このクラスで保有しているjsonファイルにからjmemと同名のデータを渡す
	json.at(jmem).get_to(mem);
}

//template <typename T>
//void JsonUtility::ReadToMap(const std::string jmem, std::map<std::string, T>& mem) {
//	T any;
//	json.at(jmem).get_to(any);
//	mem.push_back(any);
//}