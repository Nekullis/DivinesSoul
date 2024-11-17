#include "Effect.h"
Effect* Effect::efInstance = nullptr;
Effect::Effect(std::string handle, float size)
{
	efInstance = this;
	Pos = VGet(0, 0, 0);
	Size = size;
	Dir = VGet(0,0,0);
	effectResourceHandle = LoadEffekseerEffect(handle.c_str(), Size);
	useFlag = true;
	playFlag = false;
	//Effekseerにより再生中のエフェクトを更新する。
	SetPosPlayingEffekseer3DEffect(playEffectHandle, Pos.x, Pos.y, Pos.z);
}

Effect::~Effect()
{
	// エフェクトリソースを削除する。
	DeleteEffekseerEffect(effectResourceHandle);
}
bool Effect::Play()
{
	if (useFlag)
	{
		//エフェクトを再生する
		playEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
	}
	if (playEffectHandle != -1)
	{
		//再生中ならtrueに
		playFlag = true;
	}
	return true;
	
}
bool Effect::Stop()
{
	StopEffekseer3DEffect(playEffectHandle);
	return true;
}
bool Effect::Process()
{
	//Effekseerにより再生中のエフェクトを更新する。
	SetPosPlayingEffekseer3DEffect(playEffectHandle, Pos.x, Pos.y, Pos.z);
	//角度を変更する
	SetRotationPlayingEffekseer3DEffect(playEffectHandle, Dir.x, Dir.y, Dir.z);
	////再生が終わったらフラグをfalseに
	//if (IsEffekseer3DEffectPlaying(playEffectHandle) == 0)
	//{ 
	//	//useFlag = false; 
	//}
	return true;
}

bool Effect::Update()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	//マネージャーを通し複数使う場合はUpdateEffekseer3Dはマネージャークラスに置く
	UpdateEffekseer3D();
	return true;
}

bool Effect::Draw()
{
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
	return true;
}

bool Effect::Debug()
{
	DrawFormatString(100, 0, GetColor(255, 0, 0), "play=%d", IsEffekseer3DEffectPlaying(playEffectHandle));
	return true;
}