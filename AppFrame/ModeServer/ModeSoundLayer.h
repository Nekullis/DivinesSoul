//// Appframe側のModeSoundLayer,SoundServer, SoundItemは一応ひな形として置いている。
//// 全然こちらを読み込めるようにして使ってもいいが、実際のソリューション側に今は作る。
//
//#pragma once
//#include "ModeBase.h"
//#include "../Sound/SoundItem.h"
//#include <string>
//
//// モード
//class ModeSoundLayer : public ModeBase
//{
//	typedef ModeBase base;
//public:
//	virtual bool Initialize();
//	virtual bool Terminate();
//	virtual bool Process();
//	virtual bool Render();
//
//private:
//	void PrintSoundItem(int x, int y, std::string name, SoundItemBase* snd);
//
//protected:
//
//
//	int		_loadTimeMs;		// ロード登録にかかった時間
//	int		_asyncLoadBaseTimeMs;	// 非同期ロードにかかった時間(計算用)
//	int		_asyncLoadTimeMs;		// 非同期ロードにかかった時間
//
//	std::string		_msg;			// 処理メッセージ表示用
//
//	int		_listCur;			// 選択リストカーソル位置
//	int		_listViewStart, _listViewNum;	// 選択リスト表示関連
//
//};
//
