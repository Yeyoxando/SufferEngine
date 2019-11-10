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

#ifndef __VECTOR_3_H__
#define __VECTOR_3_H__ 1

namespace mathmorra {

  class Vector3 {

  public:
    //Constructors / Destructor
    Vector3();
    Vector3(const float x, const float y, const float z);
    Vector3(const Vector3& copy);
    ~Vector3() {}

    //Operators
    Vector3 operator+(const Vector3& b) const;
    Vector3 operator+(const float& b);
    Vector3& operator+=(const Vector3& b);
    Vector3& operator+=(const float& b);
    Vector3 operator-(const Vector3& b) const;
    Vector3 operator-(const float& b) const;
    Vector3 operator-();
    Vector3& operator-=(const Vector3& b);
    Vector3& operator-=(const float& b);
    bool operator==(const Vector3& b) const;
    bool operator!=(const Vector3& b) const;
    void operator=(const Vector3& b);
    void operator=(const float& b);
    Vector3 operator*(const float& b);
    Vector3& operator*=(const float& b);
    Vector3 operator/(const float& b);
    Vector3& operator/=(const float& b);

    float Magnitude() const;
    Vector3 Normalized() const;
    void Normalize();
    float SqrMagnitude() const;
    void Scale(const Vector3& other);

    static Vector3 Normalized(mathmorra::Vector3 a);
    static Vector3 Max(const Vector3& a, const Vector3& b);
    static Vector3 Min(const Vector3& a, const Vector3& b);
    static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);
    static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);
    static float DotProduct(const Vector3& a, const Vector3& b);
    static float Angle(const Vector3& a, const Vector3& b);
    static Vector3 CrossProduct(const Vector3 a, const Vector3 b);
    static float Distance(const Vector3& a, const Vector3& b);
    static Vector3 ClampMagnitude(const Vector3& a, float maxLen);

    static const Vector3 up;
    static const Vector3 down;
    static const Vector3 right;
    static const Vector3 left;
    static const Vector3 forward;
    static const Vector3 back;
    static const Vector3 zero;
    static const Vector3 unit;

    float x_;
    float y_;
    float z_;

  };
}
#endif