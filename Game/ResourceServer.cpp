#include "ResourceServer.h"

ResourceServer::ResourceServer() {
	mClearAll();
}

ResourceServer::~ResourceServer() {
	mClearAll();
}

void ResourceServer::mClearAll() {
	mClearJson();
	mClearGraph();
	mClearDivGraph();
	mClearModel();
	mClearEffect();
}

void ResourceServer::mClearJson() {
	_mapJsonImport.clear();
}
void ResourceServer::mClearGraph() {
	_mapGraph.clear();
}
void ResourceServer::mClearDivGraph() {
	_mapDivGraph.clear();
}
void ResourceServer::mClearModel() {
	_mapModel.clear(); 
	// 後にオブジェクトサーバー内の削除とサーバー自体の削除を記入するかも
}
void ResourceServer::mClearEffect() {
	_mapEffect.clear();
	// 後にエフェクトサーバー内の削除とサーバー自体の削除を記入するかも
}


bool ResourceServer::JsonToJMap(const std::string& filepath) {
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	////////////////////////////////////////////////////////////////jUtilの生存範囲	
	nlohmann::json convert = jUtil->Import(filepath);
	
	for (nlohmann::json::iterator itr = convert.begin(); itr != convert.end(); itr++) {
		auto mapitr = _mapJsonImport.find(itr.key());
		if (mapitr != _mapJsonImport.end()) {
			continue;
		}
		else {
			std::string ResType = convert[itr.key()]["ResourceType"];
			std::string mString = convert[itr.key()]["Attribute"];
			BASIC_INFO Import = { convert[itr.key()]["FilePath"] , Object::NONE , Attribute::NONE};
			if (ResType == "GRAPH") {
				Import.TYPE = Object::GRAPH;
				if (mString == "IMAGE") {
					Import.ASSIST = Attribute::IMAGE;
				}
				else if (mString == "MOVIE") {
					Import.ASSIST = Attribute::MOVIE;
				}
				_mapJsonImport.emplace(itr.key(), Import);
			}
			else if (ResType == "DIVGRAPH") {
				Import.TYPE = Object::DIVGRAPH;
				_mapJsonImport.emplace(itr.key(), Import);
				DIVGRAPH_INFO temp;
				for (int i = 0; i < 5; i++) {
					temp.div[i] = convert[itr.key()]["Div"][i];
				}
				temp.INFO = Object::NONE;
				_mapDivGraph.emplace(itr.key(), temp);
			}
			else if (ResType == "MOVIE") {
				Import.TYPE = Object::MOVIE;
				_mapJsonImport.emplace(itr.key(), Import);
			}
			// 以下は専用のサーバーに保持になったら書き換える
			else if (ResType == "MODEL") {
				Import.TYPE = Object::MODEL;
				if (mString == "ENVIRONMENT") {
					Import.ASSIST = Attribute::ENVIRONMENT;
				}
				else if (mString == "STRUCTURE") {
					Import.ASSIST = Attribute::STRUCTURE;
				}
				else if (mString == "CHARACTER") {
					Import.ASSIST = Attribute::CHARACTER;
				}
				_mapJsonImport.emplace(itr.key(), Import);
				if (convert[itr.key()]["IsStatic"] == "dynamic") {
					int cnt = 0; // 各配列内の要素を同期させて読み込む
					for (const auto& index : convert[itr.key()]["Attach_Name"]) {
						ATTACH_INFO temp = { convert[itr.key()]["Attach_Index"][cnt], convert[itr.key()]["Attach_Time"][cnt], convert[itr.key()]["Attach_Speed"][cnt] };
						_mapModelAttach.emplace(index, temp);
						cnt++;
					}
				}
			}
			else if (ResType == "EFFECT") {
				Import.TYPE = Object::EFFECT;
				_mapJsonImport.emplace(itr.key(), Import);
				// アタッチする値があったらここで配列に組み込む
			}
		}		
	}
	////////////////////////////////////////////////////////////////
	delete jUtil;
	return true;
}

void ResourceServer::JMapToArray() {
	for (const auto& JMap : _mapJsonImport) {
		std::string path = JMap.second._filepath;// c_str含めて直に入れると長くて見づらいので
		switch (JMap.second.TYPE) {
		case Object::GRAPH:
		case Object::MOVIE:{
			auto itr = _mapGraph.find(JMap.first);
			if (itr != _mapGraph.end()) {
				continue;
			}
			else {
				GRAPH_INFO temp;
				temp._handle = LoadGraph(path.c_str());
				temp.INFO = JMap.second.TYPE;
				temp.COMMON = JMap.second.ASSIST;
				_mapGraph.emplace(JMap.first, temp);
			}
			break;
		}
		case Object::DIVGRAPH: {
			auto itr = _mapDivGraph.find(JMap.first);
			if (itr != _mapDivGraph.end() && itr->second.INFO == Object::NONE) {
				int* hbuf = new int[itr->second.div[0]];
				if (LoadDivGraph(path.c_str(), itr->second.div[0],
					itr->second.div[1], itr->second.div[2], itr->second.div[3], itr->second.div[4],
					hbuf) == 0) {
					itr->second.handle = hbuf;
					itr->second.INFO = JMap.second.TYPE;
				}
			}
			else {
				continue;
			}
			break;
		}
		case Object::MODEL: {
			auto itr = _mapModel.find(JMap.first);
			if (itr != _mapModel.end()) {
				continue;
			}
			else {
				MODEL_INFO temp;
				temp._handle = MV1LoadModel(path.c_str());
				temp.INFO = JMap.second.TYPE;
				temp.COMMON = JMap.second.ASSIST;
				_mapModel.emplace(JMap.first, temp);
			}
			break;
		}
		case Object::EFFECT: {
			auto itr = _mapEffect.find(JMap.first);
			if (itr != _mapEffect.end()) {
				continue;
			}
			else {
				EFFECT_INFO temp;
				temp._filepath = path;
				temp.INFO = JMap.second.TYPE;
				//temp.COMMON = JMap.second.ASSIST;
				_mapEffect.emplace(JMap.first, temp);
			}
			break;
		}
		}
	}
	mClearJson();
}

