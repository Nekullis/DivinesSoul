#include "MathCollision.h"
#include "appframe.h"
MathCollision::MathCollision()
{

}
MathCollision::~MathCollision()
{

}
float MathCollision::DisPointAndLine(VECTOR& v1, VECTOR& v2s, VECTOR& v2e, VECTOR& mp, float& t)
{
	//v1:点の座標
	//v2s:直線の始点の座標
	//v2e:直線の終点の座標
	//mp:v1から直線に下した垂線の端点
	//始点と終点の座標があるのでこれは線分なのだが、今回は直線として扱う
	//t:直線v2(v2e-v2s)の長さを1とした時のv2sからmpまでの長さの割合

	VECTOR v2 = VSub(v2e, v2s);
	//v2:v2sからv2eまでの直線
	t = 0.0f;
	float dv = VDot(v2, v2);
	if (dv > 0.0f)
	{
		t = VDot(v2, VSub(v1, v2s)) / dv;
		//VDot(v2,VSub(v1,v2s))=|v2||VSub(v1,v2s)|cosθ
		//dv=v2*v2
		//t=|VSub(v1,v2s)|cosθ /|v2|
	}
	mp = VAdd(v2s, VScale(v2, t));
	return sqrt(VDot(VSub(v1, mp), VSub(v1, mp)));
}

float MathCollision::DisPointAndSegment(VECTOR& v1, VECTOR& v2s, VECTOR& v2e, VECTOR& mp, float& t)
{
	//v1:点の座標
	//v2s:線分の始点の座標
	//v2e:線分の終点の座標
	//mp:v1から線分に下した垂線の端点
	//t:線分v2(v2e-v2s)の長さを1とした時のv2sからmpまでの長さの割合
	VECTOR v2 = VSub(v2e, v2s);
	float dist = DisPointAndLine(v1, v2s, v2e, mp, t);
	if (t < 0.0f)
	{
		//点から始点までの距離が最短
		mp = v2s;
		return sqrt(VDot(VSub(v1, mp), VSub(v1, mp)));
	}
	if (t > 1.0f)
	{
		//点から線分の終点までの距離が最短
		mp = v2e;
		return sqrt(VDot(VSub(v1, mp), VSub(v1, mp)));
	}
	//mpが線分内にある
	//0 <= t <= 1
	return dist;
}

float MathCollision::DisLineAndLine(VECTOR& v1s, VECTOR& v1e, VECTOR& v1m, float& t1, VECTOR& v2s, VECTOR& v2e, VECTOR& v2m, float& t2)
{
	//v1s:直線の始点の座標
	//v1e:直線の終点の座標
	//v1m:最短線の端点1
	//t1:線分v1(v1e-v1s)の長さを1とした時のv1sからv1mまでの長さの割合
	//v2s:直線の始点の座標
	//v2e:直線の終点の座標
	//v2m:最短線の端点2
	//t2:線分v2(v2e-v2s)の長さを1とした時のv2sからv2mまでの長さの割合
	//始点と終点の座標があるのでこれは線分なのだが、今回は直線として扱う
	VECTOR v1 = VSub(v1e, v1s);
	VECTOR v2 = VSub(v2e, v2s);
	//2直線が平行の場合
	if (VDot(VCross(v1, v2), VCross(v1, v2)) < 0.000001f && VDot(VCross(v1, v2), VCross(v1, v2)) > -0.000001f);
	{
		//線分1の始点から直線2までの最短距離問題に帰着
		float dist = DisPointAndLine(v1s, v2s, v2e, v2m, t2);
		v1m = v1s;
		t1 = 0.0f;
		return dist;
	}
	//2直線が平行でない場合
	//互いが垂直になる最短線の端点v1m,v2mを求める
	float dov1v2 = VDot(v1, v2);
	float dov1v1 = VDot(v1, v1);
	float dov2v2 = VDot(v2, v2);
	VECTOR vp2p1 = VSub(v1s, v2s);
	t1 = (dov1v2 + VDot(v2, vp2p1) - dov2v2 * VDot(v1, vp2p1)) / (dov1v1 * dov2v2 - dov1v2 * dov1v2);
	v1m = VAdd(v1s, VScale(v1, t1));
	t2 = VDot(v2, VSub(v1m, v2s)) / dov2v2;
	v2m = VAdd(v2s, VScale(v2, t2));
	return sqrt(VDot(VSub(v2m, v1m), VSub(v2m, v1m)));
}

