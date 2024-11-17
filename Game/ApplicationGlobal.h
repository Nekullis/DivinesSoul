#pragma once
#include "appframe.h"
#include "PlayerManager.h"
#include "ResourceServer.h"
#include "SoundServer.h"

// モードを超えて保持したい情報などを記録する(後々リソースサーバーの追加をする)
class ApplicationGlobal
{public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();

	void PadInput();
	
	// Globalのみ例外でよく使うので短めにします
	ResourceServer* _RS;
	GamePad* _gPad;
	PlayerManager* _PM;
	SoundServer _sndServer;
	std::unordered_map<std::string, GRAPH_INFO> mGetGraph() { return _RS->mGetGraph(); }
	std::unordered_map<std::string, DIVGRAPH_INFO> mGetDivGraph() { return _RS->mGetDivGraph(); }
	std::unordered_map<std::string, MODEL_INFO> mGetModel() { return _RS->mGetModel(); }
	std::unordered_map<std::string, EFFECT_INFO> mGetEffect() { return _RS->mGetEffect(); }
	std::unordered_map<std::string, ATTACH_INFO> mGetAttach() { return _RS->mGetAttach(); }


	 enum class stage  {
		none , stage1, stage2, stage3
	};
	stage stageNum;

	int		_gKey, _gTrg, _gRel;
	MyStruct::ANALOGSTICK _gSti;
	bool _isLoad;
protected:

};

extern ApplicationGlobal gGlobal;