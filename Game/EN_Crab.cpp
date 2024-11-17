#include "EN_Crab.h"
EN_Crab::EN_Crab(int model, int weapon, VECTOR vpos, VECTOR vdir) : base(model, weapon, vpos, vdir)
{
	//初期値を設定
	MV1SetPosition(_model, _vPos);
	//移動量
	_vMove = VGet(0, 0, 0);
	//体力
	_hp = 60;
	//攻撃力
	_ap = 5;
	//判定カプセル内の要素を初期化
	//カプセルの半径
	_radius = 43;
	//線分の長さ
	_lineSeg = 170;
	//カプセルの位置
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//ステータスを待機状態に
	ChangeStatus(STATUS::WAIT);
	_type = ENEMYTYPE::CRAB;
}
EN_Crab::~EN_Crab()
{
	MV1DeleteModel(_model);
}

void EN_Crab::ChangeStatus(STATUS en_status)
{
	//ステータスの代入
	_data.status = en_status;
	//カウントリセット
	_actionCnt = 0;
	_timeCnt = 0;
	//各状態の総モーションフレームと探索範囲の代入
	switch (_data.status)
	{
	//待機
	case STATUS::WAIT:
		_data.motionTotalFrame = 0;
		_data._searchArea = 2000;
		break;
	//攻撃
	case STATUS::ATTACK:
		_data.motionTotalFrame = 0;
		_data._searchArea = 100;
		break;
	//休憩
	case STATUS::REST:
		_data.motionTotalFrame = 60;
		_data._searchArea = 100;
		break;
	//死亡
	case STATUS::DIE:
		_data.motionTotalFrame = 60;
		_data._searchArea = 100;
		break;
	}
}

bool EN_Crab::C_Process(VECTOR pl_pos)
{
	//カウントの加算
	_actionCnt++;
	_timeCnt++;
	//ステータスをデータ内の変更されたステータスに
	_status = _data.status;
	//当たり判定カプセルの位置を変更
	_vCapsule[0] = _vPos;
	_vCapsule[1] = VAdd(_vPos, VGet(0, _lineSeg, 0));
	//ローカル変数の初期化
	VECTOR v = VGet(0, 0, 0);
	float len = 0;
	//移動速度
	float speed = 0;
	//状態によって処理を変更　
	switch (_status)
	{
		//待機
	case STATUS::WAIT:
		//移動がないため速度を0に
		speed = 0;
		//プレイヤーと敵の位置の差分を出す
		v = VSub(_vPos, pl_pos);
		//ベクトルのサイズを計算
		len = VSize(v);
		//敵からプレイヤーの距離が探索範囲内
		if (len * len <= _data._searchArea * _data._searchArea)
		{
			//ステータスを攻撃に
			ChangeStatus(STATUS::ATTACK);
		}
		break;
		//攻撃
	case STATUS::ATTACK:
		//攻撃中なのでフラグをtrueに
		_isAttack = true;
		//ローカル変数
		VECTOR vec_pl_pos = VGet(0, 0, 0);
		VECTOR vector = VGet(0, 0, 0);
		//移動速度を設定
		speed = 2;
		//0.5秒に１回処理
		if (_timeCnt >= 30)
		{
			//自身の位置とプレイヤーのベクトルを作成
			vec_pl_pos = VSub(_vPos, pl_pos);
			//方向ベクトルとプレイヤーとの位置ベクトルの差分ベクトルを出してその2割のベクトルを出す
			vector = VScale(VSub(_vDir, vec_pl_pos), 0.2);
			//差分ベクトルと方向ベクトルを合成することで移動方向のベクトルができる
			vector = VAdd(vector, _vDir);
			//合成ベクトルの正規化し、方向ベクトルに
			_vDir = VNorm(vector);
			//カウントリセット
			_timeCnt = 0;
		}
		//方向ベクトルにスピードをかけたものを移動ベクトルとする
		_vMove = VScale(_vDir, speed);
		//位置ベクトルに移動ベクトルを加算
		_vPos = VAdd(_vPos, _vMove);
		break;
	case STATUS::REST:
		if (_actionCnt > _data.motionTotalFrame)
		{
			//ステータスを攻撃に
			ChangeStatus(STATUS::ATTACK);
		}
		break;
	case STATUS::DAMAGE:
		//カウントが総フレームに達した
		if (_actionCnt >= _data.motionTotalFrame)
		{
			//ステータスを走行に
			ChangeStatus(STATUS::RUN);
		}
		break;
	case STATUS::DIE:
		_isAttack = false;
		_die = true;
		Delete();
		break;
	}
	if (_noDamage) { _invincibleCnt++; }
	if (_invincibleCnt >= nextFrame)
	{
		_noDamage = false;
		_invincibleCnt = 0;
	}
	//埋まらないように位置を調整
	if (_vPos.y <= 0 || _vPos.y >= 0)
	{
		_vPos.y = 0;
	}
	if (_die)
	{
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
	//モデルの位置を設定
	MV1SetPosition(_model, _vPos);
	//モデルの向きを設定
	//角度を求めるのだが座標系が違うので変更
	float angle = atan2(-_vDir.x, -_vDir.z);
	MV1SetRotationXYZ(_model, VGet(0,angle,0));
	return true;
}
bool EN_Crab::Damage(VECTOR pl_pos, int subpoint, int nextframe)
{
	SoundItemBase* snditem_se = gGlobal._sndServer.Get("SE_Damage_Crab");
	snditem_se->SetVolume(200);
	if (snditem_se && snditem_se->IsLoad())
	{// 再生中か？
		if (snditem_se->IsPlay() == false)
		{// 再生する
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
		v = VScale(VNorm(v), 200);
	}
	_vPos = VAdd(_vPos, v);
	nextFrame = nextframe;
	return true;
}

bool EN_Crab::Suction(VECTOR pl_pos, int nextframe)
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
	VECTOR v = VSub(_vPos, pl_pos);
	v = VScale(VNorm(v), -5);
	_vPos = VAdd(_vPos, v);
	nextFrame = nextframe;
	_noDamage = true;
	return true;
}

bool EN_Crab::Process(VECTOR pl_pos)
{
	C_Process(pl_pos);
	return true;
}

bool EN_Crab::Render()
{
	MV1SetAttachAnimTime(_model, _attachIndex, _playTime);
	MV1DrawModel(_model);
	return true;
}

bool EN_Crab::Debug()
{
	base::Debug();
	return true;
}

bool EN_Crab::Delete()
{
	base::Delete();
	return true;
}






