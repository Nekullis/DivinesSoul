//// Appframe����ModeSoundLayer,SoundServer, SoundItem�͈ꉞ�ЂȌ`�Ƃ��Ēu���Ă���B
//// �S�R�������ǂݍ��߂�悤�ɂ��Ďg���Ă��������A���ۂ̃\�����[�V�������ɍ��͍��B
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
