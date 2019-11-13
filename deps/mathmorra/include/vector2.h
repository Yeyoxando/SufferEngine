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
Date: 01/02/2019
Version: 5.0
*/

#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__ 1

#include "math.h"

namespace mathmorra {

  class Vector2 {

    public:

      //Constructors / Destructor
      Vector2();
      Vector2(float x, float y);
      Vector2(const Vector2& copy);
      ~Vector2();

      //Operators overload
      Vector2 operator+(const Vector2& b) const;
      Vector2& operator+(const float& b);
      Vector2& operator+=(const Vector2& b);
      Vector2& operator+=(const float& b);
      Vector2 operator-(const Vector2& b) const;
      Vector2 operator-(const float& b) const;
      Vector2& operator-();
      Vector2& operator-=(const Vector2& b);
      Vector2& operator-=(const float& b);
      bool operator==(const Vector2& b) const;
      bool operator!=(const Vector2& b) const;
      void operator=(const Vector2& b);
      void operator=(const float& b);
      Vector2 operator*(const float& b);
      Vector2& operator*=(const float& b);
      Vector2 operator/(const float& b);
      Vector2& operator/=(const float& b);

      //Miscellaneous
      void Normalize();
      float Magnitude() const;
      Vector2 Normalized() const;
      float SqrMagnitude() const;
      void Scale(const Vector2 scale);
      static float DotProduct(Vector2 a, Vector2 b);
      static float Distance(const Vector2 a, const Vector2 b);
      static Vector2 Lerp(const Vector2 a, const Vector2 b, float t);
      static Vector2 LerpUnclamped(const Vector2 a, const Vector2 b, float t);
      
      //Constants
      static const Vector2 up;
      static const Vector2 down;
      static const Vector2 right;
      static const Vector2 left;
      static const Vector2 zero;
      static const Vector2 one;

      //Attributes
      float x_;
      float y_;

  };

}/* Mathmorra - Vector2 */

#endif
