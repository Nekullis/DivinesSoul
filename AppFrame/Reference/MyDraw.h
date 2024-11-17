#pragma once
#include "DxLib.h"		// VECTORやMATRIXを定義として使うため、.hに入れておく
#include "MyStruct.h"

namespace DXLib_Depend {// DXLibに依存している
	// 画像の中心で回転して描画する
	static void MyDrawModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle);

	// 画像の中心で回転して描画する(左右反転版)
	static void MyDrawTurnModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle);

	// 4点を指定して四角を描く
	static void MyDraw4PointBox(MATRIX mView, VECTOR pos[4], unsigned int Color, int FillFlag);

	// 矩形を描く
	static void MyDrawBox(MATRIX mView, int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag);

	static void MyDrawExtendGraph(MATRIX mView, int x1, int y1, int x2, int y2, unsigned int handle, int FillFlag);

	static void MyDrawDeformationGraph(MATRIX mView, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float direction, int handle, int FillFlag);

	static void MyDrawRect(MATRIX mView, MyStruct::MYRECT<int> rc, unsigned int Color, int FillFlag);

	static void MyDrawLine(MATRIX mView, int x1, int y1, int x2, int y2, int Color);

	static void MyDrawCircle(MATRIX mView, int x, int y, int r);

	// 位置を揃えて文字列を描く
	// posBaseX = -1:左揃え, 0:中央, 1:右揃え
	static void DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str);

}

