#include "Player.h"
#include "ApplicationGlobal.h"

Player* Player::_plInstance = nullptr;
Player::Player() {
	_plInstance = this;
	//位置
	_vPos = VGet(0.0f, 0.0f, 0.0f);
	//角度
	_vDir = VGet(0.0f, 1.0f, 0.0f);
	JsonUtility* jUtil;
	jUtil = new JsonUtility();
	nlohmann::json player_pos = jUtil->Import("res/Json/Player_pos.json").at("Player Start");
	for (auto& data : player_pos)
	{
		data.at("translate").at("x").get_to(_vPos.x);
		data.at("translate").at("z").get_to(_vPos.y);
		data.at("translate").at("y").get_to(_vPos.z);
		_vPos.z *= -1.f;				// 座標の変換
		data.at("rotate").at("x").get_to(_vDir.x);
		data.at("rotate").at("z").get_to(_vDir.y);
		data.at("rotate").at("y").get_to(_vDir.z);
		_vDir.x = Math::DegToRad(_vDir.x);	// 回転はdegree→radianに
		_vDir.y = Math::DegToRad(_vDir.y);
		_vDir.z = Math::DegToRad(_vDir.z);
	}
	//移動
	_vMove = VGet(0.0f, 0.0f, 0.0f);
	//カプセルの長さ
	_lineSeg = 170.0f;
	//カプセル半径
	_rCap = 30.0f;
	//カプセル頂点(下)
	_vCapsule[0] = VGet(_vPos.x + 0.0f, _vPos.y + 50.0f, _vPos.z + 0.0f);
	//カプセル頂点(上)
	_vCapsule[1] = VGet(_vPos.x + 0.0f, _vPos.y - 50.0f, _vPos.z + 0.0f);
	//モデル描画
	_model = 0;
	//再生時間の初期化
	_playTime = 0.0f;
	//アタッチするアニメーション番号
	_attachIndex = -1;
	//重力初期化
	_gravity = -15.0f;
	//カウント初期化
	_actionCnt = 0;
	//コンボ
	_comboCnt;
	//モーション番号
	_actionNum = 0;
	//武器番号初期化
	_weaponNum = 0;
	//攻撃中か
	_isAttack = false;
	//無敵中か
	_noDamage = false;
	//スキル発動中か
	_isSkill = false;
	//死んでいるか
	_isDie = false;
	//ゲームオーバーフラグ
	_gameOverFlag = false;
	//最後に押したボタン
	_lastCommand = -1;
	//武器位置
	_wPos[0] = VGet(0, 0, 0);
	_wPos[1] = VGet(0, 0, 0);
	//プレイヤーモーション状態
	_status = ACTION::WAIT;
	_oldAnimation = ANIMATION::WAIT;
	//通常派生攻撃情報
	Player::ATTACKDATA attackData[ATTACKCOUNT] =
	{   //モーション識別,	全体フレーム, 猶予フレーム(開始), 猶予フレーム(終了), モーション変更時間, 攻撃開始時間, 攻撃終了時間, 攻撃判定, 判定範囲, 入力フラグ,  変更フラグ,  派生可能か, 判定までのフレーム
		{Player::ANIMATION::NOATTACK,		 0.0f,  0.0f,  0.0f,  0.0f, 1.0f,  2.0f,{VGet(0,0,0)   ,VGet(0,0,0)},	 0.0f,  true,  false, true ,"",""},
		{Player::ANIMATION::FIRSTATTACK,	65.0f, 15.0f, 60.0f, 40.0f, 25.0f, 35.0f,{VGet(90,150,0),VGet(-60,0,0)}, 50.0f,  false, false, true ,"VO_Fe_Attack01","SE_Attack01"},
		{Player::ANIMATION::SECONDATTACK,	72.0f, 15.0f, 70.0f, 28.0f, 5.0f, 30.0f,{VGet(-60,0,0) ,VGet(60,0,0)},	50.0f,  false, false, true ,"VO_Fe_Attack02","SE_Attack02"},
		{Player::ANIMATION::LASTATTACK,		90.0f, 25.0f, 54.0f,  0.0f,31.0f, 54.0f,{VGet(0,0,0)   ,VGet(0,0,0)},	50.0f,  false, false, false,"VO_Fe_Attack03","SE_Attack03"},
	};
	//コンテナ要素初期化
	//プレイヤー通常攻撃情報
	for (int i = 0; i < ATTACKCOUNT; i++)
	{
		_attackContainer.emplace(i, attackData[i]);
	}
	//武器情報
	//攻撃状態
	AttackMotionChange(0);
	_skill = new Divine();
	//各パラメータを代入
	_hp = 255;
	_ATK = 0;
	_DEF = 0;
	_SPD = 0;
	_pm = new PP::Parameter();
	_pm->TestJsonLoad("res/Json/test.json");
	_ATK = _pm->GetATK();
	_DEF = _pm->GetDEF();
	_SPD = _pm->GetSPD();
	delete _pm;

}

