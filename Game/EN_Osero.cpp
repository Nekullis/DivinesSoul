#include "EN_Osero.h"
EN_Osero::EN_Osero(int model, int weapon, VECTOR vpos, VECTOR vdir) : base(model, weapon, vpos, vdir)
{
	//初期値を設定
	MV1SetPosition(_model, _vPos);
	//体力
	_hp = 80;
	//攻撃力
	_ap = 8;
	//死んでいるか
	_die = false;
	//カプセルの半径
	_radius = 35;
	//線分の長さ
	_lineSeg = 191;
	//カプセルの位置
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//アタッチするアニメーション番号の初期化
	_attachIndex = MV1AttachAnim(_model, 6, -1, FALSE);
	//総再生時間の初期化
	_totalTime = gGlobal._RS->mGetAttach()["osero_stand"]._attach_time;
	//武器サイズ
	_wSize = 50;
	//ステータスを待機状態に
	ChangeStatus(STATUS::WAIT);
	_type = ENEMYTYPE::OSERO;
}
EN_Osero::~EN_Osero()
{
	MV1DeleteModel(_model);
	MV1DetachAnim(_model, _attachIndex);
}
void EN_Osero::ChangeStatus(STATUS en_status)
{
	_actionCnt = 0;
	_timeCnt = 0;
	//ステータスの代入
	_status = en_status;
	//各状態の総モーションフレームと探索範囲の代入
	switch (_status)
	{
	//待機
	case WAIT:
		_data.motionTotalFrame = 0;
		_data._searchArea = 1000;
		break;
	//ダメージ
	case DAMAGE:
		_data.motionTotalFrame = 42;
		_data._searchArea = 0;
		break;
	//警戒
	case CAUTION:
		_data.motionTotalFrame = 0;
		_data._searchArea = 0;
		break;
	//攻撃
	case ATTACK:
		_data.motionTotalFrame = 38;
		_data._searchArea = 200;
		break;
	//走行
	case RUN:
		_data.motionTotalFrame = 31;
		_data._searchArea = 200;
		break;
	}
}



