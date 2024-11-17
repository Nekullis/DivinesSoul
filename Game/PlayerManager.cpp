#include "PlayerManager.h"

PlayerManager::PlayerManager() {

}

PlayerManager::~PlayerManager() {

	P_Delete();

}

void PlayerManager::Initialize() {
// �v���C���[�}�l�[�W���[���̂̏������֐��i�O���[�o���łł��Ă���̂ňꉞ���܂����j
}

void PlayerManager::Process() {
 // �K�`���Ȃǂŕϓ������X�e�[�^�X��ύX�Ȃǃv���C���[�̃Q�[����ʈȊO�ł̏������L�q�i�K�v�ɉ����đ��₷�j
}
// �ȉ���P�`�`�̓v���C���[���̊֐������̊K�w�ł�����悤�ɂ��Ă���
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
	// �K�v�Ƃ���Ή�������ǉ�����(�v���C���[�N���X�̊֐����܂Ƃ߂�Ȃ�)
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
	// �v���C���[�̕`��ȊO�ɂ��v���C���[�Ɋւ���f�o�b�O��񂪗~����������`�悷��
	_pl->Render();
}

void PlayerManager::DebugRender() {
	_pl->PlDebug();
}