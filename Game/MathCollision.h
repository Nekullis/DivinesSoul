#pragma once
#include"dxlib.h"
#include<cmath>
class MathCollision
{
public:
	MathCollision();
	virtual ~MathCollision();
	//点と直線の最短距離
	static float DisPointAndLine(VECTOR& v1, VECTOR& v2s, VECTOR& v2e, VECTOR& mp, float& t);
	//点と線分の最短距離
	static float DisPointAndSegment(VECTOR& v1, VECTOR& v2s, VECTOR& v2e, VECTOR& mp, float& t);
	//直線と直線の最短距離
	static float DisLineAndLine(VECTOR& v1s, VECTOR& v1e, VECTOR& v1m, float& t1, VECTOR& v2s, VECTOR& v2e, VECTOR& v2m, float& t2);
	//線分と線分の最短距離
	static float DisSegAndSeg(VECTOR& v1s, VECTOR& v1e, VECTOR& v1m, float& t1, VECTOR& v2s, VECTOR& v2e, VECTOR& v2m, float& t2);
	//点とOBBの最短距離
	static float DisPointAndOBB(VECTOR v1p, VECTOR v2p, VECTOR v2d, float w2, float h2, float d2);
	//点と扇形の当たり判定
	//v1:方向ベクトル, v2:差分ベクトル, rad;角度
	static bool CollisionPointAndFan(VECTOR v1, VECTOR v2, float rad);
};