bool EN_Osero::A_Process()
{
	//std::string mName;
	std::string name[2] =
	{
		"osero_walk_left",
		"osero_walk_right",
	};
	//1フレーム前のステータスと違うのなら処理
	if (_oldStatus != _status)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(_model, _attachIndex);
		//ステータスによってアタッチするアニメーションの変更
		switch (_status)
		{
		//待機
		case STATUS::WAIT:
			//キーを一致させるために文字列を代入
			mName = "osero_stand";
			_attachIndex = MV1AttachAnim(_model,gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//ダメージ
		case STATUS::DAMAGE:
			//キーを一致させるために文字列を代入
			mName = "osero_damage";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//警戒
		case STATUS::CAUTION:
			//キーを一致させるために文字列を代入
			mName = name[rand() % 2];
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//攻撃
		case STATUS::ATTACK:
			//キーを一致させるために文字列を代入
			mName = "osero_attack1";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
		//走行
		case STATUS::RUN:
			//キーを一致させるために文字列を代入
			mName = "osero_run";
			_attachIndex = MV1AttachAnim(_model, gGlobal.mGetAttach()[mName]._attach_index, -1, FALSE);
			break;
			//走行
		case STATUS::DIE:
			//キーを一致させるために文字列を代入
			mName = "osero_die";
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
			_status = STATUS::DIE;
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
		//_playTime = 0;
	}
	//一時的なステータスの変更
	_oldStatus = _status;
	return true;
}
void EN_Osero::WaitProcess(VECTOR pl_pos)
{
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(_vPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	//敵からプレイヤーの距離が探索範囲内
	if (len * len <= _data._searchArea * _data._searchArea)
	{
		//ステータスを走行に
		ChangeStatus(STATUS::RUN);
	}
}


void EN_Osero::Move(float speed, VECTOR pl_pos)
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

void EN_Osero::RunProcess(VECTOR pl_pos)
{
	float speed = 10;
	Move(speed, pl_pos);
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(_vPos, pl_pos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	//敵からプレイヤーの距離が探索範囲内
	if (len * len <= _data._searchArea * _data._searchArea)
	{
		//ステータスを警戒に
		ChangeStatus(STATUS::CAUTION);
	}
	if (len >= 2100)
	{
		//ステータスを待機に
		ChangeStatus(STATUS::WAIT);
	}

}
void EN_Osero::CautionProcess(VECTOR pl_pos)
{
	_actionCnt++;
	float attack_frame = 70 * (rand() % 1 + 1);
	if (mName == "osero_walk_left")
	{
		_vPos.x += 0.1;
	}
	if (mName == "osero_walk_right")
	{
		_vPos.x -= 0.1;
	}
	//プレイヤーと敵の位置の差分を出す
	VECTOR v = VSub(pl_pos, _vPos);
	//ベクトルのサイズを計算
	float len = VSize(v);
	//プレイヤーと敵の判定カプセルの
	float add_radius = _data._searchArea + 30;
	MATRIX m = MGetRotY(_vDir.y);
	VECTOR vec = VGet(m.m[2][0], m.m[2][1], m.m[2][2]);
	vec = VScale(vec, -1);
	//プレイヤーが敵の索敵範囲に入った
	if (MathCollision::CollisionPointAndFan(vec, v, 50))
	{
		//カウントが攻撃までのフレームに達した
		if (_actionCnt >= attack_frame)
		{
			//ステータスを攻撃に
			ChangeStatus(STATUS::ATTACK);
		}
	}
	if (len >= 300)
	{
		//ステータスを走行に
		ChangeStatus(STATUS::RUN);
	}
}
void EN_Osero::AttackProcess()
{
	_actionCnt++;
	//攻撃中なのでフラグをtrueに
	_isAttack = true;
	//カウントが総モーションフレームに達した
	if (_actionCnt >= _data.motionTotalFrame)
	{
		//攻撃が終わったのでフラグをfalseに
		_isAttack = false;
		//ステータスを走行に
		ChangeStatus(STATUS::RUN);
	}
}

void EN_Osero::DamageProcess()
{
	_actionCnt++;
	//カウントが総フレームに達した
	if (_actionCnt >= _data.motionTotalFrame)
	{
		//ステータスを走行に
		ChangeStatus(STATUS::RUN);
	}
}

void EN_Osero::DieProcess()
{
	_die = true;
	_isAttack = false;
}
void EN_Osero::SetWeapon()
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

void EN_Osero::Invincible(int nextframe)
{
	//無敵時間中のみカウントを増やす
	if (_noDamage) { _invincibleCnt++; }
	if (_invincibleCnt >= nextFrame)
	{
		_noDamage = false;
		_invincibleCnt = 0;
	}
}
VECTOR EN_Osero::AttackPos()
{
	return VECTOR();
}
bool EN_Osero::C_Process(VECTOR pl_pos)
{
	
	//カウントの加算
	_timeCnt++;
	//当たり判定カプセルの位置を変更
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//状態によって処理を変更
	switch (_status)
	{
	//待機
	case STATUS::WAIT:
		WaitProcess(pl_pos);
		break;
	//走行
	case STATUS::RUN:
		RunProcess(pl_pos);
		break;
	//ダメージ
	case STATUS::DAMAGE:
		DamageProcess();
		break;
	//警戒
	case STATUS::CAUTION:
		CautionProcess(pl_pos);
		break;
	//攻撃
	case STATUS::ATTACK:
		AttackProcess();
		break;
	//死亡
	case STATUS::DIE:
		DieProcess();
		break;
	}
	//埋まらないように位置を調整
	_vPos.y -= 10;
	if (_vPos.y <= 0)
	{
		_vPos.y = 0;
	}
	//無敵時間中のみカウントを増やす
	Invincible(nextFrame);
	SetWeapon();
	//モデルの位置を設定
	MV1SetPosition(_model, _vPos);
	//角度を求めるのだが座標系が違うので変更
	float angle = atan2(-_vDir.x, -_vDir.z);
	//モデルの向きを設定
	MV1SetRotationXYZ(_model, VGet(0,angle,0));
	return true;
}
bool EN_Osero::Process(VECTOR pl_pos)
{
	A_Process();
	C_Process(pl_pos);
	return true;
}
bool EN_Osero::Damage(VECTOR pl_pos,int subpoint, int nextframe)
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
		v = VScale(VNorm(v), 85);
		ChangeStatus(STATUS::DAMAGE);
	}
	_vPos = VAdd(_vPos, v);
	_isAttack = false;
	nextFrame = nextframe;
	_noDamage = true;
	return true;
}

bool EN_Osero::Suction(VECTOR pl_pos, int nextframe)
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

bool EN_Osero::Render()
{
	MV1SetAttachAnimTime(_model, _attachIndex, _playTime);
	MV1SetRotationXYZ(_wModel, VGet(0, 0.5, 0));
	MV1DrawModel(_model);
	MV1DrawModel(_wModel);
	return true;
}
bool EN_Osero::Debug()
{
	base::Debug();
	DrawFormatString(0, 200, GetColor(255, 255, 255), "cnt=%d", _actionCnt);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "time=%d", _playTime);
	return true;
}
bool EN_Osero::Delete()
{
	base::Delete();
	return true;
}
