#include "Divine.h"
#include"ApplicationGlobal.h"
Divine* Divine::_divineInstance = nullptr;
Divine::Divine()
{
	_divineInstance = this;
	_vPos = VGet(0,0,100);
	_hitFlag = false;
	_isDash = false;
	SKILL skill[8] =
	{//	スキル名, 判定範囲を描画するか, 位置, 当たり判定用サイズ, 再発動フレーム, 再発動までのカウント, 判定用カウント, 発動フラグ, 発動中か, 総合発動時間, 判定開始時間, エフェクト初期化
		{SKILLNAME::BREATH,	   VGet(0,0,0),   0.0f, 320, 0, 0,  30, true, false, 150.0f, 12.0f,  50.0f, new Effect("res/effekseer/bless/bless.efkefc",			   100.0f), "SE_Breath"},
		{SKILLNAME::CIRCLE,	   VGet(0,0,0), 150.0f, 900, 0, 0,   5, true, false, 500.0f, 27.0f, 400.0f, new Effect("res/effekseer/circle/circle.efkefc",			30.0f), "SE_Circle"},
		{SKILLNAME::LASER,	   VGet(0,0,0), 200.0f, 400, 0, 0,   5, true, false, 240.0f, 27.0f, 70.0f,  new Effect("res/effekseer/laser/Laser.efkefc",				30.0f), "SE_Laser"},
		{SKILLNAME::SLASH,	   VGet(0,0,0), 300.0f, 300, 0, 0,  30, true, false,  96.0f, 12.0f,  30.0f, new Effect("res/effekseer/slash/slash2.efkefc",				80.0f), "SE_Slash"},
		{SKILLNAME::EXPLOSION, VGet(0,0,0), 480.0f, 400, 0, 0, 100, true, false, 150.0f, 10.0f,  15.0f, new Effect("res/effekseer/explosion/explosion_new3.efkefc",	70.0f), "SE_Explosion"},
		{SKILLNAME::DASH,	   VGet(0,0,0), 100.0f, 180, 0, 0,  10, true, false,  60.0f, 15.0f,  60.0f, new Effect("res/effekseer/dash/dash.efkefc",				50.0f), "SE_DashAttack"},
		{SKILLNAME::VACUUM,	   VGet(0,0,0),   0.0f, 600, 0, 0,   0, true, false, 350.0f, 30.0f, 120.0f, new Effect("res/effekseer/vacuum/vacuum.efkefc",			50.0f), "SE_Vacuum"},
		{SKILLNAME::SONIC,	   VGet(0,0,0), 200.0f, 360, 0, 0,  20, true, false,  75.0f,  5.0f,  50.0f, new Effect("res/effekseer/sonicwave/sonicwave.efkefc",		50.0f), "SE_Sonic"}
	};
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		_skill[i] = std::move(skill[i]);
	}
}

Divine::~Divine()
{

}

void Divine::Invocation(kindDivine skillname)
{
	int i = static_cast<int>(skillname);
	if (_skill[i].invocationFlag)
	{
		//発動中かどうかをtrueに
		_skill[i].isPlaying = true;
		//スキル発動可能かどうかをfalseに
		_skill[i].invocationFlag = false;
	}
}

void Divine::Reset()
{
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (_skill[i].isPlaying)
		{
			//発動中かどうかをtrueに
			_skill[i].isPlaying = false;
			//スキル発動可能かどうかをfalseに
			_skill[i].invocationFlag = false;
			_skill[i].effect->Stop();
		}
		_skill[i].colCnt = 0;
		_isDash = false;
	}
	
}

bool Divine::Calcalate(VECTOR pos, float roty)
{
	MATRIX matrix = MGetRotY(roty);
	VECTOR _all_skill_calc_pos[MAX_SKILL_NUM] =
	{
		VGet(0,0,0),
		VGet(0,100,0),
		VGet(0,100,400 - (24 * _skill[2].colCnt)),
		VGet(0,0,0),
		VGet(0,100,-630),
		//VGet(0,0,0),
		VGet(0,0,0),
		VGet(0,100,-50),
		VGet(0,0,0)
	};
	for (auto i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (_skill[i].isPlaying)
		{
			if (_skill[i].colCnt > _skill[i].startColFrame &&
				_skill[i].colCnt <= _skill[i].endColFrame)
			{
				_skill[i].vPos = VAdd(pos, VTransform(_all_skill_calc_pos[i], matrix));
			}
		}
	}
	return true;
}

