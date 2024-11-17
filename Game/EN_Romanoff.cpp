#include "EN_Romanoff.h"
#include "GameEvent.h"
EN_Romanoff* EN_Romanoff::_bossInstance = nullptr;
EN_Romanoff::EN_Romanoff(int model, int weapon, VECTOR vpos, VECTOR vdir) :base(model, weapon, vpos, vdir)
{
	_bossInstance = this;
	//初期値を設定
	MV1SetPosition(_model, _vPos);
	//体力
	_hp = 4000;
	//攻撃力
	_ap = 10;
	//死んでいるか
	_die = false;
	//判定カプセル内の要素を初期化
	//カプセルの半径
	_radius = 45;
	//線分の長さ
	_lineSeg = 191;
	//カプセルの位置
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//アタッチするアニメーション番号の初期化
	_attachIndex = MV1AttachAnim(_model, 6, -1, FALSE);
	mName = "romanoff_stand";
	//総再生時間の初期化
	_totalTime = gGlobal._RS->mGetAttach()[mName]._attach_time;
	//武器サイズ
	_wSize = 50;
	_damageCnt = 5;
	//ステータスを未発見に
	ChangeStatus(STATUS::NODISCOVERY);
	_type = ENEMYTYPE::ROMANOFF;
}

EN_Romanoff::~EN_Romanoff()
{
	MV1DeleteModel(_model);
	MV1DetachAnim(_model, _attachIndex);
}

void EN_Romanoff::ChangeStatus(STATUS en_status)
{
	//ステータスの代入
	_data.status = en_status;
	//カウントリセット
	_actionCnt = 0;
	_timeCnt = 0;
	switch (_data.status)
	{
	case STATUS::DAMAGE:
		_data.motionTotalFrame = 42;
	}
}

bool EN_Romanoff::A_Process()
{
	//1フレーム前のステータスと違うのなら処理
	if (_oldAnimation != _animation)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(_model, _attachIndex);
		//ステータスによってアタッチするアニメーションの変更
		switch (_animation)
		{
		//待機
		case ANIMATION::WAIT:
			//キーを一致させるために文字列を代入
			mName = "romanoff_stand";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//ダメージ
		case ANIMATION::DAMAGE:
			//キーを一致させるために文字列を代入
			mName = "romanoff_damage";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//攻撃
		case ANIMATION::FIRSTATTACK:
			//キーを一致させるために文字列を代入
			mName = "romanoff_attack1";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		case ANIMATION::SECONDATTACK:
			//キーを一致させるために文字列を代入
			mName = "romanoff_attack2";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//走行
		case ANIMATION::RUN:
			//キーを一致させるために文字列を代入
			mName = "romanoff_run";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//走行
		case ANIMATION::DIE:
			//キーを一致させるために文字列を代入
			mName = "romanoff_die";
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
		if (_die)
		{
			_playTime = _totalTime;
			float rate = 1;
			for (rate; rate >= 0; rate -= 0.05)
			{
				MV1SetOpacityRate(_model, rate);
			}
			if (rate < 0)
			{
				Delete();
				_deleteFlag = true;
			}

		}
		else { _playTime = 0; }
	}
	//一時的なステータスの変更
	_oldAnimation = _animation;
	return true;
}

