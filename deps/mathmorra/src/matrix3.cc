/*
Author: Adrian Garvia Arrogante <adriangarviasmr@gmail.com>
--Revision 10-02-2019 - Pablo Bano Benito <pablo.bano.benito@gmail.com>
Date: 02-01-2019
Matrix3
*/

#include "Matrix3.h"
#include "Vector3.h"
#include "math.h"

//---------------------------------------------------------------------------//

mathmorra::Matrix3::Matrix3(){

  this->m[0] = 0.0f;
  this->m[1] = 0.0f;
  this->m[2] = 0.0f;
  this->m[3] = 0.0f;
  this->m[4] = 0.0f;
  this->m[5] = 0.0f;
  this->m[6] = 0.0f;
  this->m[7] = 0.0f;
  this->m[8] = 0.0f;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3::Matrix3(float *a){

  this->m[0] = a[0];
  this->m[1] = a[1];
  this->m[2] = a[2];
  this->m[3] = a[3];
  this->m[4] = a[4];
  this->m[5] = a[5];
  this->m[6] = a[6];
  this->m[7] = a[7];
  this->m[8] = a[8];

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3::Matrix3(float a){

  this->m[0] = a;
  this->m[1] = a;
  this->m[2] = a;
  this->m[3] = a;
  this->m[4] = a;
  this->m[5] = a;
  this->m[6] = a;
  this->m[7] = a;
  this->m[8] = a;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3::Matrix3(mathmorra::Vector3 a, 
                            mathmorra::Vector3 b,
                            mathmorra::Vector3 c){

  this->m[0] = a.x_;
  this->m[1] = a.y_;
  this->m[2] = a.z_;
  this->m[3] = b.x_;
  this->m[4] = b.y_;
  this->m[5] = b.z_;
  this->m[6] = c.x_;
  this->m[7] = c.y_;
  this->m[8] = c.z_;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3::Matrix3(const Matrix3& copy){

  this->m[0] = copy.m[0];
  this->m[1] = copy.m[1];
  this->m[2] = copy.m[2];
  this->m[3] = copy.m[3];
  this->m[4] = copy.m[4];
  this->m[5] = copy.m[5];
  this->m[6] = copy.m[6];
  this->m[7] = copy.m[7];
  this->m[8] = copy.m[8];

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3::~Matrix3() {

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::Identity(){

  mathmorra::Matrix3 identity;

  identity.m[0] = 1.0f;
  identity.m[4] = 1.0f;
  identity.m[8] = 1.0f;

  return identity;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::Multiply(const mathmorra::Matrix3& b) const{
  
  mathmorra::Matrix3 result;

  result.m[0] = (m[0] * b.m[0]) + (m[1] * b.m[3]) + (m[2] * b.m[6]);
  result.m[1] = (m[0] * b.m[1]) + (m[1] * b.m[4]) + (m[2] * b.m[7]);
  result.m[2] = (m[0] * b.m[2]) + (m[1] * b.m[5]) + (m[2] * b.m[8]);
  result.m[3] = (m[3] * b.m[0]) + (m[4] * b.m[3]) + (m[5] * b.m[6]);
  result.m[4] = (m[3] * b.m[1]) + (m[4] * b.m[4]) + (m[5] * b.m[7]);
  result.m[5] = (m[3] * b.m[2]) + (m[4] * b.m[5]) + (m[5] * b.m[8]);
  result.m[6] = (m[6] * b.m[0]) + (m[7] * b.m[3]) + (m[8] * b.m[6]);
  result.m[7] = (m[6] * b.m[1]) + (m[7] * b.m[4]) + (m[8] * b.m[7]);
  result.m[8] = (m[6] * b.m[2]) + (m[7] * b.m[5]) + (m[8] * b.m[8]);

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Matrix3::operator*(Vector3 scalar) const {

  mathmorra::Vector3 result;

  for (int i = 0; i < 9; i += 3) {
    if (i < 2) result.x_ =           ((this->m[i] * scalar.x_) + (this->m[i + 1] * scalar.y_) + (this->m[i + 2] * scalar.z_));
    if (i >= 2 && i < 5) result.y_ = ((this->m[i] * scalar.x_) + (this->m[i + 1] * scalar.y_) + (this->m[i + 2] * scalar.z_));
    if (i >= 5 && i < 8) result.z_ = ((this->m[i] * scalar.x_) + (this->m[i + 1] * scalar.y_) + (this->m[i + 2] * scalar.z_));
  }

  return result;

}

//---------------------------------------------------------------------------//

float mathmorra::Matrix3::Determinant() const{

  float t1;
  float t2;

  t1 = (m[0] * m[4] * m[8]) + (m[1] * m[5] * m[6]) + (m[3] * m[2] * m[7]);
  t2 = (m[2] * m[4] * m[6]) + (m[0] * m[5] * m[7]) + (m[1] * m[3] * m[8]);

  return t1 - t2;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::Adjoint() const{

  mathmorra::Matrix3 matrix;

  matrix.m[0] = m[4] * m[8] -
                m[7] * m[5];

  matrix.m[3] = m[6] * m[5] -
                m[3] * m[8];

  matrix.m[6] = m[3] * m[7] -
                m[6] * m[4];

  matrix.m[1] = m[7] * m[2] -
                m[1] * m[8];

  matrix.m[4] = m[0] * m[8] -
                m[6] * m[2];

  matrix.m[7] = m[6] * m[1] -
                m[0] * m[7];

  matrix.m[2] = m[1] * m[5] -
                m[4] * m[2];

  matrix.m[5] = m[3] * m[2] -
                m[0] * m[5];

  matrix.m[8] = m[0] * m[4] -
                m[3] * m[1];


  return matrix;

}

//---------------------------------------------------------------------------//

bool mathmorra::Matrix3::GetInverse(mathmorra::Matrix3* out) const{

    return out->Inverse();

}

//---------------------------------------------------------------------------//

bool mathmorra::Matrix3::Inverse(){
  float determinant;
  determinant = Determinant();
  if (determinant != 0.0f) {
    *this = Adjoint().Transpose();
    *this *= (1.0f / determinant);
  }
  return determinant != 0;
}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::Transpose() const{

  mathmorra::Matrix3 result;

  result.m[0] = m[0];
  result.m[1] = m[3];
  result.m[2] = m[6];
  result.m[3] = m[1];
  result.m[4] = m[4];
  result.m[5] = m[7];
  result.m[6] = m[2];
  result.m[7] = m[5];
  result.m[8] = m[8];

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::LookRotation(Vector3 forward, Vector3 up){

  Vector3 t = t.Normalized(Vector3::CrossProduct(up, forward));
  return Matrix3(t, Vector3::CrossProduct(forward, t), forward);

}

//---------------------------------------------------------------------------//

/*static mathmorra::Matrix3 Translate(const mathmorra::Vector2& position){
  mathmorra::Matrix3 translate_matrix = mathmorra::Matrix3();
  translate_matrix = mathmorra::Matrix3::Identity();
  translate_matrix.m[6] = position.x;
  translate_matrix.m[7] = position.y;
  return translate_matrix;
}*/

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::Translate(float x, float y){

  mathmorra::Matrix3 translate_matrix;

  translate_matrix = Identity();
  translate_matrix.m[6] = x;
  translate_matrix.m[7] = y;

  return translate_matrix;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Matrix3::GetColum(int colum) const{

  mathmorra::Vector3 result_colum;

  result_colum.x_ = m[colum];
  result_colum.y_ = m[colum + 3];
  result_colum.z_ = m[colum + 6];

  return result_colum;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Matrix3::GetLine(int line) const{

  mathmorra::Vector3 result_line;

  line *= 3;
  result_line.x_ = m[line];
  result_line.y_ = m[line + 1];
  result_line.z_ = m[line + 2];

  return result_line;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::operator+(const mathmorra::Matrix3& b) const{

  mathmorra::Matrix3 result;

  result.m[0] = m[0] + b.m[0];
  result.m[1] = m[1] + b.m[1];
  result.m[2] = m[2] + b.m[2];
  result.m[3] = m[3] + b.m[3];
  result.m[4] = m[4] + b.m[4];
  result.m[5] = m[5] + b.m[5];
  result.m[6] = m[6] + b.m[6];
  result.m[7] = m[7] + b.m[7];
  result.m[8] = m[8] + b.m[8];

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Matrix3::operator+=(const mathmorra::Matrix3& b){

  m[0] += b.m[0];
  m[1] += b.m[1];
  m[2] += b.m[2];
  m[3] += b.m[3];
  m[4] += b.m[4];
  m[5] += b.m[5];
  m[6] += b.m[6];
  m[7] += b.m[7];
  m[8] += b.m[8];

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::operator+(float b) const{

  mathmorra::Matrix3 result;

  result.m[0] = m[0] + b;
  result.m[1] = m[1] + b;
  result.m[2] = m[2] + b;
  result.m[3] = m[3] + b;
  result.m[4] = m[4] + b;
  result.m[5] = m[5] + b;
  result.m[6] = m[6] + b;
  result.m[7] = m[7] + b;
  result.m[8] = m[8] + b;

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Matrix3::operator+=(float b){

  m[0] += b;
  m[1] += b;
  m[2] += b;
  m[3] += b;
  m[4] += b;
  m[5] += b;
  m[6] += b;
  m[7] += b;
  m[8] += b;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::operator-(const mathmorra::Matrix3& b) const{

  mathmorra::Matrix3 result;

  result.m[0] = m[0] - b.m[0];
  result.m[1] = m[1] - b.m[1];
  result.m[2] = m[2] - b.m[2];
  result.m[3] = m[3] - b.m[3];
  result.m[4] = m[4] - b.m[4];
  result.m[5] = m[5] - b.m[5];
  result.m[6] = m[6] - b.m[6];
  result.m[7] = m[7] - b.m[7];
  result.m[8] = m[8] - b.m[8];

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Matrix3::operator-=(const mathmorra::Matrix3& b){

  m[0] -= b.m[0];
  m[1] -= b.m[1];
  m[2] -= b.m[2];
  m[3] -= b.m[3];
  m[4] -= b.m[4];
  m[5] -= b.m[5];
  m[6] -= b.m[6];
  m[7] -= b.m[7];
  m[8] -= b.m[8];

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::operator-(float b) const{

  mathmorra::Matrix3 result;

  result.m[0] = m[0] - b;
  result.m[1] = m[1] - b;
  result.m[2] = m[2] - b;
  result.m[3] = m[3] - b;
  result.m[4] = m[4] - b;
  result.m[5] = m[5] - b;
  result.m[6] = m[6] - b;
  result.m[7] = m[7] - b;
  result.m[8] = m[8] - b;

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Matrix3::operator-=(float b){

  m[0] -= b;
  m[1] -= b;
  m[2] -= b;
  m[3] -= b;
  m[4] -= b;
  m[5] -= b;
  m[6] -= b;
  m[7] -= b;
  m[8] -= b;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::operator*(float b) const{

  mathmorra::Matrix3 result;

  result.m[0] = m[0] * b;
  result.m[1] = m[1] * b;
  result.m[2] = m[2] * b;
  result.m[3] = m[3] * b;
  result.m[4] = m[4] * b;
  result.m[5] = m[5] * b;
  result.m[6] = m[6] * b;
  result.m[7] = m[7] * b;
  result.m[8] = m[8] * b;

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Matrix3::operator*=(float b){

  m[0] *= b;
  m[1] *= b;
  m[2] *= b;
  m[3] *= b;
  m[4] *= b;
  m[5] *= b;
  m[6] *= b;
  m[7] *= b;
  m[8] *= b;

}

//---------------------------------------------------------------------------//

mathmorra::Matrix3 mathmorra::Matrix3::operator/(float b) const{

  mathmorra::Matrix3 result;
  float inverted_b = 1.0f / b;

  result.m[0] = m[0] * inverted_b;
  result.m[1] = m[1] * inverted_b;
  result.m[2] = m[2] * inverted_b;
  result.m[3] = m[3] * inverted_b;
  result.m[4] = m[4] * inverted_b;
  result.m[5] = m[5] * inverted_b;
  result.m[6] = m[6] * inverted_b;
  result.m[7] = m[7] * inverted_b;
  result.m[8] = m[8] * inverted_b;

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Matrix3::operator/=(float b){

  float inverted_b = 1.0f / b;

  m[0] *= inverted_b;
  m[1] *= inverted_b;
  m[2] *= inverted_b;
  m[3] *= inverted_b;
  m[4] *= inverted_b;
  m[5] *= inverted_b;
  m[6] *= inverted_b;
  m[7] *= inverted_b;
  m[8] *= inverted_b;

}

//---------------------------------------------------------------------------//

bool mathmorra::Matrix3::operator==(const mathmorra::Matrix3& b) const{

  return m[0] == b.m[0] &&
         m[1] == b.m[1] &&
         m[2] == b.m[2] &&
         m[3] == b.m[3] &&
         m[4] == b.m[4] &&
         m[5] == b.m[5] &&
         m[6] == b.m[6] &&
         m[7] == b.m[7] &&
         m[8] == b.m[8];

}

//---------------------------------------------------------------------------//

bool mathmorra::Matrix3::operator!=(const mathmorra::Matrix3& b) const{

  return m[0] != b.m[0] &&
         m[1] != b.m[1] &&
         m[2] != b.m[2] &&
         m[3] != b.m[3] &&
         m[4] != b.m[4] &&
         m[5] != b.m[5] &&
         m[6] != b.m[6] &&
         m[7] != b.m[7] &&
         m[8] != b.m[8];

}

//---------------------------------------------------------------------------//

void mathmorra::Matrix3::operator=(const mathmorra::Matrix3& b){

  m[0] = b.m[0];
  m[1] = b.m[1];
  m[2] = b.m[2];
  m[3] = b.m[3];
  m[4] = b.m[4];
  m[5] = b.m[5];
  m[6] = b.m[6];
  m[7] = b.m[7];
  m[8] = b.m[8];

}

//---------------------------------------------------------------------------//