#include "PlayerManager.h"

PlayerManager::PlayerManager() {

}

PlayerManager::~PlayerManager() {

	P_Delete();

}

void PlayerManager::Initialize() {
// プレイヤーマネージャー自体の初期化関数（グローバルでできているので一応作りました）
}

void PlayerManager::Process() {
 // ガチャなどで変動したステータスを変更などプレイヤーのゲーム画面以外での処理を記述（必要に応じて増やす）
}
// 以下のP～～はプレイヤー内の関数を一つ上の階層でつかえるようにしている
void PlayerManager::P_Materialize() {
 
	_pl = new Player();

}

void PlayerManager::P_Delete() {

	delete _pl;

}

void PlayerManager::P_Initialize(int handle, int weapon) {

	_pl->Initialize(handle, weapon);

}

void PlayerManager::P_Process(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot) {
	// 必要とあらば何かしら追加する(プレイヤークラスの関数をまとめるなど)
	_pl->Process(trg, key, rel, campos, camtarget,slot);
}

//void PlayerManager::P_Gravity() {
//	_pl->Gravity();
//}

void PlayerManager::P_AnimProcess() {
	_pl->A_Process();
}

void PlayerManager::P_CalcuProcess() {
	_pl->C_Process();
}

void PlayerManager::P_ActionProcerss(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot)
{
	_pl->ActionProcess(trg, key, rel, campos, camtarget, slot);
}

void PlayerManager::P_Move(int key, VECTOR campos, VECTOR camtarget) {
	_pl->PlayerMove(key, campos, camtarget);
}

void PlayerManager::P_Action(int trg) {
	//_pl->PlayerAction(trg);
}
void PlayerManager::P_Damage(VECTOR pos,int subpoint)
{
	_pl->Damage(pos, subpoint);
}
void PlayerManager::Render() {
	// プレイヤーの描画以外にもプレイヤーに関するデバッグ情報が欲しかったら描画する
	_pl->Render();
}

void PlayerManager::DebugRender() {
	_pl->PlDebug();
}