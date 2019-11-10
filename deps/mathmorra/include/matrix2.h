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

#ifndef __MATRIX_2_H__
#define __MATRIX_2_H__ 1

#include "vector2.h"

namespace mathmorra {

  class Matrix2 {

  public:
    Matrix2();
    Matrix2(float a[4]);
    Matrix2(float a);
    Matrix2(mathmorra::Vector2 a, mathmorra::Vector2 b);
    Matrix2(const Matrix2& copy);
    ~Matrix2() {}
    Matrix2 Identity() const;
    Matrix2 Multiply(const Matrix2& b) const;
    float Determinant() const;
    Matrix2 Adjoint() const;
    mathmorra::Vector2 GetLine(int line) const;
    mathmorra::Vector2 GetColum(int line) const;

    Matrix2 Inverse() const;
    Matrix2 Transpose() const;

    Matrix2 operator+(const Matrix2& b) const;
    void operator+=(const Matrix2& b);
    Matrix2 operator+(const float& b) const;
    void operator+=(const float& b);
    Matrix2 operator-(const Matrix2& b) const;
    void operator-=(const Matrix2& b);
    Matrix2 operator-(const float& b) const;
    void operator-=(const float& b);

    Matrix2 operator*(const float& b) const;
    void operator*=(const float& b);
    Matrix2 operator/(const float& b) const;
    void operator/=(const float& b);

    bool operator==(const Matrix2& b) const;
    bool operator!=(const Matrix2& b) const;
    void operator=(const Matrix2& b);

    float m[4];
  };

} /* Mathmorra - Matrix2 */

#endif