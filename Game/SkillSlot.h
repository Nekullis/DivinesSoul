#pragma once
#include "AppFrame.h"
#include  "ResourceServer.h"
#include  "JsonUtility.h"
#include "EnumInfo.h"
#include  <map>

constexpr float _to_nextdiv = 10000.0f;
//’Ç‰Á
constexpr auto MAX_VOICE = 8;

class SkillSlot{
public:
	//’Ç‰Á
	struct CALLVOICE
	{
		int callCnt;
		int maxCallCnt;
		bool isCall;
		std::string voiceCode;
	};
public:

	SkillSlot();
	virtual ~SkillSlot();

	void divineToNext(int slotnum);

	void divineToPrevious(int slotnum);

	void RegisterCall();

	void SlotVoice(int i);

	void CallProcess();

	void SlotSpin(int slotnum);

	void Process();
	
	void Render();

	std::array<kindDivine, 3> Getslot() { return _slot; }

	bool GetSpin() { return _isSpin; }

protected:

	int _slotdivine;

	int _spinspeed;

	int _reeltime;

	int _voiceNum;

	bool _isSpin;

	CALLVOICE _call[MAX_VOICE];

	std::array<kindDivine, 3> _slot;

};