#pragma once
#include <math.h>
#include "MyStruct.h"

class ColDetect {
  // MyStructから使う構造体を楽に使えるようにタイプディフする
  typedef  MyStruct::MYRECT<int> I_rect;
  typedef MyStruct::MYCIRCLE<float> F_circle;
public:
  // 当たり判定用。2つのboxが当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
  static bool IsHitBox(
    I_rect rect1,		// ひとつめのbox 左上(x,y), 大きさw,h
    I_rect rect2	// ふたつめのbox 左上(x,y), 大きさw,h
  );

  // 当たり判定用。2つの円が当たったかを判定
// 当たっていたら1, 当たっていなかったら0を返す
  static bool IsHitCircle(
    F_circle circle1,		// ひとつめのcircle 中心(x,y), 半径r
    F_circle circle2		// ふたつめのcircle 中心(x,y), 半径r
  );

  // 当たり判定用。円と矩形が当たったかを判定（不完全なため、要更新）
// 当たっていたら1, 当たっていなかったら0を返す
  static bool IsHitCircleRect(
    F_circle circle,    // 円の判定
    I_rect rect         // 矩形の判定      
  );

};

