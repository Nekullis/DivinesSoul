
#include "ApplicationMain.h"
#include "ModeGameClear.h"
#include "ModeTitle.h"

bool ModeClear::Initialize() {
	if (!base::Initialize()) { return false; }
	_cg = gGlobal._RS->mGetGraph()["gameclear"]._handle;
	return true;
}

bool ModeClear::Terminate() {
	base::Terminate();
	return true;
}

bool ModeClear::Process() {
	base::Process();
	std::string bgmName = "BGM_Clear";//�����ʃR�[�h��������
	SoundItemBase* sndItem = gGlobal._sndServer.Get(bgmName);
	sndItem->SetVolume(100);
	//�ǂݍ��݊������Ă��邩�H
	if (sndItem && sndItem->IsLoad()) {
		// �Đ������H
		if (sndItem->IsPlay() == false) {
			// �Đ�����
			sndItem->Play();
		}
	}
	if (gGlobal._gTrg & PAD_INPUT_3) {
		sndItem->Stop();
		SoundItemBase* sndse = gGlobal._sndServer.Get("SE_UI_Decision");
		if (sndse && sndse->IsLoad()) {
			// �Đ������H
			if (sndse->IsPlay() == false) {
				// �Đ�����
				sndse->Play();
			}
		}
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "Title");
	}
	return true;
}

bool ModeClear::Render() {
	base::Render();
	DrawGraph(0, 0, _cg, TRUE);
	return true;
}