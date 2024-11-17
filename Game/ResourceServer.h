#pragma once
#include "AppFrame.h"
#include "JsonUtility.h"

// 最終的にはjsonデータでまとめた画像のアドレスをまとめて読み込めるようにしたい →　jsonデータで”自分で決めたキー”と”オブジェクトの種類,ファイルパス”でまとめたデータを作ってそれを一度読み込む（その都度で必要となるデータを）
// モデルに関しては動くものがあり保持する情報が多いので、サウンドのように独自クラスにするかも
// objectType {environment , object ,character}　オブジェクトマネージャーにするかは要考慮 ->後回し
// →　このクラスにオブジェクトサーバーをくっつけてそこで管理する（attach_time, attach_index等もそこから引っ張る）
// IsStatic{static , dynamic}


enum class Object {
	NONE = 0, GRAPH, DIVGRAPH, MOVIE, MODEL, EFFECT
};

enum class Attribute {
	NONE, ENVIRONMENT, STRUCTURE, CHARACTER, IMAGE, MOVIE
};

// 略語はObjectJson内の項目に準ずる
// RN = ResourceName = std::string
// RT = ResourceType = Object
// RH = ResourceHandle,メモリに読み込んだ素材のハンドル = int
// AB = Attribute = Attribute
// IS  = IsStatic = bool
// AN = AnimationName = std::string
// AI  = AnimationIndex = int
// AT = AnimationTime = float
// AS = AnimationSpeed = float
enum class Reference {
	RN, RT, RH, AB, IS, AN, AI, AT, AS
};


struct BASIC_INFO {
	std::string _filepath;
	Object TYPE;
	Attribute ASSIST;
};

struct GRAPH_INFO {
	int _handle;
	Object INFO;
	Attribute  COMMON;
};

struct MODEL_INFO {
	int _handle;
	Object INFO;
	Attribute  COMMON;
};

struct ATTACH_INFO {
	int _attach_index;
	float _attach_time, _attach_speed;
};

struct EFFECT_INFO {
	std::string _filepath;
	Object INFO;
	// Attribute COMMON; いったん保留
};

struct DIVGRAPH_INFO {
	int	div[5];
	int* handle;
	Object INFO;
};

class ResourceServer{
public:
	ResourceServer();
	virtual ~ResourceServer();

	// マップ配列の中身を消去
	void mClearAll();
	void mClearJson();
	void mClearGraph();
	void mClearDivGraph();
	void mClearModel();
	void mClearEffect();

	// jsonデータをマップ配列にインポート
	bool JsonToJMap(const std::string& filepath);

	// jsonImportにあるデータを各配列に移動後、mapjsonを空にする
	void JMapToArray();
	
	// 指定したJsonファイルのデータに含まれているオブジェクトを各マップ配列から削除する
	void ExcludeObject_map(const std::string& filepath);

	// Jsonmapから指定の要素を各配列に追加
	bool Add(const std::string& key);

	// 各配列から指定の要素を削除
	bool Delete(const std::string& key);

protected:	
	std::unordered_map<std::string, BASIC_INFO> _mapJsonImport; 
	std::unordered_map<std::string, BASIC_INFO> _mapAdd;// 個々に追加する要素用のJson配列
	std::unordered_map<std::string, BASIC_INFO> _mapDel;// 削除するようののJson配列
	std::unordered_map<std::string, GRAPH_INFO>	_mapGraph; // movieもここにハンドルを入れる
	std::unordered_map<std::string, DIVGRAPH_INFO>	_mapDivGraph;// divgraphに関しては今回は使う見込みが薄いので後回し（分割の数など）
	
	std::unordered_map<std::string, MODEL_INFO> _mapModel;  // 一応仮置きの配列→専用のサーバー内で管理するかも
	std::unordered_map<std::string, EFFECT_INFO> _mapEffect;   // 一応仮置きの配列→専用のサーバー内で管理するかも
	std::unordered_map<std::string, ATTACH_INFO> _mapModelAttach;
	// 一応仮置きの配列→専用のサーバー内で管理するかも---専用サーバー化した際にはオブジェクトごとに小分けにするー＞_mapModelAttach

public:	

	Object GetTNone() { return Object::NONE; } Object GetTGraph() { return Object::GRAPH; } 	Object GetTDiv() { return Object::DIVGRAPH; } 	Object GetTModel() { return Object::MODEL; } 	Object GetTEffect() { return Object::EFFECT; }

	Attribute GetANone() { return Attribute::NONE; } Attribute GetAEnvi() { return Attribute::ENVIRONMENT; } Attribute GetAStruc() { return Attribute::STRUCTURE; } Attribute GetAChara() { return Attribute::CHARACTER; }
	Attribute GetAImage() { return Attribute::IMAGE; } Attribute GetAMovie() { return Attribute::MOVIE; }

