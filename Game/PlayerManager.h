#pragma once
#include "Player.h"
// プレイヤーに関する情報を保持し、それをプレイヤーに適用するクラス（例：冬期制作におけるガチャなど）モードサーバーに登録して不要な時は止めてもいいかも？
// またステージにおけるプレイヤーの呼び出しも行う(ガチャなどの本編外のステータスを加算して呼び出す)

class PlayerManager
{public:
	PlayerManager();
	virtual ~PlayerManager();
	void Initialize();
	void Process();
	void Render(); // プレイヤー描画含む、もしデバッグ情報を描画するのであればまとめる
	void DebugRender();
public:
	//プレイヤークラスから持ってきた処理を階層を上げてマネージャーから直に使えるようにしている
	void P_Materialize(); // ゲーム本編に入ってきたとき、プレイヤーを出現させる・それまでに受け取った数値で初期化
	void P_Delete();
	void P_Initialize(int handle, int weapon);
	void P_Process(int trg, int key, int rel, VECTOR campos, VECTOR camtarget,SkillSlot* slot);
	//void P_Gravity();
	void P_Move(int key, VECTOR campos, VECTOR camtarget);
	void P_Action(int trg);
	void P_AnimProcess();
	void P_CalcuProcess();
	void P_ActionProcerss(int trg, int key, int rel, VECTOR campos, VECTOR camtarget,SkillSlot* slot);
	void P_Damage(VECTOR pos,int subpoint);
	// レンダーは直にマネージャーのレンダーに貼ってます
	//個別にとるか総体でとるかは悩み中
	Player* P_Get() { return _pl; }
	////////////////////////////////////////
	VECTOR P_GetMove() { return _pl->GetMove(); }
	VECTOR P_GetPos() { return _pl->GetPos(); }
	VECTOR P_GetDir() { return _pl->GetDir(); }
	Divine* P_GetSkill() { return _pl->GetDivine(); }
	int P_GetHp() { return _pl->GetHp(); }
	bool P_GetDie() { return _pl->GetGameOver(); }
	int P_GetCommand() { return _pl->GetLastCommand(); }
	void P_SetPos(VECTOR any) { _pl->SetPos(any); }
	void P_SetPos_y(float y) { _pl->SetPos_y(y); }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	Player* _pl;
};

