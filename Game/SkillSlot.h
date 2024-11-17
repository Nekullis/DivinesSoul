//----------------------------------------------------------------------
// @filename SkillSlot.h
// @author: Fukuma Kyohei, Nara Mitsuki
// @explanation
// �X�L���X���b�g
// �g�p�ł���X�L����ύX�����邽�߂̃N���X
//----------------------------------------------------------------------
#pragma once
#include "AppFrame.h"
#include "ResourceServer.h"
#include "JsonUtility.h"
#include "EnumInfo.h"
#include  <map>

constexpr float _to_nextdiv = 10000.0f;
//�ǉ�
constexpr auto MAX_VOICE = 8;

class SkillSlot{
public:
	//�ǉ�
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
	//�{�C�X�o�^
	void RegisterCall();
	//�{�C�X�o��
	void SlotVoice(int i);
	//�{�C�X�Đ��֘A����
	void CallProcess();
	//�X���b�g��]����
	void SlotSpin(int slotnum);
	//�X���b�g�֘A�����܂Ƃ�
	void Process();
	//�X���b�g�`��
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