	Reference GetRRN() { return Reference::RN; } Reference GetRRT() { return Reference::RT; } Reference GetRRH() { return Reference::RH; }Reference GetRAB() { return Reference::AB; } Reference GetRIS() { return Reference::IS; } 
	Reference GetRAN() { return Reference::AN; } Reference GetRAI() { return Reference::AI; } Reference GetRAT() { return Reference::AT; } Reference GetRAS() { return Reference::AS; }

	std::unordered_map<std::string, GRAPH_INFO> mGetGraph() { return _mapGraph; }
	std::unordered_map<std::string, DIVGRAPH_INFO>	mGetDivGraph() { return _mapDivGraph; }
	std::unordered_map<std::string, MODEL_INFO> mGetModel() { return _mapModel; }
	std::unordered_map<std::string, EFFECT_INFO> mGetEffect() { return _mapEffect; }
	std::unordered_map<std::string, ATTACH_INFO> mGetAttach() { return _mapModelAttach; }

	// map配列に指定したキーかつタイプのオブジェクトが存在するか確認する
// 返り値はサーバー存在しない = -1, graph = 1, divgraph= 2, model = 3, effect = 4,
	int SearchInArray(const std::string& key, const Object TYPE);

	// ResourceServer内のオブジェクトの参照したい値を持ってくる
	// TYPE = Object::NONEにした場合はモデルにアタッチしたモーションの検索になる
	//template <typename T>
	//T GetRef(std::string& key, Object TYPE, Reference ELEMENT);
};



//
//template <typename T> // DivGraphはいったん保留
//T ResourceServer::GetRef(std::string& key, Object TYPE, Reference ELEMENT) {
//	if (TYPE != Object::NONE) {
//		if (ELEMENT == Reference::AN || ELEMENT == Reference::AI || ELEMENT == Reference::AT || ELEMENT == Reference::AS) {
//			return -1;
//		}
//		switch (SearchInArray(key, TYPE)) {
//		case 1: {
//			auto itr = _mapGraph.find(key);
//			switch (ELEMENT) {
//			case RN: {
//				return key;
//				break;
//			}
//			case RT: {
//				std::string rType = itr->second.INFO;
//				return rType;
//				break;
//			}
//			case RH: {
//				int handle = itr->second._handle;
//				return handle;
//				break;
//			}
//			case AB: {
//				Object common = itr->second.COMMON;
//				return common;
//				break;
//			}
//			}
//			break;
//		}
//		case 2: {
//			auto itr = _mapDivGraph.find(key);
//			//switch (ELEMENT) {
//			//case RN: {
//			//	return key;
//			//	break;
//			//}
//			//case RT: {
//			//	std::string rType = itr->second.INFO;
//			//	return rType;
//			//	break;
//			//}
//			//case RH: {
//			//	int handle = itr->second._handle;
//			//	return handle;
//			//	break;
//			//}
//			//case AB: {
//			//	Object common = itr->second.COMMON;
//			//	return common;
//			//	break;
//			//}
//			//}
//			break;
//		}
//		case 3: {
//			auto itr = _mapModel.find(key);
//			auto attach_itr = _mapModelAttach(key);
//			switch (ELEMENT) {
//			case RN: {
//				return key;
//				break;
//			}
//			case RT: {
//				std::string rType = itr->second.INFO;
//				return rType;
//				break;
//			}
//			case RH: {
//				int handle = itr->second._handle;
//				return handle;
//				break;
//			}
//			case AB: {
//				Object common = itr->second.COMMON;
//				return common;
//				break;
//			}
//			}
//			break;
//		}
//		case 4: {
//			auto itr = _mapEffect.find(key);
//			switch (ELEMENT) {
//			case RN: {
//				return key;
//				break;
//			}
//			case RT: {
//				std::string rType = itr->second.INFO;
//				return rType;
//				break;
//			}
//			case RH: {
//				std::string filepath = itr->second._filepath;
//				return filepath;
//				break;
//			}
//			//case AB: {
//			//	Object common = itr->second.COMMON;
//			//	return common;
//			//	break;
//			//}
//			}
//			break;
//		}
//		case -1: {
//			return -1;
//			break;
//		}
//		}
//	}
//	else {
//		if (ELEMENT == Reference::AN && ELEMENT == Reference::AI && ELEMENT == Reference::AT && ELEMENT == Reference::AS) {
//			return -1;
//		}
//		auto itr = _mapModelAttach(key);
//		switch (ELEMENT) {
//		case IS: {
//			if (itr != _mapModelAttach.end()) {
//				return true;
//			}
//			else {
//				return false;
//			}
//			break;
//		}
//		case AN: {
//			return key;
//			break;
//		}
//		case AI: {
//			int index = itr->second._attach_index;
//			return  index;
//			break;
//		}
//		case AT: {
//			float time = itr->second._attach_time;
//			return time;
//			break;
//		}
//		case AS: {
//			float speed = itr->second._attach_speed;
//			return speed;
//			break;
//		}		
//		}
//	}
//}