Player::~Player() {
	_pm = new PP::Parameter();
	_pm->TestJsonLoad("res/Json/test.json");
	_pm->SetATK(_ATK);
	_pm->SetDEF(_DEF);
	_pm->SetSPD(_SPD);
	_pm->TestJsonSave("res/Json/test.json");
	delete _pm;
	delete _skill;
	MV1DetachAnim(_model, _attachIndex);
}

void Player::Initialize(int handle, int weapon) {
	// モデルデータのロード（テクスチャも読み込まれる）	
	_model = handle;
	// 3Dモデルの1番目のアニメーションをアタッチする
	_attachIndex = MV1AttachAnim(_model, 0, -1, FALSE);
	// アタッチしたアニメーションの総再生時間を取得する
	_totalTime = gGlobal._RS->mGetAttach()["player_stand"]._attach_time;
	//武器モデルのロード
	_wModel = weapon;
}

void Player::A_Process()
{
	std::string mName;
	//static ANIMATION _old_animation;
	if (_oldAnimation != _animation)
	{
		MV1DetachAnim(_model, _attachIndex);
		switch (_animation)
		{
		case ANIMATION::WAIT:
			// 待機状態のアニメーションをアタッチする
			mName = "player_stand";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::WALK:
			// 走るアニメーションをアタッチする
			mName = "player_run";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::FIRSTATTACK:
			//縦斬りモーションをアタッチする
			mName = "player_attack1";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::SECONDATTACK:
			//横斬りモーションをアタッチする
			mName = "player_attack2";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::LASTATTACK:
			//回転斬りモーションをアタッチする
			mName = "player_attack3";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::SKILL:
			//ディバインスキルを使用するモーションをアタッチする
			mName = "player_skill";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::AVOID:
			//回避モーションをアタッチする
			mName = "player_attack1";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::DAMAGE:
			//ダメージモーションをアタッチする
			mName = "player_damage";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::DIE:
			//死亡モーションをアタッチする
			mName = "player_blow";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		_totalTime = gGlobal._RS->mGetAttach()[mName]._attach_time;
		_playTime = 0.0f;
	}
	// 再生時間を進める
	_playTime += 1.0f;
	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (_playTime >= _totalTime)
	{
		if (_animation==ANIMATION::DIE)
		{
			_playTime = _totalTime;
			_gameOverFlag = true;
		}
		else { _playTime = 0.0f; }
	}
	_oldAnimation = _animation;
}

void Player::AttackMotionChange(int motionId)
{
	//イテレータで対応キーを見つける
	auto itr = _attackContainer.find(motionId);
	if (itr != _attackContainer.end())
	{//対応キーが見つかったら対応要素を代入する
		_attackData[motionId] = itr->second;
		//その際の番号をアニメーションプロセスで使えるよう代入
		if (motionId != 0) { _animation = _attackData[motionId].animation; }
		_actionCnt = 0;
	}
}

bool Player::Attack()
{
	//ステータスが攻撃に関するもの
	if (_animation == ANIMATION::FIRSTATTACK 
		|| _animation == ANIMATION::SECONDATTACK 
		|| _animation == ANIMATION::LASTATTACK)
	{
		//trueを返す
		return true;
	}
	else
	{
		//falseを返す
		return false;
	}
	
}

int Player::SetSpeed()
{
	//スピード
	int speed = 0;
	//攻撃時
	if (Attack() || _isSkill)
	{
		//スピードを0に
		speed = 0.f;
	}
	//ダッシュアタック時
	else if (_skill->GetIsDash())
	{
		//スピードを上昇させる
		speed = 30.f;
	}
	else
	{
		speed = 15;
	}
	return speed;
}

void Player::SetWeapon()
{
	//プレイヤーのモデルから武器を装備するフレームを探す
	int frame_index = MV1SearchFrame(_model, "joint_sword");
	//位置をローカルからグローバルに変換するマトリックスを作成
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(_model, frame_index);
	_wPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	_wPos[1] = VTransform(VGet(0, 100, 0), weapon_matrix);
	//武器の位置を手のフレームに設定
	MV1SetMatrix(_wModel, weapon_matrix);
}

Player::ANIMATION Player::SkillAnimation()
{
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		int cnt = _skill->GetSkill(i).divineCnt;
		if (cnt > 0 && cnt <= 38)
		{
			switch (_skill->GetSkill(i).skillName)
			{
			case Divine::SKILLNAME::BREATH:
			case Divine::SKILLNAME::CIRCLE:
			case Divine::SKILLNAME::EXPLOSION:
			case Divine::SKILLNAME::LASER:
			case Divine::SKILLNAME::SLASH:
			case Divine::SKILLNAME::SONIC:
			case Divine::SKILLNAME::VACUUM:
				_animation = ANIMATION::SKILL;
				break;
			case Divine::SKILLNAME::DASH:
				_animation = ANIMATION::WALK;
				break;
			}
		}

	}
	return _animation;
} 
void Player::SkillVoice()
{
	std::string voice;
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		switch (_skill->GetSkill(i).skillName)
		{
		case Divine::SKILLNAME::BREATH:
			voice = "VO_Fe_Breath";
			break;
		case Divine::SKILLNAME::CIRCLE:
			voice = "VO_Fe_Circle";
			break;
		case Divine::SKILLNAME::EXPLOSION:
			voice = "VO_Fe_Explosion";
			break;
		case Divine::SKILLNAME::LASER:
			voice = "VO_Fe_Laser";
			break;
		case Divine::SKILLNAME::SLASH:
			voice = "VO_Fe_Slash";
			break;
		case Divine::SKILLNAME::DASH:
			voice = "VO_Fe_Avoid";
			break;
		case Divine::SKILLNAME::SONIC:
			voice = "VO_Fe_Slash";
			break;
		case Divine::SKILLNAME::VACUUM:
			voice = "VO_Fe_Attack03";
			break;
		}
		if (_skill->GetSkill(i).divineCnt > 0 && _skill->GetSkill(i).divineCnt < 10)
		{
			SoundItemBase* snditem_voice = gGlobal._sndServer.Get(voice);
			if (snditem_voice && snditem_voice->IsLoad())
			{
				if (!snditem_voice->IsPlay())
				{
					snditem_voice->Play();
				}
			}
		}
	}
}