bool Divine::Process(VECTOR pos, float roty)
{
	Calcalate(pos, roty);
	//スキルの位置
	VECTOR all_skill_pos[MAX_SKILL_NUM] =
	{
		VGet(0,0,0),
		VGet(0,30,0),
		VGet(0,100,-200),
		VGet(0,0,0),
		VGet(0,0,-630),
		//VGet(0,0,0),
		VGet(0,100,-100),
		VGet(0,100,-50),
		VGet(0,0,0)
	};
	//y軸回転のためのマトリクス作成
	MATRIX matrix = MGetRotY(roty);
	float all_skill_dir[MAX_SKILL_NUM] =
	{
		90.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
	};
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		//スキル発動可能でないのならカウントを増やす
		if (!_skill[i].invocationFlag)
		{
			_skill[i].divineCnt++;
		}
		//カウントが特定のフレームに達した
		if(_skill[i].colCnt >= _skill[i].startColFrame + 10)
		{
			//再生可能フラグをfalseに
			_skill[i].effect->SetUseFlag(false);
		}
		//カウントが発動可能フレームまで達したなら
		if (_skill[i].divineCnt >= _skill[i].reInvocationFrame)
		{
			//エフェクト再生可能フラグをtrueに
			_skill[i].effect->SetUseFlag(true);
			//スキル発動フラグをtrueに
			_skill[i].invocationFlag = true;
			//カウントリセット
			_skill[i].divineCnt = 0;
		}
		//再生中でなければコンティニュー
		if (!_skill[i].isPlaying) continue;
		else{ _skill[i].colCnt++;}
		//エフェクト再生中なら
		if (_skill[i].effect->GetPlayFlag())
		{
			//向きの単位をラジアンに変更
			all_skill_dir[i] = Math::DegToRad(all_skill_dir[i]);
			//向きを変更する
			_skill[i].effect->SetDir(VGet(0,roty+all_skill_dir[i], 0));
			//位置を変更
			_skill[i].effect->SetPos(VAdd(pos, VTransform(all_skill_pos[i], matrix)));
			//プロセスを回す
			_skill[i].effect->Process();
		}
		//エフェクトの再生
		if (_skill[i].colCnt == _skill[i].startColFrame)
		{
			_skill[i].effect->Play();
			//何回も再生されないように条件を付ける
			if (_skill[i].colCnt <= _skill[i].startColFrame + 1)
			{
				SoundItemBase* snditem_se = gGlobal._sndServer.Get(_skill[i].seCode);
				if (snditem_se && snditem_se->IsLoad())
				{	// 再生中か？
					if (snditem_se->IsPlay() == false)
					{	// 再生する
						snditem_se->Play();
					}
				}
			}
		}
		//判定カウントが総発動時間に到達した
		if (_skill[i].colCnt >= _skill[i].invocationFrame)
		{
			//発動していないのでfalse
			_skill[i].isPlaying = false;
			_isDash = false;
			//カウントリセット
			_skill[i].colCnt = 0;
		}
	}
	return true;
}

bool Divine::Render()
{
	//エフェクトの描画
	for (int i = 0; i < MAX_SKILL_NUM; i++)
	{
		if (_skill[i].effect->GetPlayFlag())
		{
			_skill[i].effect->Draw();
		}
	}
	return true;
}
bool Divine::Debug()
{
	DrawFormatString(300, 0, GetColor(0, 0, 255), "Cnt =%d", _skill[3].divineCnt);
	DrawFormatString(300, 20, GetColor(0, 0, 255), "Cnt =%d", _skill[4].divineCnt);
	return true;
}