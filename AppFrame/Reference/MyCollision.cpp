#include "Mycollision.h"
#include "MyMath.h"


// 2Dにおける計算関数
bool ColDetect::IsHitBox(
  I_rect rect1,		// ひとつめのbox 左上(x,y), 大きさw,h
  I_rect rect2	// ふたつめのbox 左上(x,y), 大きさw,h
)
{
  if (rect1.x < rect2.x + rect2.w && rect2.x < rect1.x + rect1.w		// x方向の判定
    && rect1.y < rect2.y + rect2.h && rect2.y < rect1.y + rect1.h		// y方向の判定
    )
  {
    // 2つのboxは当たっている
    return true;
  }

  // 2つのboxは当たっていない
  return false;
}

bool ColDetect::IsHitCircle(
  F_circle circle1,		// ひとつめのcircle 中心(x,y), 半径r
  F_circle circle2			// ふたつめのcircle 中心(x,y), 半径r
) {
  int w, h, r;
  w = circle1.x - circle2.x;
  h = circle1.y - circle2.y;
  r = circle1.r + circle2.r;
  if (r * r > w * w + h * h) {
    return true;
  }
  return false;
}

bool ColDetect::IsHitCircleRect(
  F_circle circle,    // 円の判定
  I_rect rect         // 矩形の判定  
) {
  int x, y;
  float rad, deg;
  // 360点とって当たり判定したら場合によって重くなりました
  for (deg = 0; deg <= 360; deg += 90) {
    rad = Math::DegToRad(deg);
    x = (circle.x + circle.r * cos(rad));
    y = (circle.y + circle.r * sin(rad));

    // 当たっている・・・左上起点の矩形のみ（時間がないので）
    if (rect.x < x && x < rect.x + rect.w && rect.y < y && y < rect.y + rect.h) {
      return true;
    }
  }

  return false;
}