void Player::PlayerMove(int key, VECTOR campos, VECTOR camtarget)
{
	// キャラ移動(カメラ設定に合わせて)
	// カメラの向いている角度を取得      
	float sx = campos.x - camtarget.x;
	float sz = campos.z - camtarget.z;
	float camrad = atan2(sz, sx);
	// 移動方向を決める
	_vMove = { 0,0,0 };
	//走る速度の設定
	float mvSpeed = SetSpeed();
	//移動方向を決定
	if (key & PAD_INPUT_DOWN) { _vMove.x = 1; }
	if (key & PAD_INPUT_UP) { _vMove.x = -1; }
	if (key & PAD_INPUT_LEFT) { _vMove.z = -1; }
	if (key & PAD_INPUT_RIGHT) { _vMove.z = 1; }
	// vをrad分回転させる
	float length = 0.f;
	if (VSize(_vMove) > 0.f)
	{
		length = mvSpeed;
	}
	float rad = atan2(_vMove.z, _vMove.x);
	_vMove.x = cos(rad + camrad) * length;
	_vMove.z = sin(rad + camrad) * length;
	// vの分移動
	_vPos = VAdd(_vPos, _vMove);
	_vPos.y += _gravity;
	// 移動量をそのままキャラの向きにする
	if (VSize(_vMove) > 0.f)
	{
		// 移動していない時は無視するため
		// プレイヤーのステータスを「WALK」に変更
		_animation = ANIMATION::WALK;
		_vDir = _vMove;
	}
	// プレイヤーのステータスを「WAIT」に変更
	else { _animation = ANIMATION::WAIT; }
	if (_vPos.y <= 0)
	{
		_vPos.y = 0;
	}
	
	VECTOR vRot = { 0,0,0 };
	vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);
	_vDir.y = vRot.y;
	// 位置
	MV1SetPosition(_model, _vPos);
}

