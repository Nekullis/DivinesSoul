
#include "ApplicationMain.h"
#include "ModeGameover.h"
#include "ModeGame.h"

bool ModeGameover::Initialize() {
	if (!base::Initialize()) { return false; }
	_cg[0] = gGlobal._RS->mGetGraph()["gameover_continue"]._handle;
	_cg[1] = gGlobal._RS->mGetGraph()["gameover_reset"]._handle;
	_selection = 0;
	return true;
}

bool ModeGameover::Terminate() {
	base::Terminate();
	return true;
}

bool ModeGameover::Process() {
	base::Process();
	std::string bgmName = "BGM_GameOver";//←識別コードをここに
	SoundItemBase* sndItem = gGlobal._sndServer.Get(bgmName);
	sndItem->SetVolume(100);
	// 読み込み完了しているか？
	if (sndItem && sndItem->IsLoad()) {
		// 再生中か？
		if (sndItem->IsPlay() == false) {
			// 再生する
			sndItem->Play();
		}
	}
	if (gGlobal._gTrg & PAD_INPUT_UP){_selection = 0;}
	if (gGlobal._gTrg & PAD_INPUT_DOWN){_selection = 1;}
	if (gGlobal._gTrg & PAD_INPUT_3) {
		sndItem->Stop();
		switch (_selection)
		{
		case 0:
			// このモードを削除予約
			ModeServer::GetInstance()->Del(this);
			// 次のモードを登録
			ModeServer::GetInstance()->Add(new ModeGame(), 1, "game");
			break;
		case 1:
			// このモードを削除予約
			ModeServer::GetInstance()->Del(this);
			// 次のモードを登録
			ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
			break;
		}
		
	}

	return true;
}

bool ModeGameover::Render() {
	base::Render();

	DrawGraph(0, 0, _cg[_selection], TRUE);
	return true;
}