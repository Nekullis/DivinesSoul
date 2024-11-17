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
	//Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	SetPosPlayingEffekseer3DEffect(playEffectHandle, Pos.x, Pos.y, Pos.z);
}

Effect::~Effect()
{
	// �G�t�F�N�g���\�[�X���폜����B
	DeleteEffekseerEffect(effectResourceHandle);
}
bool Effect::Play()
{
	if (useFlag)
	{
		//�G�t�F�N�g���Đ�����
		playEffectHandle = PlayEffekseer3DEffect(effectResourceHandle);
	}
	if (playEffectHandle != -1)
	{
		//�Đ����Ȃ�true��
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
	//Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	SetPosPlayingEffekseer3DEffect(playEffectHandle, Pos.x, Pos.y, Pos.z);
	//�p�x��ύX����
	SetRotationPlayingEffekseer3DEffect(playEffectHandle, Dir.x, Dir.y, Dir.z);
	////�Đ����I�������t���O��false��
	//if (IsEffekseer3DEffectPlaying(playEffectHandle) == 0)
	//{ 
	//	//useFlag = false; 
	//}
	return true;
}

bool Effect::Update()
{
	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();
	//�}�l�[�W���[��ʂ������g���ꍇ��UpdateEffekseer3D�̓}�l�[�W���[�N���X�ɒu��
	UpdateEffekseer3D();
	return true;
}

bool Effect::Draw()
{
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
	return true;
}

bool Effect::Debug()
{
	DrawFormatString(100, 0, GetColor(255, 0, 0), "play=%d", IsEffekseer3DEffectPlaying(playEffectHandle));
	return true;
}