void Player::PlayerAttack(int trg)
{
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(_attackData[_actionNum].voiceCode);
	SoundItemBase* snditem_se = gGlobal._sndServer.Get(_attackData[_actionNum].seCode);
	//カウントを増やす
	if (_actionNum != 0) { _actionCnt++; }
	//フレームカウントが入力猶予フレーム内ならば
	if (_actionCnt >= _attackData[_actionNum].pushButtonStartFrame && _actionCnt <= _attackData[_actionNum].pushButtonEndFrame)
	{//ボタン入力フラグをtrueにする
		_attackData[_actionNum].pushFlug = true;
		// 読み込み完了しているか？
		if (snditem_voice && snditem_voice->IsLoad())
		{
			// 再生中か？
			if (!snditem_voice->IsPlay())
			{
				// 再生する
				snditem_voice->Play();
			}
		}
		if (snditem_se && snditem_se->IsLoad())
		{
			// 再生中か？
			if (!snditem_se->IsPlay())
			{
				// 再生する
				snditem_se->Play();
			}
		}
	}
	//通常攻撃ボタンを押した際
	//ダメージ中ではない
	if (trg & PAD_INPUT_4)
	{
		//ボタン入力フラグがtrueの場合
		if (_attackData[_actionNum].pushFlug)
		{//モーション変更フラグをtrueに変更
			_attackData[_actionNum].changeFlug = true;
		}
	}
	//モーション変更フラグがtrue
	if (_attackData[_actionNum].changeFlug)
	{//かつモーションが切り替わるフレームカウントに到達した
		if (_actionCnt >= _attackData[_actionNum].motionChangeStartFrame)
		{
			//かつその攻撃が派生可能ならば
			if (_attackData[_actionNum].isDerivasion)
			{//カウントを増やしてモーション変更
				if (_actionCnt != 0)
				{
					snditem_voice->Stop();
					snditem_se->Stop();
				}
				_actionNum++;
				AttackMotionChange(_actionNum);
			}
		}
	}
	//攻撃時
	if (_actionNum != 0)
	{//カウントが総フレームに到達していない
		if (_actionCnt != _attackData[_actionNum].motionAllFrame)
		{//状態をそのままに
			_status = ACTION::ATTACK;
		}
		if (_actionCnt == 0 || _actionCnt == _attackData[_actionNum].motionAllFrame)
		{
			int frame_index = MV1SearchFrame(_model, "Character1_Hips");
			//位置をローカルからグローバルに変換するマトリックスを作成
			MATRIX matrix = MV1GetFrameLocalWorldMatrix(_model, frame_index);
			VECTOR vec = VTransform(VGet(0, 0, 0), matrix);
			_vPos = VGet(vec.x, 0, vec.z);
		}
	}
	//何も入力せずカウントがトータルフレームに達した
	if (_actionCnt == _attackData[_actionNum].motionAllFrame)
	{//モーションを攻撃していない状態に
		if (_actionCnt != 0)
		{
			snditem_voice->Stop();
			snditem_se->Stop();
		}
		_actionNum = 0;
		AttackMotionChange(_actionNum);
		//カウントもリセット
		_actionCnt = 0;
		_status = ACTION::WAIT;
	}
}



void Player::PlayerSkill(int trg, int key, int rel, SkillSlot* slot,  VECTOR campos, VECTOR camtarget)
{
	std::array<kindDivine, 3> _slot = slot->Getslot();

	if (trg & PAD_INPUT_1)
	{
		_skill->Invocation(_slot[1]);
		_lastCommand = 1;
	}
	if (trg & PAD_INPUT_2)
	{
		_skill->Invocation(_slot[0]);
		_lastCommand = 0;
	}
	if (trg & PAD_INPUT_3)
	{
		_skill->Invocation(_slot[2]);
		_lastCommand = 2;
	}
	// 向きからY軸回転を算出
	VECTOR vRot = { 0,0,0 };
	vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);
	_vDir.y = vRot.y;
	//モデルの回転値をモデルに代入
	MV1SetRotationXYZ(_model, vRot);
	_skill->Process(_vPos, _vDir.y);
	SkillVoice();
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (_skill->GetSkill(i).divineCnt > 0 && _skill->GetSkill(i).divineCnt < 54)
		{
			_status = ACTION::SKILL;
			if (_skill->GetSkill(i).skillName == Divine::SKILLNAME::DASH)
			{
				PlayerMove(key, campos, camtarget);
			}
			_animation = SkillAnimation();
		}
		if (_skill->GetSkill(i).colCnt > 54 && _skill->GetSkill(i).colCnt < 55)
		{
			_status = ACTION::WAIT;
		}
	}
}