void EN_Romanoff::DiscoveryProcess(VECTOR pl_pos)
{
	float dis_discovery = 2000.0f;
	_animation = ANIMATION::WAIT;
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(_vPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	if (len <= dis_discovery)
	{
		ChangeStatus(STATUS::WAIT);
		GameEvent::GetInstance()->SetEvent(1);
	}

}

void EN_Romanoff::WaitProcess()
{
	int action_num = rand() % 10;
	_animation = ANIMATION::WAIT;
	_actionCnt++;
	if (_actionCnt >= 110)
	{
		if (action_num < 7)
		{
			//ステータスを走行に
			ChangeStatus(STATUS::RUN);
		}
		else if (action_num >= 7)
		{
			//ステータスを突撃に
			ChangeStatus(STATUS::ASSAULT);
		}
		
	}
}

void EN_Romanoff::Move(float speed, VECTOR pl_pos)
{
	//ローカル変数を設定
	VECTOR vec_pl_pos = VGet(0, 0, 0);
	VECTOR vector = VGet(0, 0, 0);
	//自身の位置とプレイヤーのベクトルを作成
	vec_pl_pos = VSub(pl_pos, _vPos);
	//ベクトルを正規化
	VECTOR vunit = VNorm(vec_pl_pos);
	//正規化したベクトルを
	vector = vunit;
	//向きを設定するために代入
	_vDir = vec_pl_pos;
	//方向ベクトルにスピードをかけたものを移動ベクトルとする
	_vMove = VScale(vector, speed);
	//位置ベクトルに移動ベクトルを加算
	_vPos = VAdd(_vPos, _vMove);
}

void EN_Romanoff::RunProcess(VECTOR pl_pos)
{
	//アニメーションを走行に
	_animation = ANIMATION::RUN;
	//スピードを設定
	float speed = 8.5;
	//カウント加算
	_actionCnt++;
	//移動処理
	Move(speed, pl_pos);
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(_vPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	//カウントが規定数、もしくはベクトルサイズが規定以内
	if (len <= 100)
	{
		//ステータスを攻撃に変更
		ChangeStatus(STATUS::ATTACK);
	}
	else if (_actionCnt >= 360 && len >= 100)
	{
		//ステータスを攻撃に変更
		ChangeStatus(STATUS::ASSAULT);
	}

}

VECTOR EN_Romanoff::AttackPos()
{
	VECTOR vec = { 0 };
	int frame_index = MV1SearchFrame(_model, "Character1_Hips");
	//位置をローカルからグローバルに変換するマトリックスを作成
	MATRIX matrix = MV1GetFrameLocalWorldMatrix(_model, frame_index);
	vec = VTransform(VGet(0, 0, 0), matrix);
	return VGet(vec.x, 0, vec.z);
}

bool EN_Romanoff::Attack()
{
	if (_actionCnt >= 25 && _actionCnt <= 35 ||
		_actionCnt >= 45 && _actionCnt <= 70)
	{
		return true;
	}
	return false;
}

void EN_Romanoff::AttackProcess()
{
	_actionCnt++;
	std::string se_voice = "VO_Ro_Attack";
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(se_voice);
	if (Attack())
	{
		//_vPos = AttackPos();
		_isAttack = true;
	}
	else
	{
		_isAttack = false;
	}
	if (_actionCnt >= 0 && _actionCnt < 40)
	{
		_animation = ANIMATION::FIRSTATTACK;
		if (snditem_voice && snditem_voice->IsLoad())
		{
			// 再生中か？
			if (snditem_voice->IsPlay() == false)
			{
				// 再生する
				snditem_voice->Play();
			}
		}
	}
	else if (_actionCnt >= 40 && _actionCnt < 112)
	{
		_animation = ANIMATION::SECONDATTACK;
	}
	else if (_actionCnt == 112)
	{
		ChangeStatus(STATUS::WAIT);
	}
}

bool EN_Romanoff::Assult()
{
	if (_actionCnt >= 85 && _actionCnt <= 95)
	{
		return true;
	}
	return false;
}

void EN_Romanoff::AssaultProcess(VECTOR pl_pos)
{
	//スピードを設定
	float speed = 30.0;
	float finish_frame = 125;
	float assult_start_frame = 40;
	float dis_assult = 100;
	std::string voice[3] =
	{
		"VO_Ro_Divine1",
		"VO_Ro_DIvine2",
		"VO_Ro_DIvine3"
	};
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(voice[rand() % 3]);
	//カウント加算
	_actionCnt++;
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(_vPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	if (_actionCnt == 1)
	{
		snditem_voice->Play();
	}
	if (_actionCnt < assult_start_frame)
	{
		//アニメーションを走行に
		Move(speed, pl_pos);
		_animation = ANIMATION::RUN;
	}
	else if (_actionCnt == assult_start_frame)
	{
		_animation = ANIMATION::FIRSTATTACK;
	}
	else if (_actionCnt == finish_frame)
	{
		ChangeStatus(STATUS::WAIT);
	}
	
	if (Assult())
	{
		//_vPos = AttackPos();
		_isAttack = true;
	}
	if (_actionCnt < 85 || _actionCnt > 95)
	{
		_isAttack = false;
	}

}


void EN_Romanoff::DieProcess()
{
	std::string se_voice = "VO_Ro_Blow";
	SoundItemBase* snditem_voice = gGlobal._sndServer.Get(se_voice);
	_animation = ANIMATION::DIE;
	if (snditem_voice && snditem_voice->IsLoad())
	{
		// 再生中か？
		if (snditem_voice->IsPlay() == false)
		{
			// 再生する
			snditem_voice->Play();
		}
	}
	_die = true;
}

void EN_Romanoff::DamageProcess()
{
	_actionCnt++;
	_animation = ANIMATION::DAMAGE;
	//カウントが総フレームに達した
	if (_actionCnt >= _data.motionTotalFrame)
	{
		//ステータスを走行に
		ChangeStatus(STATUS::WAIT);
	}

}

bool EN_Romanoff::Damage(VECTOR pl_pos, int subpoint, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal._sndServer.Get("SE_Damage");
	snditem_se->SetVolume(200);
	if (snditem_se && snditem_se->IsLoad())
	{
		// 再生中か？
		if (snditem_se->IsPlay() == false)
		{
			// 再生する
			snditem_se->Play();
		}
	}
	_damageCnt--;
	VECTOR v = VSub(_vPos, pl_pos);
	_hp = _hp - subpoint;
	if (_hp <= 0)
	{
		v = VScale(VNorm(v), 100);
		//ステータスを死亡に
		ChangeStatus(STATUS::DIE);
	}
	else if (_hp > 0)
	{
		v = VScale(VNorm(v), 50);
		//ステータスをダメージに
		if (_damageCnt <= 0)
		{
			ChangeStatus(STATUS::DAMAGE);
			_damageCnt = 5;
		}
	}
	_vPos = VAdd(_vPos, v);
	nextFrame = nextframe;
	_noDamage = true;
	return true;
}

bool EN_Romanoff::Suction(VECTOR pl_pos, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal._sndServer.Get("SE_Damage");
	if (snditem_se && snditem_se->IsLoad())
	{
		// 再生中か？
		if (snditem_se->IsPlay() == false)
		{
			// 再生する
			snditem_se->Play();
		}
	}
	ChangeStatus(STATUS::DAMAGE);
	VECTOR v = VSub(_vPos, pl_pos);
	v = VScale(VNorm(v), -5);
	_vPos = VAdd(_vPos, v);
	nextFrame = nextframe;
	_noDamage = true;
	return true;
}

void EN_Romanoff::SetWeapon()
{
	//プレイヤーのモデルから武器を装備するフレームを探す
	int frame_index = MV1SearchFrame(_model, "joint_axe");
	//位置をローカルからグローバルに変換するマトリックスを作成
	MATRIX weapon_matrix = MV1GetFrameLocalWorldMatrix(_model, frame_index);
	MATRIX weapon_dir_matrix = MGetRotY(1.75);
	weapon_matrix = MMult(weapon_dir_matrix,weapon_matrix);
	//武器位置の設定
	_wPos[0] = VTransform(VGet(0, 0, 0), weapon_matrix);
	_wPos[1] = VTransform(VGet(0, 150, 0), weapon_matrix);
	//武器の位置を手のフレームに設定
	MV1SetMatrix(_wModel, weapon_matrix);
}

void EN_Romanoff::Invincible(int nextframe)
{
	//無敵時間中のみカウントを増やす
	if (_noDamage) { _invincibleCnt++; }
	//カウントが規定数に達する
	if (_invincibleCnt >= nextframe)
	{
		//無敵フラグをfalseに
		_noDamage = false;
		//カウントリセット
		_invincibleCnt = 0;
	}
}

bool EN_Romanoff::C_Process(VECTOR pl_pos)
{
	_status = _data.status;
	//カウントの加算
	_timeCnt++;
	//当たり判定カプセルの位置を変更
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//状態によって処理を変更
	switch (_status)
	{
	case STATUS::NODISCOVERY:
		DiscoveryProcess(pl_pos);
		break;
	//待機
	case STATUS::WAIT:
		WaitProcess();
		break;
	//走行
	case STATUS::RUN:
		RunProcess(pl_pos);
		break;
	//ダメージ
	case STATUS::DAMAGE:
		DamageProcess();
		break;
	//攻撃
	case STATUS::ATTACK:
		AttackProcess();
		break;
	//突撃
	case STATUS::ASSAULT:
		AssaultProcess(pl_pos);
		break;
	//死亡
	case STATUS::DIE:
		DieProcess();
		break;
	}
	//埋まらないように位置を調整
	if (_vPos.y <= 0|| _vPos.y >= 0)
	{
		_vPos.y = 0;
	}
	Invincible(nextFrame);
	SetWeapon();
	//角度を求めるのだが座標系が違うので変更
	float angle = atan2(-_vDir.x, -_vDir.z);
	//モデルの向きを設定
	MV1SetRotationXYZ(_model, VGet(0, angle, 0));
	MV1SetPosition(_model, _vPos);
	return true;
}

bool EN_Romanoff::Process(VECTOR pl_pos)
{
	C_Process(pl_pos);
	A_Process();
	return true;
}

bool EN_Romanoff::Render()
{
	MV1SetAttachAnimTime(_model, _attachIndex, _playTime);
	MV1DrawModel(_model);
	MV1DrawModel(_wModel);
	return true;
}

bool EN_Romanoff::Debug()
{
	return true;
}

bool EN_Romanoff::Delete()
{
	return true;
}








