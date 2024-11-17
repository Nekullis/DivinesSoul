//// Appframe側のModeSoundLayer,SoundServer, SoundItemは一応ひな形として置いている。
//// 全然こちらを読み込めるようにして使ってもいいが、実際のソリューション側に今は作る。
//#pragma once
//#include "SoundItem.h"
//
//#include <string>
//#include <map>
//
//class SoundServer
//{
//public:
//	SoundServer();
//	virtual ~SoundServer();
//
//	void Clear();
//	void Add(SoundItemOneShot* snd);
//	void Add(std::string name, SoundItemBase* snd);
//	bool Del(std::string name);
//	bool Del(SoundItemBase* snd);
//	SoundItemBase* Get(std::string name);
//
//	std::map<std::string, SoundItemBase*>& GetVector() { return _v; }
//
//	void StopType(SoundItemBase::TYPE type);
//
//	void Update();
//
//protected:
//	bool	_isUpdate;
//	std::map<std::string, SoundItemBase*> _v;
//
//	std::map<std::string, SoundItemBase*> _vAdd;
//	std::map<std::string, SoundItemBase*> _vDel;
//
//	int		_cntOneShot;
//};
//
