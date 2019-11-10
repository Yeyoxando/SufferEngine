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

#ifndef __VECTOR_4_H__
#define __VECTOR_4_H__ 1

#include "vector3.h"
#include "matrix3.h"
#include <math.h>

namespace mathmorra {

  class Vector4 {
  public:

    //Constructors / Destructor
    Vector4();
    Vector4(float x, float y, float z, float w);
    Vector4(Vector3 a, float w);
    Vector4(float a);
    Vector4(const Vector4& other);
    ~Vector4();


    //Operators overload
    Vector4 operator+(const Vector4& b) const;
    Vector4 operator+(const float& b) const;
    void operator+=(const Vector4& b);
    void operator+=(const float& b);
    Vector4 operator-(const Vector4& b) const;
    Vector4 operator-(const float& b) const;
    void operator -=(const Vector4& b);
    void operator -=(const float& b);
    Vector4 operator*(const float& b) const;
    void operator*=(const float& b);
    Vector4 operator/(const float& b) const;
    void operator/=(const float& b);
    bool operator==(const Vector4& b);
    bool operator!=(const Vector4& b);
    void operator=(const Vector4& b);


    //Miscellaneous
    float Magnitude() const;
    void Normalize();
    Vector4 Normalized() const;
    void Scale(Vector4 scale);
    float SqrMagnitude() const;
    static float Distance(const Vector4& a, const Vector4& b);
    static float DotProduct(Vector4 a, Vector4 b); // a · b
    static Vector4 Lerp(const Vector4& a, const Vector4& b, float index);
    static Vector4 Projection(Vector4 a, Vector4 b);

    //Constants
    static const Vector4 one;
    static const Vector4 zero;

    //Attributes
    float x_;
    float y_;
    float z_;
    float w_;

  };

}/* Mathmorra */

#endif