void Player::Damage(VECTOR pos, int subpoint)
{
	std::string se_code_damage[3] =
	{
		"VO_Fe_Damage1",
		"VO_Fe_Damage2",
		"VO_Fe_Damage3",
	};
	std::string se_code_die[2] =
	{
		"VO_Fe_Blow1",
		"VO_Fe_Blow2"
	};
	_hp = _hp - subpoint;
	if (_hp <= 0)
	{
		//ステータスを死亡に
		_status = ACTION::DIE;
		_animation = ANIMATION::DIE;
		SoundItemBase* snditem_voice = gGlobal._sndServer.Get(se_code_die[rand() % 2]);
		snditem_voice->SetVolume(255);
		if (snditem_voice && snditem_voice->IsLoad())
		{// 再生中か？
			if (snditem_voice->IsPlay() == false)
			{// 再生する
				snditem_voice->Play();
			}
		}
	}
	if (_hp > 0)
	{
		//ステータスをダメージに
		_status = ACTION::DAMAGE;
		SoundItemBase* snditem_voice = gGlobal._sndServer.Get(se_code_damage[rand() % 3]);
		snditem_voice->SetVolume(255);
		if (snditem_voice && snditem_voice->IsLoad())
		{// 再生中でないなら
			if (snditem_voice->IsPlay() == false)
			{// 再生する
				snditem_voice->Play();
			}
		}
	}
	VECTOR v = VSub(_vPos, pos);
	v = VScale(VNorm(v), 50);
	_vMove = VAdd(_vMove, v);
	_vPos = VAdd(_vPos, v);
	_actionNum = 0;
	AttackMotionChange(_actionNum);
	_skill->Reset();
}

void Player::PlayerDie()
{
	_noDamage = true;
	_isDie = true;
}

void Player::Invincible()
{
	if (!_isDie)
	{
		if (_noDamage)_invincibleCnt++;
		if (_invincibleCnt > 0 && _invincibleCnt <= 42)
		{
			_animation = ANIMATION::DAMAGE;
		}
		if (_invincibleCnt > 42)
		{
			_status = ACTION::WAIT;
		}
		if (_invincibleCnt > 80)
		{
			_noDamage = false;
			_invincibleCnt = 0;
		}
	}
	
}

void Player::ActionProcess(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot)
{
	// 移動方向を決める
	_vMove = { 0,0,0 };
	bool attack = false;
	bool move = false;
	bool skill = false;
	switch (_status)
	{
	case ACTION::WAIT:
		_animation = ANIMATION::WAIT;
		move = true;
		attack = true;
		skill = true;
		break;
	case ACTION::WALK:
		_animation = ANIMATION::WALK;
		move = true;
		attack = true;
		skill = true;
		break;
	case ACTION::ATTACK:
		_animation = _attackData[_actionNum].animation;
		move = false;
		attack = true;
		skill = true;
		break;
	case ACTION::SKILL:
		attack = true;
		move = false;
		skill = true;
		break;
	case ACTION::AVOID:
		_animation = ANIMATION::AVOID;
		attack = false;
		move = false;
		skill = false;
		break;
	case ACTION::DAMAGE:
		attack = false;
		move = false;
		skill = false;
		break;
	case ACTION::DIE:
		_animation = ANIMATION::DIE;
		PlayerDie();
		attack = false;
		move = false;
		skill = false;
		break;
	}
	if (attack)
	{
		PlayerAttack(trg);
	}
	if (move)
	{
		PlayerMove(key, campos, camtarget);
	}
	if (skill)
	{
		PlayerSkill(trg, key, rel, slot, campos, camtarget);
	}
	if (_hp <= 0)
	{
		_status = ACTION::DIE;
		_animation = ANIMATION::DIE;
	}
	Invincible();
	SetWeapon();
}

void Player::C_Process() 
{
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
}

void Player::Process(int trg, int key, int rel, VECTOR campos, VECTOR camtarget, SkillSlot* slot)
{
	A_Process();
	ActionProcess(trg, key, rel, campos, camtarget,slot);
	C_Process();
}

void Player::Render() 
{
	_skill->Render();
	// 再生時間をセットする
	MV1SetAttachAnimTime(_model, _attachIndex, _playTime);
	// モデルを描画する
	MV1DrawModel(_model);
	MV1DrawModel(_wModel);
}


void Player::PlDebug()
{
	clsDx();
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", _invincibleCnt);
	DrawCapsule3D(VAdd(_vCapsule[0], VGet(0, _rCap, 0)), _vCapsule[1], _rCap, 5, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	
	DrawFormatString(0, 100, GetColor(255, 255, 255), "%f,%f,%f", _wPos[0].x, _wPos[0].y, _wPos[0].z);
}