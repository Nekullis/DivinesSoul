#pragma once
#include "ApplicationMain.h"
#include "ModeTitle.h"
#include "ModeLoad.h"
#include "ModeFade.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }
	_cg = gGlobal._RS->mGetGraph()["title"]._handle;
	return true;
}

bool ModeTitle::Terminate() {
	base::Terminate();
	return true;
}

bool ModeTitle::Process() {
	base::Process();
	std::string bgmName = "BGM_Title";
	SoundItemBase* sndItem = gGlobal._sndServer.Get(bgmName);
	sndItem->SetVolume(100);
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
		ModeServer::GetInstance()->Add(new ModeLoad(), 1, "load");
	}
	return true;
}

bool ModeTitle::Render() {
	base::Render();
	DrawGraph(0, 0, _cg, TRUE);
	return true;
}