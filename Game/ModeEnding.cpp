#include "ModeEnding.h"
#include "ModeGameClear.h"
#include "ApplicationGlobal.h"
bool ModeEnding::Initialize()
{
    _handleMovie = LoadGraph("res/Movie/Ending.mp4");
    return true;
}

bool ModeEnding::Terminate()
{
    DeleteGraph(_handleMovie);
    return true;
}

bool ModeEnding::Process()
{
    //再生されていなければ動画を再生する
    if (GetMovieStateToGraph(_handleMovie) == 0 && TellMovieToGraph(_handleMovie) == 0)
    {
        PlayMovieToGraph(_handleMovie);
        ChangeMovieVolumeToGraph(150, _handleMovie);
    }
    if (GetMovieStateToGraph(_handleMovie) == 0)
    {
        // このモードを削除予約
        ModeServer::GetInstance()->Del(this);
        // 次のモードを登録
        ModeServer::GetInstance()->Add(new ModeClear(), 1, "clear");
    }
    if (gGlobal._gTrg & PAD_INPUT_3)
    {
        //ボタンを押すとポーズ、再生中ではなくなる
        PauseMovieToGraph(_handleMovie);
    }
    return true;
}

bool ModeEnding::Render()
{
    DrawGraph(0, 0, _handleMovie, FALSE);
    return true;
}
