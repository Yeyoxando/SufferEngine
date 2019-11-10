/*
Author: Pablo Bano Benito <pablo.bano.benito@gmail.com>
Date: 10-02-2019
Matrix4
*/

#include "matrix4.h"
#include "math.h"

//---------------------------------------------------------------------------//

mathmorra::Matrix4::Matrix4() {

  for (int i = 0; i < 16; ++i) {
    m[i] = 0.0f;
  }

}

//---------------------------------------------------------------------------//

mathmorra::Matrix4::Matrix4(Vector4 a, Vector4 b, Vector4 c, Vector4 d){

  this->m[0] = a.x_;
  this->m[1] = a.y_;
  this->m[2] = a.z_;
  this->m[3] = a.w_;

  this->m[4] = b.x_;
  this->m[5] = b.y_;
  this->m[6] = b.z_;
  this->m[7] = b.w_;

  this->m[8]  = c.x_;
  this->m[9]  = c.y_;
  this->m[10] = c.z_;
  this->m[11] = c.w_;

  this->m[12] = d.x_;
  this->m[13] = d.y_;
  this->m[14] = d.z_;
  this->m[15] = d.w_;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix4::Matrix4 (float a[16]) {

  for (int i = 0; i < 16; ++i) {
    m[i] = a[i];
  }

}

//---------------------------------------------------------------------------//

mathmorra::Matrix4::Matrix4(const mathmorra::Matrix4& copy) {

  for (int i = 0; i < 16; ++i) {
    this->m[i] = copy.m[i];
  }

}

//---------------------------------------------------------------------------//

mathmorra::Matrix4::Matrix4 (float a) {

  for (int i = 0; i < 16; ++i) {
    m[i] = a;
  }

}

//---------------------------------------------------------------------------//

mathmorra::Matrix4::~Matrix4 () {

}

//---------------------------------------------------------------------------//

mathmorra::Matrix4 mathmorra::Matrix4::operator+(const mathmorra::Matrix4& b) const {

  Matrix4  result;

  for (int i = 0; i < 16; ++i) {
    result.m[i] = this->m[i] + b.m[i];
  }

  return result;

}

//---------------------------------------------------------------------------//

 void mathmorra::Matrix4::operator+=(const mathmorra::Matrix4 & b) {

  for (int i = 0; i < 16; ++i) {
    this->m[i] += b.m[i];
  }

}

//---------------------------------------------------------------------------//

 mathmorra::Matrix4 mathmorra::Matrix4::operator+(float b) const {

  Matrix4  result;

  for (int i = 0; i < 16; ++i) {
    result.m[i] = (this->m[i] + b);
  }

  return result;

}

//---------------------------------------------------------------------------//

 void mathmorra::Matrix4::operator+=(float b) {

  for (int i = 0; i < 16; ++i) {
    m[i] += b;
  }

}

//---------------------------------------------------------------------------//

 mathmorra::Matrix4 mathmorra::Matrix4::operator-(const mathmorra::Matrix4 & b) const {

  Matrix4  result = { 0.0f };

  for (int i = 0; i < 16; ++i) {
    result.m[i] = m[i] + b.m[i];
  }

  return result;

}

//---------------------------------------------------------------------------//

 void mathmorra::Matrix4::operator-=(const mathmorra::Matrix4 & b) {

  for (int i = 0; i < 16; ++i) {
    this->m[i] -= b.m[i];
  }

}

//---------------------------------------------------------------------------//

 mathmorra::Matrix4  mathmorra::Matrix4::operator-(float b) const {

  Matrix4  result = { 0.0f };

  for (int i = 0; i < 16; ++i) {
    result.m[i] = (this->m[i] - b);
  }

  return result;

}

//---------------------------------------------------------------------------//

 void mathmorra::Matrix4::operator-=(float b) {

  for (int i = 0; i < 16; ++i) {
    this->m[i] -= b;
  }

}


void mathmorra::Matrix4::operator*=(const Matrix4& b){

  this->m[0] = (m[0] * b.m[0]) + (m[1] * b.m[4]) + (m[2] * b.m[8]) + (m[3] * b.m[12]);
  this->m[1] = (m[0] * b.m[1]) + (m[1] * b.m[5]) + (m[2] * b.m[9]) + (m[3] * b.m[13]);
  this->m[2] = (m[0] * b.m[2]) + (m[1] * b.m[6]) + (m[2] * b.m[10]) + (m[3] * b.m[14]);
  this->m[3] = (m[0] * b.m[3]) + (m[1] * b.m[7]) + (m[2] * b.m[11]) + (m[3] * b.m[15]);

  this->m[4] = (m[4] * b.m[0]) + (m[5] * b.m[4]) + (m[6] * b.m[8]) + (m[7] * b.m[12]);
  this->m[5] = (m[4] * b.m[1]) + (m[5] * b.m[5]) + (m[6] * b.m[9]) + (m[7] * b.m[13]);
  this->m[6] = (m[4] * b.m[2]) + (m[5] * b.m[6]) + (m[6] * b.m[10]) + (m[7] * b.m[14]);
  this->m[7] = (m[4] * b.m[3]) + (m[5] * b.m[7]) + (m[6] * b.m[11]) + (m[7] * b.m[15]);

  this->m[8] = (m[8] * b.m[0]) + (m[9] * b.m[4]) + (m[10] * b.m[8]) + (m[11] * b.m[12]);
  this->m[9] = (m[8] * b.m[1]) + (m[9] * b.m[5]) + (m[10] * b.m[9]) + (m[11] * b.m[13]);
  this->m[10] = (m[8] * b.m[2]) + (m[9] * b.m[6]) + (m[10] * b.m[10]) + (m[11] * b.m[14]);
  this->m[11] = (m[8] * b.m[3]) + (m[9] * b.m[7]) + (m[10] * b.m[11]) + (m[11] * b.m[15]);

  this->m[12] = (m[12] * b.m[0]) + (m[13] * b.m[4]) + (m[14] * b.m[8]) + (m[15] * b.m[12]);
  this->m[13] = (m[12] * b.m[1]) + (m[13] * b.m[5]) + (m[14] * b.m[9]) + (m[15] * b.m[13]);
  this->m[14] = (m[12] * b.m[2]) + (m[13] * b.m[6]) + (m[14] * b.m[10]) + (m[15] * b.m[14]);
  this->m[15] = (m[12] * b.m[3]) + (m[13] * b.m[7]) + (m[14] * b.m[11]) + (m[15] * b.m[15]);

}

//---------------------------------------------------------------------------//

 void mathmorra::Matrix4::operator*=(float b) {

  for (int i = 0; i < 16; ++i) {
    this->m[i] *= b;
  }

}

//---------------------------------------------------------------------------//

 mathmorra::Matrix4 mathmorra::Matrix4::operator*(const Matrix4& b){

   Matrix4  result;

   result.m[0] = (m[0] * b.m[0]) + (m[1] * b.m[4]) + (m[2] * b.m[8]) + (m[3] * b.m[12]);
   result.m[1] = (m[0] * b.m[1]) + (m[1] * b.m[5]) + (m[2] * b.m[9]) + (m[3] * b.m[13]);
   result.m[2] = (m[0] * b.m[2]) + (m[1] * b.m[6]) + (m[2] * b.m[10]) + (m[3] * b.m[14]);
   result.m[3] = (m[0] * b.m[3]) + (m[1] * b.m[7]) + (m[2] * b.m[11]) + (m[3] * b.m[15]);

   result.m[4] = (m[4] * b.m[0]) + (m[5] * b.m[4]) + (m[6] * b.m[8]) + (m[7] * b.m[12]);
   result.m[5] = (m[4] * b.m[1]) + (m[5] * b.m[5]) + (m[6] * b.m[9]) + (m[7] * b.m[13]);
   result.m[6] = (m[4] * b.m[2]) + (m[5] * b.m[6]) + (m[6] * b.m[10]) + (m[7] * b.m[14]);
   result.m[7] = (m[4] * b.m[3]) + (m[5] * b.m[7]) + (m[6] * b.m[11]) + (m[7] * b.m[15]);

   result.m[8] = (m[8] * b.m[0]) + (m[9] * b.m[4]) + (m[10] * b.m[8]) + (m[11] * b.m[12]);
   result.m[9] = (m[8] * b.m[1]) + (m[9] * b.m[5]) + (m[10] * b.m[9]) + (m[11] * b.m[13]);
   result.m[10] = (m[8] * b.m[2]) + (m[9] * b.m[6]) + (m[10] * b.m[10]) + (m[11] * b.m[14]);
   result.m[11] = (m[8] * b.m[3]) + (m[9] * b.m[7]) + (m[10] * b.m[11]) + (m[11] * b.m[15]);

   result.m[12] = (m[12] * b.m[0]) + (m[13] * b.m[4]) + (m[14] * b.m[8]) + (m[15] * b.m[12]);
   result.m[13] = (m[12] * b.m[1]) + (m[13] * b.m[5]) + (m[14] * b.m[9]) + (m[15] * b.m[13]);
   result.m[14] = (m[12] * b.m[2]) + (m[13] * b.m[6]) + (m[14] * b.m[10]) + (m[15] * b.m[14]);
   result.m[15] = (m[12] * b.m[3]) + (m[13] * b.m[7]) + (m[14] * b.m[11]) + (m[15] * b.m[15]);

   return result;

 }

//---------------------------------------------------------------------------//

 mathmorra::Matrix4 mathmorra::Matrix4::operator*(float b) const {

  Matrix4  result = { 0.0f };

  for (int i = 0; i < 16; ++i) {
    result.m[i] = (this->m[i] * b);
  }

  return result;

}

//---------------------------------------------------------------------------//

 void mathmorra::Matrix4::operator/=(float b) {

  for (int i = 0; i < 16; ++i) {
    this->m[i] /= b;
  }

}

//---------------------------------------------------------------------------//

 mathmorra::Matrix4 mathmorra::Matrix4::operator/(float b) const {

  Matrix4  result = { 0.0f };
  float inverted_b = 1.0f / b;

  for (int i = 0; i < 16; ++i) {
    result.m[i] = (this->m[i] * inverted_b);
  }

  return result;

}

//---------------------------------------------------------------------------//

 bool mathmorra::Matrix4::operator==(const mathmorra::Matrix4 & b) {

  for (int i = 0; i < 16; ++i) {
    if (this->m[i] != b.m[i]) {
      return false;
    };
  }

  return true;
}

//---------------------------------------------------------------------------//

 bool mathmorra::Matrix4::operator!=(const mathmorra::Matrix4 & b) {

  for (int i = 0; i < 16; ++i) {
    if (this->m[i] != b.m[i]) {
      return true;
    };
  }

  return false;
}

//---------------------------------------------------------------------------//

 void mathmorra::Matrix4::operator=(const mathmorra::Matrix4 & b) {

  for (int i = 0; i < 16; ++i) {
    this->m[i] = b.m[i];
  }

}

//---------------------------------------------------------------------------//

 mathmorra::Vector3 mathmorra::Matrix4::operator*(mathmorra::Vector3 scalar) const {

  Vector3 result;

  result.x_ = (scalar.x_ * this->m[0]) + (scalar.y_ * this->m[1]) + (scalar.z_ * this->m[2]) + this->m[3];
  result.y_ = (scalar.x_ * this->m[4]) + (scalar.y_ * this->m[5]) + (scalar.z_ * this->m[6]) + this->m[7];
  result.z_ = (scalar.x_ * this->m[8]) + (scalar.y_ * this->m[9]) + (scalar.z_ * this->m[10]) + this->m[11];

  return result;

}

//---------------------------------------------------------------------------//


 mathmorra::Vector4 mathmorra::Matrix4::operator*(mathmorra::Vector4 scalar) const {

  Vector4 result;

  result.x_ = ((this->m[0] * scalar.x_) + (this->m[1] * scalar.y_) + (this->m[2] * scalar.z_) + (this->m[3] * scalar.w_));
  result.y_ = ((this->m[4] * scalar.x_) + (this->m[5] * scalar.y_) + (this->m[6] * scalar.z_) + (this->m[7] * scalar.w_));
  result.z_ = ((this->m[8] * scalar.x_) + (this->m[9] * scalar.y_) + (this->m[10] * scalar.z_) + (this->m[11] * scalar.w_));
  result.w_ = ((this->m[12] * scalar.x_) + (this->m[13] * scalar.y_) + (this->m[14] * scalar.z_) + (this->m[15] * scalar.w_));

  float inverted_w = 1.0f / result.w_;

  result.x_ *= inverted_w;
  result.y_ *= inverted_w;
  result.z_ *= inverted_w;
  result.w_ *= inverted_w;


  return result;

}

//---------------------------------------------------------------------------//

/*
  * @brief    This is a matrix that effectively does nothing when applied.
  *           It has 1s in the main diagonal and 0s in all other elements
  * @return   The identity 4x4 Matrix
*/


 mathmorra::Matrix4  mathmorra::Matrix4::Identity(){

  Matrix4  identity;

  identity.m[0] = 1.0f;
  identity.m[5] = 1.0f;
  identity.m[10] = 1.0f;
  identity.m[15] = 1.0f;

  return identity;
}

//---------------------------------------------------------------------------//

 mathmorra::Matrix4 mathmorra::Matrix4::Zero(){

   Matrix4 result;

   for (int i = 0; i < 16; ++i) {
     result.m[i] = 0.0f;
   }

   return result;

 }

//---------------------------------------------------------------------------//

/*
  * @brief    Multiplies two matrices.
  * @param    The other matrix to multiply.
  * @return   The result of this multiplication.
*/

 mathmorra::Matrix4 mathmorra::Matrix4::Multiply(const mathmorra::Matrix4 & b) const {

  Matrix4  result;

  result.m[0] = (m[0] * b.m[0]) + (m[1] * b.m[4]) + (m[2] * b.m[8]) + (m[3] * b.m[12]);
  result.m[1] = (m[0] * b.m[1]) + (m[1] * b.m[5]) + (m[2] * b.m[9]) + (m[3] * b.m[13]);
  result.m[2] = (m[0] * b.m[2]) + (m[1] * b.m[6]) + (m[2] * b.m[10]) + (m[3] * b.m[14]);
  result.m[3] = (m[0] * b.m[3]) + (m[1] * b.m[7]) + (m[2] * b.m[11]) + (m[3] * b.m[15]);

  result.m[4] = (m[4] * b.m[0]) + (m[5] * b.m[4]) + (m[6] * b.m[8]) + (m[7] * b.m[12]);
  result.m[5] = (m[4] * b.m[1]) + (m[5] * b.m[5]) + (m[6] * b.m[9]) + (m[7] * b.m[13]);
  result.m[6] = (m[4] * b.m[2]) + (m[5] * b.m[6]) + (m[6] * b.m[10]) + (m[7] * b.m[14]);
  result.m[7] = (m[4] * b.m[3]) + (m[5] * b.m[7]) + (m[6] * b.m[11]) + (m[7] * b.m[15]);

  result.m[8] = (m[8] * b.m[0]) + (m[9] * b.m[4]) + (m[10] * b.m[8]) + (m[11] * b.m[12]);
  result.m[9] = (m[8] * b.m[1]) + (m[9] * b.m[5]) + (m[10] * b.m[9]) + (m[11] * b.m[13]);
  result.m[10] = (m[8] * b.m[2]) + (m[9] * b.m[6]) + (m[10] * b.m[10]) + (m[11] * b.m[14]);
  result.m[11] = (m[8] * b.m[3]) + (m[9] * b.m[7]) + (m[10] * b.m[11]) + (m[11] * b.m[15]);

  result.m[12] = (m[12] * b.m[0]) + (m[13] * b.m[4]) + (m[14] * b.m[8]) + (m[15] * b.m[12]);
  result.m[13] = (m[12] * b.m[1]) + (m[13] * b.m[5]) + (m[14] * b.m[9]) + (m[15] * b.m[13]);
  result.m[14] = (m[12] * b.m[2]) + (m[13] * b.m[6]) + (m[14] * b.m[10]) + (m[15] * b.m[14]);
  result.m[15] = (m[12] * b.m[3]) + (m[13] * b.m[7]) + (m[14] * b.m[11]) + (m[15] * b.m[15]);

  return result;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Creates a translation Matrix.
  * @param    The vector to create the Matrix.
  * @return   Translate 4x4 Matrix.
*/

 mathmorra::Matrix4  mathmorra::Matrix4::Translate(const mathmorra::Vector3& mov_vector) {

  Matrix4  result = result.Identity();

  result.m[12] = mov_vector.x_;
  result.m[13] = mov_vector.y_;
  result.m[14] = mov_vector.z_;

  return result;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Creates a translation Matrix.
  * @param    Three floats, x, y, z (position on the axis).
  * @return   Translate 4x4 Matrix.
*/

 mathmorra::Matrix4  mathmorra::Matrix4::Translate(float x, float y, float z) {

  Matrix4  result = result.Identity();

  result.m[12] = x;
  result.m[13] = y;
  result.m[14] = z;

  return result;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Creates a perspective projection matrix.
  * @param    "fov" is the vertical field-of-view in degrees of
              the perspective matrix,
  *           "aspect" is the aspect ratio (width divided by height).
  *           "near" and "far" set up the depth clipping planes.
  * @return   Perspective 4x4 Matrix.
*/

 mathmorra::Matrix4  mathmorra::Matrix4::PerspectiveMatrix(float fov, float aspect,
  float near, float far) const {

   float cotangent = 1.0f / tan(fov * 0.5f);
   float rcpdz = 1.0f / (near - far);

   Vector4 a(cotangent / aspect, 0.0f, 0.0f, 0.0f);
   Vector4 b(0.0f, cotangent, 0.0f, 0.0f);
   Vector4 c(0.0f, 0.0f, (far + near) * rcpdz, 2.0f * near * far * rcpdz);
   Vector4 d(0.0f, 0.0f, -1.0f, 0.0f);

   return Matrix4( a, b, c, d );

}

//---------------------------------------------------------------------------//

/*
  * @brief    Creates an orthogonal projection matrix.
  * @param    The returned matrix, when used as a Camera's projection matrix,
  *           creates a view showing the area between left, right, top and bottom,
  *           with zNear and zFar as the near and far depth clipping planes.
  * @return   Orthogonal 4x4 Matrix.
*/

 mathmorra::Matrix4  mathmorra::Matrix4::OrthoMatrix(float width, float height, float near, float far) const {

   float rcpdx = 1.0f / width;
   float rcpdy = 1.0f / height;
   float rcpdz = 1.0f / (far - near);

   Vector4 a(2.0f * rcpdx, 0.0f, 0.0f, 0.0f);
   Vector4 b(0.0f, 2.0f * rcpdy, 0.0f, 0.0f);
   Vector4 c(0.0f, 0.0f, -2.0f * rcpdz, -(far + near) * rcpdz);
   Vector4 d(0.0f, 0.0f, 0.0f, 1.0f);

   return Matrix4( a, b, c, d );

}

//---------------------------------------------------------------------------//

/*
  * @brief    The determinant of the matrix.
  * @return   Determinant.
*/

 float mathmorra::Matrix4::Determinant() const {

  Matrix4  matrix;
  float determinant;

  matrix = this->Adjoint();
  matrix = matrix.Transpose();

  determinant = m[0] * matrix.m[0] +
    m[1] * matrix.m[4] +
    m[2] * matrix.m[8] +
    m[3] * matrix.m[12];

  return determinant;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Calculate the adjoint matrix.
  * @return   the adjoint matrix.
*/

 mathmorra::Matrix4  mathmorra::Matrix4::Adjoint() const {

  Matrix4  matrix;

  matrix.m[0] = m[5] * m[10] * m[15] -
                m[5] * m[11] * m[14] -
                m[9] * m[6] * m[15] +
                m[9] * m[7] * m[14] +
                m[13] * m[6] * m[11] -
                m[13] * m[7] * m[10];

  matrix.m[1] = -m[1] * m[10] * m[15] +
    m[1] * m[11] * m[14] +
    m[9] * m[2] * m[15] -
    m[9] * m[3] * m[14] -
    m[13] * m[2] * m[11] +
    m[13] * m[3] * m[10];

  matrix.m[2] = m[1] * m[6] * m[15] -
    m[1] * m[7] * m[14] -
    m[5] * m[2] * m[15] +
    m[5] * m[3] * m[14] +
    m[13] * m[2] * m[7] -
    m[13] * m[3] * m[6];

  matrix.m[3] = -m[1] * m[6] * m[11] +
    m[1] * m[7] * m[10] +
    m[5] * m[2] * m[11] -
    m[5] * m[3] * m[10] -
    m[9] * m[2] * m[7] +
    m[9] * m[3] * m[6];

  matrix.m[4] = -m[4] * m[10] * m[15] +
    m[4] * m[11] * m[14] +
    m[8] * m[6] * m[15] -
    m[8] * m[7] * m[14] -
    m[12] * m[6] * m[11] +
    m[12] * m[7] * m[10];

  matrix.m[5] = m[0] * m[10] * m[15] -
    m[0] * m[11] * m[14] -
    m[8] * m[2] * m[15] +
    m[8] * m[3] * m[14] +
    m[12] * m[2] * m[11] -
    m[12] * m[3] * m[10];

  matrix.m[6] = -m[0] * m[6] * m[15] +
    m[0] * m[7] * m[14] +
    m[4] * m[2] * m[15] -
    m[4] * m[3] * m[14] -
    m[12] * m[2] * m[7] +
    m[12] * m[3] * m[6];

  matrix.m[7] = m[0] * m[6] * m[11] -
    m[0] * m[7] * m[10] -
    m[4] * m[2] * m[11] +
    m[4] * m[3] * m[10] +
    m[8] * m[2] * m[7] -
    m[8] * m[3] * m[6];

  matrix.m[8] = m[4] * m[9] * m[15] -
    m[4] * m[11] * m[13] -
    m[8] * m[5] * m[15] +
    m[8] * m[7] * m[13] +
    m[12] * m[5] * m[11] -
    m[12] * m[7] * m[9];

  matrix.m[9] = -m[0] * m[9] * m[15] +
    m[0] * m[11] * m[13] +
    m[8] * m[1] * m[15] -
    m[8] * m[3] * m[13] -
    m[12] * m[1] * m[11] +
    m[12] * m[3] * m[9];

  matrix.m[10] = m[0] * m[5] * m[15] -
    m[0] * m[7] * m[13] -
    m[4] * m[1] * m[15] +
    m[4] * m[3] * m[13] +
    m[12] * m[1] * m[7] -
    m[12] * m[3] * m[5];

  matrix.m[11] = -m[0] * m[5] * m[11] +
    m[0] * m[7] * m[9] +
    m[4] * m[1] * m[11] -
    m[4] * m[3] * m[9] -
    m[8] * m[1] * m[7] +
    m[8] * m[3] * m[5];

  matrix.m[12] = -m[4] * m[9] * m[14] +
    m[4] * m[10] * m[13] +
    m[8] * m[5] * m[14] -
    m[8] * m[6] * m[13] -
    m[12] * m[5] * m[10] +
    m[12] * m[6] * m[9];

  matrix.m[13] = m[0] * m[9] * m[14] -
    m[0] * m[10] * m[13] -
    m[8] * m[1] * m[14] +
    m[8] * m[2] * m[13] +
    m[12] * m[1] * m[10] -
    m[12] * m[2] * m[9];

  matrix.m[14] = -m[0] * m[5] * m[14] +
    m[0] * m[6] * m[13] +
    m[4] * m[1] * m[14] -
    m[4] * m[2] * m[13] -
    m[12] * m[1] * m[6] +
    m[12] * m[2] * m[5];

  matrix.m[15] = m[0] * m[5] * m[10] -
    m[0] * m[6] * m[9] -
    m[4] * m[1] * m[10] +
    m[4] * m[2] * m[9] +
    m[8] * m[1] * m[6] -
    m[8] * m[2] * m[5];

  matrix = matrix.Transpose();

  return matrix;
}

//---------------------------------------------------------------------------//

bool mathmorra::Matrix4::IsIdentity(){

  return (this->m[0]  == 1.0f &&
          this->m[5]  == 1.0f &&
          this->m[10] == 1.0f &&
          this->m[15] == 1.0f);

}

//---------------------------------------------------------------------------//

/*
  * @brief    Calculate if its possible calculate the inverse of the matrix.
  * @return   Change the original matrix to its inverse.
*/

 bool mathmorra::Matrix4::Inverse() {

  Matrix4  matrix;
  float determinant;

  matrix = this->Adjoint();
  matrix = matrix.Transpose();
  determinant = this->Determinant();

  //We make sure that determinant != 0
  if (determinant == 0) return false;

  //Get determinant = 1.0f / determinant
  determinant = powf(determinant, -1.0f);

  //Getting the inverse matrix
  for (int i = 0; i < 16; ++i) {
    this->m[i] = matrix.m[i] * determinant;
  }

  return true;
}

//---------------------------------------------------------------------------//

/*
  * @brief    Calculate if its possible calculate the inverse of the matrix.
  * @return   Change the original matrix to its inverse.
*/

 mathmorra::Matrix4  mathmorra::Matrix4::Scale(const mathmorra::Vector3& scale_vector) {

  Matrix4  result;

  result.m[0] = scale_vector.x_;
  result.m[5] = scale_vector.y_;
  result.m[10] = scale_vector.z_;
  result.m[15] = 1.0f;

  return result;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Creates a Scale Matrix.
  * @param    Three floats.
  * @return   Scale 4x4 Matrix.
*/

 mathmorra::Matrix4 mathmorra::Matrix4::Scale(float x, float y, float z) {

  Matrix4  result;

  result = result.Identity();
  result.m[0] = x;
  result.m[5] = y;
  result.m[10] = z;

  return result;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Creates a Rotate Matrix on the X axis.
  * @param    The angle (in radians) to rotate.
  * @return   Rotate X 4x4 Matrix.
*/

 mathmorra::Matrix4 mathmorra::Matrix4::RotateX(float angle) {

  Matrix4  result;

  result.m[0] = 1.0f;
  result.m[5] = cos(angle);
  result.m[6] = -sin(angle);
  result.m[9] = sin(angle);
  result.m[10] = cos(angle);
  result.m[15] = 1.0f;

  return result;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Creates a Rotate Matrix on the Y axis.
  * @param    The angle (in radians) to rotate.
  * @return   Rotate Y 4x4 Matrix.
*/

 mathmorra::Matrix4 mathmorra::Matrix4::RotateY(float angle) {

  Matrix4  result = { 0.0f };

  result = result.Identity();
  result.m[0] = cos(angle);
  result.m[2] = sin(angle);
  result.m[8] = -sin(angle);
  result.m[10] = cos(angle);


  return result;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Creates a Rotate Matrix on the Z axis.
  * @param    The angle (in radians) to rotate.
  * @return   Rotate Z 4x4 Matrix.
*/

 mathmorra::Matrix4 mathmorra::Matrix4::RotateZ(float angle) {

  Matrix4  result;

  result = result.Identity();
  result.m[0] = cos(angle);
  result.m[1] = -sin(angle);
  result.m[4] = sin(angle);
  result.m[5] = cos(angle);

  return result;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Get the line passed by param.
  * @param    The line to get.
  * @return   The line on a Vector4.
*/

 mathmorra::Vector4 mathmorra::Matrix4::GetLine(int line) const {

  Vector4 vec = { 0.0f };

  //We make sure that we do not put a value that leaves the array
  if (line > 3 || line < 0) return vec;

  int row = line * 4;

  vec.x_ = m[row];
  vec.y_ = m[row + 1];
  vec.z_ = m[row + 2];
  vec.w_ = m[row + 3];

  return vec;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Get the column passed by param.
  * @param    The column to get.
  * @return   The column on a Vector4.
*/

 mathmorra::Vector4 mathmorra::Matrix4::GetColum(int colum) const {

  Vector4 vec = { 0.0f };

  //We make sure that we do not put a value that leaves the array
  if (colum > 3 || colum < 0) return vec;

  vec.x_ = m[colum];
  vec.y_ = m[colum + 4];
  vec.z_ = m[colum + 8];
  vec.w_ = m[colum + 12];

  return vec;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Set the line passed by param in the Matrix.
  * @param    Values to set in the Matrix on a Vector4.
  * @param    The line to set.
*/


 void mathmorra::Matrix4::SetRow(const mathmorra::Vector4& a, int row) {

  //We make sure that we do not put a value that leaves the array
  if (row < 3 && row > 0) {

    int line = row * 4;

    this->m[line] = a.x_;
    this->m[line + 1] = a.y_;
    this->m[line + 2] = a.z_;
    this->m[line + 3] = a.w_;

  }

}

//---------------------------------------------------------------------------//

/*
  * @brief    Set the column passed by param in the Matrix.
  * @param    Values to set in the Matrix on a Vector4.
  * @param    The column to set.
*/

 void mathmorra::Matrix4::SetColum(const mathmorra::Vector4& a, int colum) {

  //We make sure that we do not put a value that leaves the array
  //Make ASSERT
  if (colum < 3 && colum > 0) {

    this->m[colum] = a.x_;
    this->m[colum + 1] = a.y_;
    this->m[colum + 2] = a.z_;
    this->m[colum + 3] = a.w_;

  }

}

//---------------------------------------------------------------------------//

/*
  * @brief    Calculate the transpose of this matrix.
  * @param    Returns the transpose of this matrix (Read Only).
*/

 mathmorra::Matrix4  mathmorra::Matrix4::Transpose() const {

  Matrix4  result;

  result.m[0] = m[0];
  result.m[1] = m[4];
  result.m[2] = m[8];
  result.m[3] = m[12];

  result.m[4] = m[1];
  result.m[5] = m[5];
  result.m[6] = m[9];
  result.m[7] = m[13];

  result.m[8] = m[2];
  result.m[9] = m[6];
  result.m[10] = m[10];
  result.m[11] = m[14];

  result.m[12] = m[3];
  result.m[13] = m[7];
  result.m[14] = m[11];
  result.m[15] = m[15];

  return result;

}


 mathmorra::Matrix4 mathmorra::Matrix4::LookAt(mathmorra::Vector3 eye, 
                                               mathmorra::Vector3 target, 
                                               mathmorra::Vector3 up){

   Matrix3 rot = Matrix3::LookRotation(Vector3::Normalized(target - eye), up);

   Matrix4 matrix;
   Vector4 column_0 = { rot.GetColum(0).x_,
                        rot.GetColum(0).y_,
                        rot.GetColum(0).z_,
                        0.0f };

   Vector4 column_1 = { rot.GetColum(1).x_,
                        rot.GetColum(1).y_,
                        rot.GetColum(1).z_,
                        0.0f };

   Vector4 column_2 = { rot.GetColum(2).x_,
                        rot.GetColum(2).y_,
                        rot.GetColum(2).z_,
                        0.0f };

   Vector4 eye_4 = { eye.x_,
                     eye.y_,
                     eye.z_,
                     1.0f };

   matrix.SetColum(column_0, 0);
   matrix.SetColum(column_1, 1);
   matrix.SetColum(column_2, 2);
   matrix.SetColum(eye_4, 3);

   return matrix;

 }

//---------------------------------------------------------------------------//

/*
  * @brief    Calculate if its possible to invert the matrix passed by parameter.
*/

 bool mathmorra::Matrix4::GetInverse(Matrix4 * out) const {

  Matrix4  matrix;
  float determinant;

  matrix = this->Adjoint();
  matrix = matrix.Transpose();
  determinant = this->Determinant();

  if (determinant == 0) return false;

  determinant = 1.0 / determinant;

  for (int i = 0; i < 16; i++) {
    out->m[i] = matrix.m[i] * determinant;
  }

  return true;

}

//---------------------------------------------------------------------------//

/*
  * @brief    Calculate if its possible to invert the matrix passed by parameter.
*/

 mathmorra::Matrix4  mathmorra::Matrix4::GetTransform(const mathmorra::Vector3& translate,
  const Vector3& scale,
  float rotateX, float rotateY,
  float rotateZ) {

  Matrix4  result = result.Identity();

  //Translate
  result = result.Multiply(Translate(translate));

  //Rotate
  result = result.Multiply(RotateX(rotateX));
  result = result.Multiply(RotateY(rotateY));
  result = result.Multiply(RotateZ(rotateZ));

  //Scale
  result = result.Multiply(Scale(scale));


  return result;
}

//---------------------------------------------------------------------------//

 mathmorra::Matrix4 mathmorra::Matrix4::GetTransform(float trans_x, float trans_y, float trans_z,
  float scale_x, float scale_y, float scale_z,
  float rotateX, float rotateY, float rotateZ) {


   mathmorra::Matrix4  result = result.Identity();
   mathmorra::Vector3 scale = { scale_x, scale_y, scale_z };
  mathmorra::Vector3 translate = { trans_x, trans_y, trans_z };

  //Translate
  result = result.Multiply(Translate(translate));

  //Rotate
  result = result.Multiply(RotateX(rotateX));
  result = result.Multiply(RotateY(rotateY));
  result = result.Multiply(RotateZ(rotateZ));

  //Scale
  result = result.Multiply(Scale(scale));



  return result;
}

//---------------------------------------------------------------------------//