float MathCollision::DisSegAndSeg(VECTOR& v1s, VECTOR& v1e, VECTOR& v1m, float& t1, VECTOR& v2s, VECTOR& v2e, VECTOR& v2m, float& t2)
{
	//はみ出さないようにクランプする関数を作っておく
	auto clamp0to1 = [](float& f)
		{
			if (f < 0.0f) { f = 0.0f; }
			else if (f > 1.0f) { f = 1.0f; }
		};
	//v1s:直線の始点の座標
	//v1e:直線の終点の座標
	//v1m:最短線の端点1
	//t1:線分v1(v1e-v1s)の長さを1とした時のv1sからv1mまでの長さの割合
	//v2s:直線の始点の座標
	//v2e:直線の終点の座標
	//v2m:最短線の端点2
	//t2:線分v2(v2e-v2s)の長さを1とした時のv2sからv2mまでの長さの割合
	VECTOR v1 = VSub(v1e, v1s);
	VECTOR v2 = VSub(v2e, v2s);
	float dist = 0.0f;
	//一旦2直線間の最短距離を求める
	dist = DisLineAndLine(v1s, v1e, v1m, t1, v2s, v2e, v2m, t2);
	if (0.0f <= t1 && t1 <= 1.0f && 0.0f <= t2 && t2 <= 1.0f)
	{
		//v1m,v2mが両方とも線分内にあった
		return dist;
	}
	//両方、またはどちらかがないため次へ
	clamp0to1(t2);
	v2m = VAdd(v2s, VScale(v2, t2));
	//vb = v2m;
	dist = DisPointAndSegment(v2m, v1s, v1e, v1m, t1);
	if (0.0f <= t1 && t1 <= 1.0f)
	{
		//v2mが線分内にあった
		return dist;
	}
	//v1mが線分内にないので次へ
	clamp0to1(t1);
	v1m = VAdd(v1s, VScale(v1, t1));
	//va = v1m;
	dist = DisPointAndSegment(v1m, v2s, v2e, v2m, t2);
	if (0.0f <= t2 && t2 <= 1.0f)
	{
		//v2mが線分内にあった
		return dist;
	}
	//v2mが線分内にないので次へ
	//ここまでなかったらv1mからv2mまでが最短
	return sqrt(VDot(VSub(v2m, v1m), VSub(v2m, v1m)));
}

float MathCollision::DisPointAndOBB(VECTOR v1p, VECTOR v2p, VECTOR v2d, float w2, float h2, float d2)
{
	float dis = 0;
	VECTOR vec = VGet(0, 0, 0);
	//for文で使えるように各大きさを配列に代入
	float getlen[3] = { w2,h2,d2 };
	for (auto i = 0; i < 3; i++)
	{
		float l = getlen[i];
		//各大きさが0より大きいなら続行
		if (l <= 0) { continue; }
		//点とOBBの位置の差分と方向ベクトルから内積を計算し、各大きさで割る
		float s = VDot(VSub(v1p, v2p), v2d) / l;
		//絶対値に変換
		s = std::fabs(s);
		if (s > 1)
		{//絶対値が1より大きいならはみ出した部分のベクトル算出
			vec = VAdd(vec, VScale(v2d, (1 - s) * l));
		}
	}
	dis = VSize(vec);
	return dis;
}

bool MathCollision::CollisionPointAndFan(VECTOR v1, VECTOR v2, float rad)
{
	//内積の計算
	v1 = VNorm(v1);
	v2 = VNorm(v2);
	float dot = VDot(v1, v2);
	//内積の計算がバグらないように
	if (dot < 0.0000001 && dot > -0.0000001) { return false; }
	if (dot > Math::DegToRad(rad))
	{
		return true;
	}
	return false;
}
