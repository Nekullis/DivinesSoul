#include "SkillSlot.h"
#include "ApplicationGlobal.h"
#include "GameEvent.h"
SkillSlot::SkillSlot() {
	_slotdivine = 0;
	_spinspeed = 5000;
	_reeltime = 0;
	for (int i = 0; i < _slot.size(); i++) {
		if (i == 0) {
			_slot[i] = kindDivine::BLEATH;
		}
		if (i == 1) {
			_slot[i] = kindDivine::CIRCLE;
		}
		if (i == 2) {
			_slot[i] = kindDivine::DASH;
		}
	}
	RegisterCall();
	_voiceNum = -1;
	_isSpin = false;
}

SkillSlot::~SkillSlot() {


}

void SkillSlot::RegisterCall(){
	//���[�J���ō\���̂��`
	CALLVOICE call[MAX_VOICE]
	{
		{0,180,false,"VO_Ca_Breath"},
		{0,180,false,"VO_Ca_Circle"},
		{0,180,false,"VO_Ca_Laser"},
		{0,180,false,"VO_Ca_Slash"},
		{0,180,false,"VO_Ca_Explosion"},
		{0,180,false,"VO_Ca_Dash"},
		{0,180,false,"VO_Ca_Vacuum"},
		{0,180,false,"VO_Ca_Sonic"},
	};
	for (int i = 0; i < MAX_VOICE; i++)
	{	//���g���ړ�
		_call[i] = std::move(call[i]);
	}
}

void SkillSlot::SlotVoice(int i)
{
	//�{�C�X�ԍ�����
	_voiceNum = i;
	//�Đ����Ȃ̂�true��
	_call[_voiceNum].isCall = true;
	//�{�C�X�L�[����
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(_call[_voiceNum].voiceCode);
	//�J�E���g���K�萔�ɒB���Ă��Ȃ�
	if (_call[_voiceNum].callCnt <= _call[_voiceNum].maxCallCnt)
	{
		if (snditem_voice && snditem_voice->IsLoad())
		{	// �Đ����łȂ��Ȃ�
			if (snditem_voice->IsPlay() == false)
			{	// �Đ�����
				snditem_voice->Play();
			}
		}
	}
}

void SkillSlot::CallProcess()
{
	//�Đ����Ȃ�΃J�E���g���Z
	if (_call[_voiceNum].isCall) { _call[_voiceNum].callCnt++; }
	//�J�E���g���K�萔�ɒB����
	if (_call[_voiceNum].callCnt >= _call[_voiceNum].maxCallCnt)
	{	//�Đ�����������̂�false��
		_call[_voiceNum].isCall = false;
	}
}

void SkillSlot::divineToNext(int slotnum) {
	switch (_slot[slotnum ]) {
	case kindDivine::BLEATH: {
		_slot[slotnum] = kindDivine::CIRCLE;
		break;
	}
	case kindDivine::CIRCLE: {
		_slot[slotnum] = kindDivine::LASER;
		break;
	}
	case kindDivine::LASER: {
		_slot[slotnum] = kindDivine::SLASH;
		break;
	}
	case kindDivine::SLASH: {
		_slot[slotnum] = kindDivine::EXPLOSION;
		break;
	}
	case kindDivine::EXPLOSION: {
		_slot[slotnum] = kindDivine::SONIC_WAVE;
		break;
	}
	case kindDivine::SONIC_WAVE: {
		_slot[slotnum] = kindDivine::VACCUM;
		break;
	}
	case kindDivine::VACCUM: {
		_slot[slotnum] = kindDivine::DASH;
		break;
	}
	case kindDivine::DASH: {
		_slot[slotnum] = kindDivine::BLEATH;
		break;
	}
	}

}
void SkillSlot::divineToPrevious(int slotnum){
	switch (_slot[slotnum]) {
	case kindDivine::BLEATH: {
		_slot[slotnum] = kindDivine::DASH;
		break;
	}
	case kindDivine::CIRCLE: {
		_slot[slotnum] = kindDivine::BLEATH;
		break;
	}
	case kindDivine::LASER: {
		_slot[slotnum] = kindDivine::CIRCLE;
		break;
	}
	case kindDivine::SLASH: {
		_slot[slotnum] = kindDivine::LASER;
		break;
	}
	case kindDivine::EXPLOSION: {
		_slot[slotnum] = kindDivine::SLASH;
		break;
	}
	case kindDivine::SONIC_WAVE: {
		_slot[slotnum] = kindDivine::EXPLOSION;
		break;
	}
	case kindDivine::VACCUM: {
		_slot[slotnum] = kindDivine::SONIC_WAVE;
		break;
	}
	case kindDivine::DASH: {
		_slot[slotnum] = kindDivine::VACCUM;
		break;
	}
	}
}


void SkillSlot::SlotSpin(int slotnum){
	SoundItemBase* snditem_se = gGlobal._sndServer.Get("SE_Slot_Finish");
	if (_spinspeed > 0) {
		_isSpin = true;
		_reeltime += _spinspeed;
		_spinspeed -= 30;
	}
	if (_reeltime >= _to_nextdiv) {
		_slotdivine = rand() % 8;
		_reeltime = 0;
	}
	if (_spinspeed <= 0) {
		_reeltime = 0;
		kindDivine divine = static_cast <kindDivine>(_slotdivine);
		_slot[slotnum] = divine;
		while (1)
		{
			if (_slot[0] != _slot[1] && 
				_slot[1] != _slot[2] && 
				_slot[2] != _slot[0]) { break; }
			_slotdivine++;
			divine = static_cast <kindDivine>(_slotdivine);
			_slot[slotnum] = divine;
		}
		snditem_se->Play();
		SlotVoice(_slotdivine);
		_spinspeed = 5000;
		_isSpin = false;
		if (GameEvent::GetInstance()->GetDivineEvent() == 0)
		{
			GameEvent::GetInstance()->SetDivineEvent(1);
		}
	}
}

void SkillSlot::Process()
{
	CallProcess();
}

void SkillSlot::Render() 
{
	int cg[8] =
	{
		gGlobal.mGetGraph()["UI_skill_bleath"]._handle,
		gGlobal.mGetGraph()["UI_skill_sircle"]._handle,
		gGlobal.mGetGraph()["UI_skill_lasar"]._handle,
		gGlobal.mGetGraph()["UI_skill_slash"]._handle,
		gGlobal.mGetGraph()["UI_skill_explosion"]._handle,
		gGlobal.mGetGraph()["UI_skill_dashattack"]._handle,
		gGlobal.mGetGraph()["UI_skill_vacuum"]._handle,
		gGlobal.mGetGraph()["UI_skill_sonic"]._handle,
	};
	if (_reeltime > 0) {
		DrawGraph(1650, 890, cg[_slotdivine], TRUE);
	}

}