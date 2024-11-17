
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
	std::string bgmName = "BGM_Clear";//←識別コードをここに
	SoundItemBase* sndItem = gGlobal._sndServer.Get(bgmName);
	sndItem->SetVolume(100);
	//読み込み完了しているか？
	if (sndItem && sndItem->IsLoad()) {
		// 再生中か？
		if (sndItem->IsPlay() == false) {
			// 再生する
			sndItem->Play();
		}
	}
	if (gGlobal._gTrg & PAD_INPUT_3) {
		sndItem->Stop();
		SoundItemBase* sndse = gGlobal._sndServer.Get("SE_UI_Decision");
		if (sndse && sndse->IsLoad()) {
			// 再生中か？
			if (sndse->IsPlay() == false) {
				// 再生する
				sndse->Play();
			}
		}
		// このモードを削除予約
		ModeServer::GetInstance()->Del(this);
		// 次のモードを登録
		ModeServer::GetInstance()->Add(new ModeTitle(), 1, "Title");
	}
	return true;
}

bool ModeClear::Render() {
	base::Render();
	DrawGraph(0, 0, _cg, TRUE);
	return true;
}