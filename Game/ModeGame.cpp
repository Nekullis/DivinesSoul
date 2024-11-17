#pragma once
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "ModeGameClear.h"
#include "ModeGameover.h"
#include "ModeEnding.h"
#include "ModeFade.h"
// ��������Ă���̂Ō�X�������t�@�C������
// ���[�h�Q�[����W�J������Ɋe�X�e�[�W��W�J����B���[�h�Q�[�����X�e�[�W�Ɠ����Ɏ��s����Ă���ۂ͓�����~�߂Ȃ�
// �|�[�Y�A���U���g�A�G�̓o�ꉉ�o�Ȃǂ����܂�ꍇ�͎~�߂�
//
// �T�E���h�Ɋւ��āA��������p���ăI�u�W�F�N�g�Ǘ��AJson�t�@�C�����p�A�ߋ��̃t�@�C������
// �ǂ����ȃ��m����������o��
// �J�������Q�[�����Ɏ����Ă��Ēǉ�����
// 
//�@�{�^����ŃC�[�W���O���Ă̏���ʒu�ւ̃J�����ړ�
//�@�����蔻�菈��
//

bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }
	//ModeG = gGlobal.stageNum; // �g��Ȃ������B�B�B�F�F�ʂ̃��[�h���ɑI�����ꂽ�X�e�[�W���O���[�o���ɕێ����Ă����ăX�e�[�W�i���o�[���R�s�[����
	gGlobal.stageNum = ApplicationGlobal::stage::stage1;
	_cam = new Camera ();
	//ModeServer::GetInstance()->Add(new ModeFade(1), 10, "fade");
	_gMapEntity = new MapEntity();
	_aCol = new ActionCollision();
	_slot = new SkillSlot();
	gGlobal._PM->P_Materialize();
	_gameUI = new GameUI();
	_event = new GameEvent();
	_system = new GameSystem();
	gGlobal._PM->P_Initialize(gGlobal.mGetModel()["Feld"]._handle, gGlobal.mGetModel()["W_Sword"]._handle);

	return true;
}

bool ModeGame::Terminate() {
	delete _cam;
	gGlobal._PM->P_Delete();
	delete _event;
	delete _gMapEntity;
	delete _gameUI;
	gGlobal.stageNum = ApplicationGlobal::stage::none;
	base::Terminate();
	return true;
}

bool ModeGame::Process() {
	std::string bgmName;
	if (_event->GetEvent() < 1)
	{
		bgmName = "BGM_Quest01";
	}
	else if (_event->GetEvent() >= 1)
	{
		bgmName = "BGM_Boss";
	}
	SoundItemBase* sndItem = gGlobal._sndServer.Get(bgmName);
	sndItem->SetVolume(75);
	 //�ǂݍ��݊������Ă��邩�H
	if (sndItem && sndItem->IsLoad()) {
		// �Đ������H
		if (sndItem->IsPlay() == false) {
			// �Đ�����
			sndItem->Play();
		}
	}
	base::Process();
	_gMapEntity->Process();
	_aCol->Process(gGlobal._PM->P_Get(), _event->GetEnemyManager());
	_cam->CamCollection(gGlobal._PM->P_GetPos());
	_cam->Process(gGlobal._gKey,gGlobal._gSti , gGlobal._gTrg, gGlobal._PM->P_GetMove(), gGlobal._PM->P_GetPos(), gGlobal._PM->P_GetDir());
	gGlobal._PM->P_Process(gGlobal._gTrg, gGlobal._gKey, gGlobal._gRel, _cam->GetVPos(), _cam->GetVTarget(), _slot);
	Effect::GetInstance()->Update();
	_event->Process();
	_system->Process(_event->GetEnemyManager(),_slot,gGlobal._PM->P_GetCommand());
	_slot->Process();
	if (_event->GameClear(EN_Romanoff::GetInstance()))
	{

		sndItem->Stop();
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeEnding(), 1, "Ending");

	}
	if (_event->GameOver())
	{
		sndItem->Stop();
		// ���̃��[�h���폜�\��
		ModeServer::GetInstance()->Del(this);
		// ���̃��[�h��o�^
		ModeServer::GetInstance()->Add(new ModeGameover(), 1, "gameover");
	}
	return true;
}

bool ModeGame::Render() {
	base::Render();
	// 3D��{�ݒ�
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);
	_cam->Render();
	_gMapEntity->Render();
	gGlobal._PM->Render();
	_event->Render();
	_gameUI->Draw(_slot->Getslot());
	_slot->Render();
	return true;
}

void ModeGame::DIRender() {//DebugInfo
	// 0,0,0�𒆐S�ɐ�������
	{
		float linelength = 1000.f;
		VECTOR v = { 0, 0, 0 };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	// �J�����^�[�Q�b�g�𒆐S�ɒZ����������
	{
		float linelength = 10.f;
		VECTOR v = _cam->GetVTarget();
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}

	// �J�������\��
	{
		int x = 0, y = 0, size = 16;
		SetFontSize(size);
		DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _cam->GetVTarget().x, _cam->GetVTarget().y, _cam->GetVTarget().z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _cam->GetVPos().x, _cam->GetVPos().y, _cam->GetVPos().z); y += size;
		float sx = _cam->GetVPos().x - _cam->GetVTarget().x;
		float sz = _cam->GetVPos().z - _cam->GetVTarget().z;
		float length = sqrt(sz * sz + sx * sx);
		float rad = atan2(sz, sx);
		float deg = Math::RadToDeg(rad);
		DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", length, rad, deg); y += size;
	}
	int x = 0, y = 0, size = 16;
	DrawFormatString(x, y, GetColor(255, 0, 0), "  player    = (%f, %f, %f)", gGlobal._PM->P_GetPos().x, gGlobal._PM->P_GetPos().y, gGlobal._PM->P_GetPos().z); y += size;
	DrawFormatString(x, y, GetColor(255, 0, 0), "  camera    = (%f, %f, %f)", _cam->GetVPos().x, _cam->GetVPos().y, _cam->GetVPos().z); y += size;
}
