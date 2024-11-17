#include "MyMath.h"


  // 汎用的な計算関数
// イージング
float Math::EasingLinear(float cnt, float start, float end, float frames) {
  return (end - start) * cnt / frames + start;
}
float Math::EasingInQuad(float cnt, float start, float end, float frames) {
  cnt /= frames;
  return (end - start) * cnt * cnt + start;
}
float Math::EasingOutQuad(float cnt, float start, float end, float frames) {
  cnt /= frames;
  return -(end - start) * cnt * (cnt - 2) + start;
}
float Math::EasingInOutQuad(float cnt, float start, float end, float frames) {
  cnt /= frames / 2.0;
  if (cnt < 1) {
    return (end - start) / 2.0 * cnt * cnt + start;
  }
  cnt--;
  return -(end - start) / 2.0 * (cnt * (cnt - 2) - 1) + start;
}
float Math::EasingInCubic(float cnt, float start, float end, float frames) {
  cnt /= frames;
  return (end - start) * cnt * cnt * cnt + start;
}
float Math::EasingOutCubic(float cnt, float start, float end, float frames) {
  cnt /= frames;
  cnt--;
  return (end - start) * (cnt * cnt * cnt + 1) + start;
}
float Math::EasingInOutCubic(float cnt, float start, float end, float frames) {
  cnt /= frames / 2.0;
  if (cnt < 1) {
    return (end - start) / 2.0 * cnt * cnt * cnt + start;
  }
  cnt -= 2;
  return (end - start) / 2.0 * (cnt * cnt * cnt + 2) + start;
}
float Math::EasingInQuart(float cnt, float start, float end, float frames) {
  cnt /= frames;
  return (end - start) * cnt * cnt * cnt * cnt + start;
}
float Math::EasingOutQuart(float cnt, float start, float end, float frames) {
  cnt /= frames;
  cnt--;
  return -(end - start) * (cnt * cnt * cnt * cnt - 1) + start;
}
float Math::EasingInOutQuart(float cnt, float start, float end, float frames) {
  cnt /= frames / 2.0;
  if (cnt < 1) {
    return (end - start) / 2.0 * cnt * cnt * cnt * cnt + start;
  }
  cnt -= 2;
  return -(end - start) / 2.0 * (cnt * cnt * cnt * cnt - 2) + start;
}
float Math::EasingInQuint(float cnt, float start, float end, float frames) {
  cnt /= frames;
  return (end - start) * cnt * cnt * cnt * cnt * cnt + start;
}
float Math::EasingOutQuint(float cnt, float start, float end, float frames) {
  cnt /= frames;
  cnt--;
  return (end - start) * (cnt * cnt * cnt * cnt * cnt + 1) + start;
}
float Math::EasingInOutQuint(float cnt, float start, float end, float frames) {
  cnt /= frames / 2.0;
  if (cnt < 1) {
    return (end - start) / 2.0 * cnt * cnt * cnt * cnt * cnt + start;
  }
  cnt -= 2;
  return (end - start) / 2.0 * (cnt * cnt * cnt * cnt * cnt + 2) + start;
}
float Math::EasingInSine(float cnt, float start, float end, float frames) {
  return -(end - start) * cos(cnt / frames * (PI/2.0f)) + end + start;
}
float Math::EasingOutSine(float cnt, float start, float end, float frames) {
  return (end - start) * sin(cnt / frames * PI/2.0f) + start;
}
float Math::EasingInOutSine(float cnt, float start, float end, float frames) {
  return -(end - start) / 2.0 * (cos(PI * cnt / frames) - 1) + start;
}
float Math::EasingInExpo(float cnt, float start, float end, float frames) {
  return (end - start) * pow(2.0, 10 * (cnt / frames - 1)) + start;
}
float Math::EasingOutExpo(float cnt, float start, float end, float frames) {
  return (end - start) * (-pow(2.0, -10 * cnt / frames) + 1) + start;
}
float Math::EasingInOutExpo(float cnt, float start, float end, float frames) {
  cnt /= frames / 2.0;
  if (cnt < 1) {
    return (end - start) / 2.0 * pow(2.0, 10 * (cnt - 1)) + start;
  }
  cnt--;
  return (end - start) / 2.0 * (-pow(2.0, -10 * cnt) + 2) + start;
}
float Math::EasingInCirc(float cnt, float start, float end, float frames) {
  cnt /= frames;
  return -(end - start) * (sqrt(1 - cnt * cnt) - 1) + start;
}
float Math::EasingOutCirc(float cnt, float start, float end, float frames) {
  cnt /= frames;
  cnt--;
  return (end - start) * sqrt(1 - cnt * cnt) + start;
}
float Math::EasingInOutCirc(float cnt, float start, float end, float frames) {
  cnt /= frames / 2.0;
  if (cnt < 1) {
    return -(end - start) / 2.0 * (sqrt(1 - cnt * cnt) - 1) + start;
  }
  cnt -= 2;
  return (end - start) / 2.0 * (sqrt(1 - cnt * cnt) + 1) + start;
}

// 範囲内を返す
float Math::Clamp(float min_n, float max_n, float n) {
  if (n <= min_n) { return min_n; }
  if (n >= max_n) { return max_n; }
  return n;
}
