#include "SoundItem.h"
#include "ModeSound.h"
/*
サウンド関係は基本ここにデータを読み込む
サウンドデータはresフォルダにbgm、se、voiceの三種類に分けてファイリング
例
BGM		gGlobal._sndServer.Add("BGM_01", new SoundItemBGM("res/bgm/maou_bgm_fantasy01.mp3"));
SE		gGlobal._sndServer.Add("SE_01", new SoundItemSE("res/se/tm2_bom005.wav"));
VOICE	gGlobal._sndServer.Add("VOICE_01", new SoundItemVOICE("res/voice/「あとちょっとだったね」.mp3"));
*/
//モードの登録

bool ModeSound::Initialize() {
	if (!base::Initialize()) { return false; }

//	 非同期読み込み設定
	SetUseASyncLoadFlag(TRUE);
//	 音データファイルを読み込む
	//BGM
	gGlobal._sndServer.Add("BGM_Title",		 new SoundItemBGM("res/Sound/BGM/Title.mp3"));
	gGlobal._sndServer.Add("BGM_Clear",		 new SoundItemBGM("res/Sound/BGM/Clear.mp3"));
	gGlobal._sndServer.Add("BGM_GameOver",	 new SoundItemBGM("res/Sound/BGM/GameOver.mp3"));
	gGlobal._sndServer.Add("BGM_Quest01",	 new SoundItemBGM("res/Sound/BGM/Quest01.mp3"));
	gGlobal._sndServer.Add("BGM_Quest02",	 new SoundItemBGM("res/Sound/BGM/Quest02.mp3"));
	gGlobal._sndServer.Add("BGM_Quest03",	 new SoundItemBGM("res/Sound/BGM/Quest03.mp3"));
	gGlobal._sndServer.Add("BGM_Boss",		 new SoundItemBGM("res/Sound/BGM/Boss.mp3"));
	gGlobal._sndServer.Add("BGM_RastBoss",	 new SoundItemBGM("res/Sound/BGM/RastBoss.mp3"));
	//SE
	gGlobal._sndServer.Add("SE_Attack01",	 new SoundItemSE("res/Sound/SE/SE_Attack01.mp3"));
	gGlobal._sndServer.Add("SE_Attack02",	 new SoundItemSE("res/Sound/SE/SE_Attack02.mp3"));
	gGlobal._sndServer.Add("SE_Attack03",	 new SoundItemSE("res/Sound/SE/SE_Attack03.mp3"));
	gGlobal._sndServer.Add("SE_Run",		 new SoundItemSE("res/Sound/SE/SE_Run.mp3"));
	gGlobal._sndServer.Add("SE_Divine",		 new SoundItemSE("res/Sound/SE/SE_Divine.mp3"));
	gGlobal._sndServer.Add("SE_Laser",		 new SoundItemSE("res/Sound/SE/SE_Beam.mp3"));
	gGlobal._sndServer.Add("SE_Skill",		 new SoundItemSE("res/Sound/SE/SE_Divine.mp3"));
	gGlobal._sndServer.Add("SE_Explosion",	 new SoundItemSE("res/Sound/SE/SE_Explosion.mp3"));
	gGlobal._sndServer.Add("SE_Hammer",		 new SoundItemSE("res/Sound/SE/SE_hammer.mp3"));
	gGlobal._sndServer.Add("SE_Slash",		 new SoundItemSE("res/Sound/SE/SE_Slash.mp3"));
	gGlobal._sndServer.Add("SE_Breath",		 new SoundItemSE("res/Sound/SE/SE_Breath.mp3"));
	gGlobal._sndServer.Add("SE_Circle",		 new SoundItemSE("res/Sound/SE/SE_Circle.mp3"));
	gGlobal._sndServer.Add("SE_Sonic",		 new SoundItemSE("res/Sound/SE/SE_Sonic.mp3"));
	gGlobal._sndServer.Add("SE_DashAttack",  new SoundItemSE("res/Sound/SE/SE_DashAttack.mp3"));
	gGlobal._sndServer.Add("SE_Vacuum",		 new SoundItemSE("res/Sound/SE/SE_Vacuum.mp3"));
	gGlobal._sndServer.Add("SE_UI_Decision", new SoundItemSE("res/Sound/SE/SE_UI_Decision.mp3"));
	gGlobal._sndServer.Add("SE_Damage",		 new SoundItemSE("res/Sound/SE/SE_Damage.mp3"));
	gGlobal._sndServer.Add("SE_Damage_Crab", new SoundItemSE("res/Sound/SE/SE_Damage_Crab.mp3"));
	gGlobal._sndServer.Add("SE_Slot_Start",  new SoundItemSE("res/Sound/SE/SE_Slot_Start.mp3"));
	gGlobal._sndServer.Add("SE_Slot_Finish", new SoundItemSE("res/Sound/SE/SE_Slot_Finish.mp3"));
	gGlobal._sndServer.Add("SE_Page",		 new SoundItemSE("res/Sound/SE/SE_Page.mp3"));
	//VOICE
	gGlobal._sndServer.Add("VO_Fe_Attack01", new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Attack01_B.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Attack02", new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Attack02_B.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Attack03", new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Attack03.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Slash",	 new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Slash.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Explosion",new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Explosion.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Breath",	 new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Breath.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Circle",	 new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Circle.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Laser",	 new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Laser.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Damage1",	 new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Damage1.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Damage2",	 new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Damage2.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Damage3",  new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Damage3.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Blow1",	 new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Blow1.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Blow2",	 new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Blow2.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Avoid",	 new SoundItemVOICE("res/Sound/VOICE/Feld_Action/Voice_Feld_Avoid.mp3"));
	gGlobal._sndServer.Add("VO_Ca_Explosion",new SoundItemVOICE("res/Sound/VOICE/Call/Voice_Call_Explosion.mp3"));
	gGlobal._sndServer.Add("VO_Ca_Circle",	 new SoundItemVOICE("res/Sound/VOICE/Call/Voice_Call_Circle.mp3"));
	gGlobal._sndServer.Add("VO_Ca_Slash",	 new SoundItemVOICE("res/Sound/VOICE/Call/Voice_Call_Slash.mp3"));
	gGlobal._sndServer.Add("VO_Ca_Breath",	 new SoundItemVOICE("res/Sound/VOICE/Call/Voice_Call_Breath.mp3"));
	gGlobal._sndServer.Add("VO_Ca_Laser",	 new SoundItemVOICE("res/Sound/VOICE/Call/Voice_Call_Laser.mp3"));
	gGlobal._sndServer.Add("VO_Ca_Dash",	 new SoundItemVOICE("res/Sound/VOICE/Call/Voice_Call_DashAttack.mp3"));
	gGlobal._sndServer.Add("VO_Ca_Sonic",	 new SoundItemVOICE("res/Sound/VOICE/Call/Voice_Call_Sonic.mp3"));
	gGlobal._sndServer.Add("VO_Ca_Vacuum",   new SoundItemVOICE("res/Sound/VOICE/Call/Voice_Call_Vacuum.mp3"));
	gGlobal._sndServer.Add("VO_Ro_Attack",	 new SoundItemVOICE("res/Sound/VOICE/Romanoff_Action/Voice_Romanoff_Attack.mp3"));
	gGlobal._sndServer.Add("VO_Ro_Divine1",	 new SoundItemVOICE("res/Sound/VOICE/Romanoff_Action/Voice_Romanoff_Divine1.mp3"));
	gGlobal._sndServer.Add("VO_Ro_DIvine2",	 new SoundItemVOICE("res/Sound/VOICE/Romanoff_Action/Voice_Romanoff_DIvine2.mp3"));
	gGlobal._sndServer.Add("VO_Ro_DIvine3",	 new SoundItemVOICE("res/Sound/VOICE/Romanoff_Action/Voice_Romanoff_DIvine3.mp3"));
	gGlobal._sndServer.Add("VO_Ro_Blow",	 new SoundItemVOICE("res/Sound/VOICE/Romanoff_Action/Voice_Romanoff_Blow.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_01", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_01.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_02", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_02.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_03", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_03.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_04", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_04.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_05", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_05.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_06", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_06.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_07", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_07.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_08", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_08.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_09", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_09.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_10", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_10.mp3"));
	gGlobal._sndServer.Add("VO_Fe_Quest_11", new SoundItemVOICE("res/Sound/VOICE/Feld_Quest/Voice_Feld_Quest_11.mp3"));
	gGlobal._sndServer.Add("VO_Ro_Quest_01", new SoundItemVOICE("res/Sound/VOICE/Romanoff_Quest/Voice_Romanoff_Quest_01.mp3"));
	gGlobal._sndServer.Add("VO_Ro_Quest_02", new SoundItemVOICE("res/Sound/VOICE/Romanoff_Quest/Voice_Romanoff_Quest_02.mp3"));
	gGlobal._sndServer.Add("VO_Ro_Quest_03", new SoundItemVOICE("res/Sound/VOICE/Romanoff_Quest/Voice_Romanoff_Quest_03.mp3"));
	gGlobal._sndServer.Add("VO_Ro_Quest_04", new SoundItemVOICE("res/Sound/VOICE/Romanoff_Quest/Voice_Romanoff_Quest_04.mp3"));
	gGlobal._sndServer.Add("VO_RO_Quest_05", new SoundItemVOICE("res/Sound/VOICE/Romanoff_Quest/Voice_Romanoff_Quest_05.mp3"));
	gGlobal._sndServer.Add("VO_RO_Quest_06", new SoundItemVOICE("res/Sound/VOICE/Romanoff_Quest/Voice_Romanoff_Quest_06.mp3"));
	gGlobal._sndServer.Add("VO_RO_Quest_07", new SoundItemVOICE("res/Sound/VOICE/Romanoff_Quest/Voice_Romanoff_Quest_07.mp3"));


//	 同期読み込み設定
	SetUseASyncLoadFlag(FALSE);
	return true;
}

bool ModeSound::Terminate() {
	base::Terminate();
	return true;
}

bool ModeSound::Process() {
	base::Process();
	// サウンドサーバ更新
	gGlobal._sndServer.Update();
	return true;
}

bool ModeSound::Render()
{
	return false;
}
