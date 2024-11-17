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
		// Ä¶’†‚©H
		if (sndItem->IsPlay() == false) {
			// Ä¶‚·‚é
			sndItem->Play();
		}
	}
	if (gGlobal._gTrg & PAD_INPUT_3) {
		sndItem->Stop();
		SoundItemBase* sndse = gGlobal._sndServer.Get("SE_UI_Decision");
		if (sndse && sndse->IsLoad()) {
			// Ä¶’†‚©H
			if (sndse->IsPlay() == false) {
				// Ä¶‚·‚é
				sndse->Play();
			}
		}
		// ‚±‚Ìƒ‚[ƒh‚ðíœ—\–ñ
		ModeServer::GetInstance()->Del(this);
		// ŽŸ‚Ìƒ‚[ƒh‚ð“o˜^
		ModeServer::GetInstance()->Add(new ModeLoad(), 1, "load");
	}
	return true;
}

bool ModeTitle::Render() {
	base::Render();
	DrawGraph(0, 0, _cg, TRUE);
	return true;
}