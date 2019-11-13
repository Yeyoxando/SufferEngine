/*
               <M
   /| ......  /:M\------------------------------------------------,,,,,,
 ((O)[]XXXXXX[]I:K+}=====<{H}>================================------------>
   \| ^^^^^^  \:W/------------------------------------------------''''''
               <W

888b     d888          888    888
8888b   d8888          888    888
88888b.d88888          888    888
888Y88888P888  8888b.  888888 88888b.  88888b.d88b.   .d88b.  888d888 888d888 8888b.
888 Y888P 888     "88b 888    888 "88b 888 "888 "88b d88""88b 888P"   888P"      "88b
888  Y8P  888 .d888888 888    888  888 888  888  888 888  888 888     888    .d888888
888   "   888 888  888 Y88b.  888  888 888  888  888 Y88..88P 888     888    888  888
888       888 "Y888888  "Y888 888  888 888  888  888  "Y88P"  888     888    "Y888888

                                                          <M
   ,,,,,,------------------------------------------------/:M\ ...... |\
<------------=====<{H}>================================{+K:I[]XXXXXX[](0))
   ''''''------------------------------------------------\:W/ ...... |/
                                                          <W

Authors: Pablo Bañó Benito, Adrián Garvía Arrogante
Date: 17/02/2019
Version: 5.0
*/


#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

namespace ThiefUtils {

  class Math {

  public:
    static int RandomRange(int from, int to);
    static float Lerp(float x, float y, float s);
    static bool Approximately(float one, float two);

    static float Clamp(float value, float min, float max);
    static float Clamp01(float value);

    static float Max(float x, float y);
    static float Min(float x, float y);

    static float Radians(float degrees);
    static float Degrees(float radians);

    static float Ceil(float value);
    static float Floor(float value);

    // Attributes
    static float fPI;
    static double dPI;

  };

}


#endif