#pragma once
#include "DxLib.h"
// MyMathにインクルードしているのでもしエラー起こしたらいじってみてください。

// そのまんま書くとめんどいので使うところでtypedef書いてください
// 例：typedef  MyStruct::MYRECT<使いたい型> ｜使いたい型を省略した文字｜_rect;
namespace MyStruct {
	// RECT用構造体
	template<typename T>
	struct MYRECT {
		T		x, y, w, h;
	};

	// RECT用構造体+アルファ(例は上下左右のスピード)
	//template<typename T>
	//struct MYRECT_PLUS {
	//	MYRECT<T> Rect;
	//  例：	T     mx, my;
	//};

	// CIRCLE用構造体
	template<typename T>
	struct MYCIRCLE {
		T x, y;
		T r;
	};
	
	// CIRCLE用構造体+アルファ(例は当たったかどうか)
	//template<typename T>
	//struct MYCIRCLE_PLUS {
	//	MYCIRCLE<T> Circle;
	//	bool hit;
	//};

		// VECTOR構造体
	template<typename T>
	struct MYVECTOR {
		T x, y, z;
	};

	// Sphere構造体
	template<typename T>
	struct MYSPHERE {
		VECTOR position;
		T radius;
	};

	// Color構造体（R,G,B）
	struct s_COLOR
	{		int r, g, b;	};

	// アナログスティック左右の座標
	struct ANALOGSTICK
	{
		float lx, ly, rx, ry, analogMin;	// 左右アナログスティックの座標とアナログ閾値（認識する最小の動きの幅）
	};
}