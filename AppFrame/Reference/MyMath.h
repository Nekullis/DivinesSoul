#pragma once
#include <math.h>
#include "MyStruct.h"

  // GeneralPurposeCalculate = 汎用的な計算関数
  class Math {
  public:

    static constexpr double PI = 3.141592653589793;

    // degree→radian
    template<typename T>
    static T DegToRad(T deg) {
      return deg * PI / 180.0f;		// 角度をdegreeからradianに変換
    };

    // radian→degree
    template<typename T>
    static T RadToDeg(T rad) {
      return rad * 180.0f / PI;		// 角度をradianからdegreeに変換
    };

    // 様々なイージング
// https://game-ui.net/?p=835 を参考に
    static float EasingLinear(float cnt, float start, float end, float frames);
    static float EasingInQuad(float cnt, float start, float end, float frames);
    static float EasingOutQuad(float cnt, float start, float end, float frames);
    static float EasingInOutQuad(float cnt, float start, float end, float frames);
    static float EasingInCubic(float cnt, float start, float end, float frames);
    static float EasingOutCubic(float cnt, float start, float end, float frames);
    static float EasingInOutCubic(float cnt, float start, float end, float frames);
    static float EasingInQuart(float cnt, float start, float end, float frames);
    static float EasingOutQuart(float cnt, float start, float end, float frames);
    static float EasingInOutQuart(float cnt, float start, float end, float frames);
    static float EasingInQuint(float cnt, float start, float end, float frames);
    static float EasingOutQuint(float cnt, float start, float end, float frames);
    static float EasingInOutQuint(float cnt, float start, float end, float frames);
    static float EasingInSine(float cnt, float start, float end, float frames);
    static float EasingOutSine(float cnt, float start, float end, float frames);
    static float EasingInOutSine(float cnt, float start, float end, float frames);
    static float EasingInExpo(float cnt, float start, float end, float frames);
    static float EasingOutExpo(float cnt, float start, float end, float frames);
    static float EasingInOutExpo(float cnt, float start, float end, float frames);
    static float EasingInCirc(float cnt, float start, float end, float frames);
    static float EasingOutCirc(float cnt, float start, float end, float frames);
    static float EasingInOutCirc(float cnt, float start, float end, float frames);

    // 範囲内を返す
    static float Clamp(float min_n, float max_n, float n);
  }; 

