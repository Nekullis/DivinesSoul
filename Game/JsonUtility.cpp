#include "JsonUtility.h"

JsonUtility::JsonUtility() {
	json = nullptr;
	// jsonstring = nullptr;
}

JsonUtility::~JsonUtility() {

}

nlohmann::json JsonUtility::Import(const std::string& filepath) {
	std::ifstream file(filepath);
	file >> json;
	return json;
}

void JsonUtility::strWrite(const std::string& jdata) {
	// クラス内のjsonデータに書き込み
	// Init();←必要とあらば個別に
	json = nlohmann::json::parse(jdata);
}

void JsonUtility::Save(const std::string& filepath) {
	std::ofstream file(filepath);
	file << std::setw(3) << json << std::endl;
}

