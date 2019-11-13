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
Date: 09/02/2019
Version: 5.0
*/

#ifndef __MATRIX_4_H__
#define __MATRIX_4_H__ 1

#include <vector3.h>
#include <vector4.h>

namespace mathmorra {

  //-------------------------------- Matrix 4 ---------------------------------//

  class Matrix4 {
  public:

    Matrix4();
    Matrix4(float a[16]);
    Matrix4(float a);
    Matrix4(Vector4 a, Vector4 b, Vector4 c, Vector4 d);
    Matrix4(const Matrix4& copy);
    ~Matrix4();

    static Matrix4 Identity();
    static Matrix4 Zero();
    Matrix4 Multiply(const Matrix4& b) const;

    float Determinant() const;
    Matrix4 Adjoint() const;
    bool IsIdentity();
    bool GetInverse(Matrix4* out) const;
    bool Inverse();

    Matrix4 Transpose() const;
    static Matrix4 LookAt(mathmorra::Vector3 eye,
                          mathmorra::Vector3 target,
                          mathmorra::Vector3 up);


    //--------------------------- Transformations ------------------------------//

    static Matrix4 Translate(const Vector3& mov_vector);
    static Matrix4 Translate(float x, float y, float z);

    static Matrix4 Scale(const Vector3& scale_vector);
    static Matrix4 Scale(float x, float y, float z);


    static Matrix4 RotateX(float angle);
    static Matrix4 RotateY(float angle);
    static Matrix4 RotateZ(float angle);

    static Matrix4 GetTransform(const Vector3& translate, const Vector3& scale,
      float rotateX, float rotateY, float rotateZ);

    static Matrix4 GetTransform(float trans_x, float trans_y, float trans_z,
      float scale_x, float scale_y, float scale_Z,
      float rotateX, float rotateY, float rotateZ);

    Matrix4 PerspectiveMatrix(float fov, float aspect, float near, float far) const;
    Matrix4 OrthoMatrix(float width, float height, float near, float far) const;

    Vector4 GetColum(int colum) const;
    Vector4 GetLine(int line) const;

    //More functions
    void SetColum(const Vector4& a, int colum);
    void SetRow(const Vector4& a, int row);


    //-------------------------- Operand overload -------------------------------//

    Matrix4 operator+(const Matrix4& b) const;
    Matrix4 operator*(const Matrix4& b);
    void operator*=(const Matrix4& b);
    void operator+=(const Matrix4& b);
    Matrix4 operator+(float b) const;
    void operator+=(float b);
    Matrix4 operator-(const Matrix4& b) const;
    void operator-=(const Matrix4& b);
    Matrix4 operator-(float b) const;
    void operator-=(float b);
    void operator*=(float b);
    Matrix4 operator*(float b) const;
    void operator/=(float b);
    Matrix4 operator/(float b) const;
    bool operator==(const Matrix4& b);
    bool operator!=(const Matrix4& b);
    void operator=(const Matrix4& b);

    mathmorra::Vector3 operator*(mathmorra::Vector3 scalar) const;
    mathmorra::Vector4 operator*(mathmorra::Vector4 scalar) const;

    //------------------------------- Attributes --------------------------------//

    float m[16];

  };

  //---------------------------------------------------------------------------//

}

#endif