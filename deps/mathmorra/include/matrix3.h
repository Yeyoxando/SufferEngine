/*
               <M
   /| ......  /:M\------------------------------------------------,,,,,,
 ((O)[]XXXXXX[]I:K+}=====<{H}>================================------------>
   \| ^^^^^^  \:W/------------------------------------------------''''''
               <W

                         _ _  .',        '     | ______
                        |_)_)  |  |~) \/ | (_(_| (_(_(_
                                  |   (,


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
Date: 09/02/2019
Version: 5.0
*/

#ifndef __MATRIX3_H__
#define __MATRIX_3_H__ 1

#include <vector3.h>

namespace mathmorra {

  class Matrix3 {
  public:

    Matrix3();
    Matrix3(float *a);
    Matrix3(float a);
    Matrix3(mathmorra::Vector3 a, mathmorra::Vector3 b, mathmorra::Vector3 c);

    Matrix3(const Matrix3& copy);
    ~Matrix3();

    static Matrix3 Identity();

    Matrix3 Multiply(const Matrix3& b) const;

    float Determinant() const;

    Matrix3 Adjoint() const;
    bool GetInverse(Matrix3* out) const;
    bool Inverse();

    Matrix3 Transpose() const;
    static Matrix3 LookRotation(Vector3 forward, Vector3 up);

    //static Matrix3 Translate(const Vector2& position);
    static Matrix3 Translate(float x, float y);

    Vector3 GetColum(int colum) const;
    Vector3 GetLine(int line) const;

    Matrix3 operator+(const Matrix3& b) const;
    void operator+=(const Matrix3& b);
    Matrix3 operator+(float b) const;
    void operator+=(float b);
    Matrix3 operator-(const Matrix3& b) const;
    void operator-=(const Matrix3& b);
    Matrix3 operator-(float b) const;
    void operator-=(float b);
    Matrix3 operator*(float b) const;
    void operator*=(float b);
    Matrix3 operator/(float b) const;
    void operator/=(float b);
    bool operator==(const Matrix3& b) const;
    bool operator!=(const Matrix3& b) const;
    void operator=(const Matrix3& b);

    Vector3 operator*(Vector3 scalar) const;

    float m[9];
  };
}

#endif