void ResourceServer::ExcludeObject_map(const std::string& filepath) {
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	////////////////////////////////////////////////////////////////jUtilの生存範囲	
	nlohmann::json exclude = jUtil->Import(filepath);

	for (nlohmann::json::iterator itr = exclude.begin(); itr != exclude.end(); itr++) {
		std::string ResType = exclude[itr.key()]["ResourceType"];
		if (ResType == "GRAPH") {
			auto graitr = _mapGraph.find(itr.key());
			if (graitr != _mapGraph.end()) {
				DeleteGraph(graitr->second._handle);
				_mapGraph.erase(itr.key());
			}
		}
		else if (ResType == "DIVGRAPH") {// いったん保留
			auto divitr = _mapDivGraph.find(itr.key());
			if (divitr != _mapDivGraph.end()) {
				for (int i = 0; i < divitr->second.div[0]; i++) {
					DeleteGraph(divitr->second.handle[i]);
				}
				delete[] divitr->second.handle;
				_mapDivGraph.erase(itr.key());
			}
		}
		else if (ResType == "MODEL") {
			auto moditr = _mapModel.find(itr.key());
			if (moditr != _mapModel.end()) {
				MV1DeleteModel(moditr->second._handle);
				_mapModel.erase(itr.key());
			}
			if (exclude[itr.key()]["IsStatic"] == "dynamic") {
				for (auto& index : exclude[itr.key()]["Attach_Name"]) {
				  auto attitr = 	_mapModelAttach.find(index);
					if (attitr != _mapModelAttach.end()) {
						_mapModelAttach.erase(index);
					}
				}
			}
		}
		else if (ResType == "EFFECT") {
			auto effitr = _mapEffect.find(itr.key());
			if (effitr != _mapEffect.end()) {
				_mapEffect.erase(itr.key());
			}
		}
	}
	////////////////////////////////////////////////////////////////
	delete jUtil;
}

int ResourceServer::SearchInArray(const std::string& key, const Object TYPE) {
	switch (TYPE) {
	case Object::GRAPH: {
		auto itr = _mapGraph.find(key);
		if (itr != _mapGraph.end()) {
			return 1;
		}
		else {
			return -1;
		}
		break;
	}
	case Object::DIVGRAPH: {
		auto itr = _mapDivGraph.find(key);
		if (itr != _mapDivGraph.end()) {
			return 2;
		}
		else {
			return -1;
		}
		break;
	}
	case Object::MODEL: {
		auto itr = _mapModel.find(key);
		if (itr != _mapModel.end()) {
			return 3;
		}
		else {
			return -1;
		}
		break;
	}
	case Object::EFFECT: {
		auto itr = _mapEffect.find(key);
		if (itr != _mapEffect.end()) {
			return 4;
		}
		else {
			return -1;
		}
		break;
	}
	case Object::NONE: {
		return -1;
		break;
	}
	}
}

bool ResourceServer::Add(const std::string& key) {
	auto itr = _mapJsonImport.find(key);
	if (itr != _mapJsonImport.end()) {
		switch (SearchInArray(key, itr->second.TYPE)) {
		case 1:		
		case 3:
		case 4: {
			return false;
			break;
		}
		case 2: {
			DIVGRAPH_INFO temp;
				int* hbuf = new int[_mapDivGraph[key].div[0]];
				if (LoadDivGraph(itr->second._filepath.c_str(), _mapDivGraph[key].div[0],
					_mapDivGraph[key].div[1], _mapDivGraph[key].div[2], _mapDivGraph[key].div[3], _mapDivGraph[key].div[4],
					hbuf) == 0) {
					_mapDivGraph[key].handle = hbuf;
					_mapDivGraph[key].INFO = itr->second.TYPE;
					return true;
				}
		}
		case -1: {
			switch (itr->second.TYPE){
			case Object::GRAPH:
			case Object::MOVIE: {
				GRAPH_INFO temp;
				temp._handle = LoadGraph(itr->second._filepath.c_str());
				temp.INFO = itr->second.TYPE;
				temp.COMMON = itr->second.ASSIST;
				_mapGraph.emplace(key, temp);
				break;
			}
			case Object::MODEL: {
				MODEL_INFO temp;
				temp._handle = MV1LoadModel(itr->second._filepath.c_str());
				temp.INFO = itr->second.TYPE;
				temp.COMMON = itr->second.ASSIST;
				_mapModel.emplace(key, temp);
				break;
			}
			case Object::EFFECT: {
				EFFECT_INFO temp;
				temp._filepath = LoadGraph(itr->second._filepath.c_str());
				temp.INFO = itr->second.TYPE;
				//temp.COMMON = JMap.second.ASSIST;
				_mapEffect.emplace(key, temp);
				break;
			}
			   return true;
			}
			break;
		}
		}
	}
	else {
		return false;
	}
}