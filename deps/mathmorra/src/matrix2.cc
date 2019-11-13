/*
Author: Adrian Garvia Arrogante <adriangarviasmr@gmail.com>
Date: 17-02-2019
mathmorra::Matrix2
*/

#include "matrix2.h"

//---------------------------------------------------------------------------//

mathmorra::Matrix2::Matrix2() {
  m[0] = 0.0f;
  m[1] = 0.0f;
  m[2] = 0.0f;
  m[3] = 0.0f;
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2::Matrix2(float a[4]) {
  m[0] = a[0];
  m[1] = a[1];
  m[2] = a[2];
  m[3] = a[3];
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2::Matrix2(float a) {
  m[0] = a;
  m[1] = a;
  m[2] = a;
  m[3] = a;
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2::Matrix2(mathmorra::Vector2 a, mathmorra::Vector2 b) {
  m[0] = a.x_;
  m[1] = b.x_;
  m[2] = a.y_;
  m[3] = b.y_;
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2::Matrix2(const mathmorra::Matrix2& copy) {
  m[0] = copy.m[0];
  m[1] = copy.m[1];
  m[2] = copy.m[2];
  m[3] = copy.m[3];
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::Identity() const {
  mathmorra::Matrix2 identity = mathmorra::Matrix2();
  identity.m[0] = 1.0f;
  identity.m[1] = 0.0f;
  identity.m[2] = 0.0f;
  identity.m[3] = 1.0f;
  return identity;
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::Multiply(const mathmorra::Matrix2& b) const {
  mathmorra::Matrix2 result = mathmorra::Matrix2();
  result.m[0] = (m[0] * b.m[0]) + (m[1] * b.m[2]);
  result.m[1] = (m[0] * b.m[1]) + (m[1] * b.m[3]);
  result.m[2] = (m[2] * b.m[0]) + (m[3] * b.m[2]);
  result.m[3] = (m[2] * b.m[1]) + (m[3] * b.m[3]);
  return result;
}

//---------------------------------------------------------------------------//

float mathmorra::Matrix2::Determinant() const {
  return (m[0] * m[3]) - (m[1] * m[2]);
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::Adjoint() const {

  mathmorra::Matrix2 result;
  result.m[0] = m[3];
  result.m[1] = -m[2];
  result.m[2] = m[1];
  result.m[3] = -m[0];

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Matrix2::GetLine(int line) const {
  return mathmorra::Vector2(m[line * 2], m[(line * 2) + 1]);
}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Matrix2::GetColum(int line) const {
  return mathmorra::Vector2(m[line], m[line + 2]);
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::Inverse() const {

  float determinant = Determinant();

  if (determinant == 0) {
    return Identity();
  }

  return Adjoint() * (1.0f / determinant);
  
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::Transpose() const {
  mathmorra::Matrix2 result = mathmorra::Matrix2();
  result.m[0] = m[0];
  result.m[1] = m[2];
  result.m[2] = m[1];
  result.m[3] = m[3];
  return result;
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::operator+(const mathmorra::Matrix2& b) const {
  mathmorra::Matrix2 result = mathmorra::Matrix2();
  result = this->m[0] + b.m[0];
  result = this->m[1] + b.m[1];
  result = this->m[2] + b.m[2];
  result = this->m[3] + b.m[3];
  return result;
}

//---------------------------------------------------------------------------//

void mathmorra::Matrix2::operator+=(const mathmorra::Matrix2& b) {
  this->m[0] += b.m[0];
  this->m[1] += b.m[1];
  this->m[2] += b.m[2];
  this->m[3] += b.m[3];
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::operator+(const float& b) const {
  mathmorra::Matrix2 result = mathmorra::Matrix2();
  result = this->m[0] + b;
  result = this->m[1] + b;
  result = this->m[2] + b;
  result = this->m[3] + b;
  return result;
}

//---------------------------------------------------------------------------//

void mathmorra::Matrix2::operator+=(const float& b) {
  this->m[0] += b;
  this->m[1] += b;
  this->m[2] += b;
  this->m[3] += b;
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::operator-(const mathmorra::Matrix2& b) const {
  mathmorra::Matrix2 result = mathmorra::Matrix2();
  result = this->m[0] - b.m[0];
  result = this->m[1] - b.m[1];
  result = this->m[2] - b.m[2];
  result = this->m[3] - b.m[3];
  return result;
}

//---------------------------------------------------------------------------//

void mathmorra::Matrix2::operator-=(const mathmorra::Matrix2& b) {
  this->m[0] -= b.m[0];
  this->m[1] -= b.m[1];
  this->m[2] -= b.m[2];
  this->m[3] -= b.m[3];
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::operator-(const float& b) const {
  mathmorra::Matrix2 result = mathmorra::Matrix2();
  result = this->m[0] - b;
  result = this->m[1] - b;
  result = this->m[2] - b;
  result = this->m[3] - b;
  return result;
}

//---------------------------------------------------------------------------//

void mathmorra::Matrix2::operator-=(const float& b) {
  this->m[0] -= b;
  this->m[1] -= b;
  this->m[2] -= b;
  this->m[3] -= b;
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::operator*(const float& b) const {
  mathmorra::Matrix2 result = mathmorra::Matrix2();
  result = this->m[0] * b;
  result = this->m[1] * b;
  result = this->m[2] * b;
  result = this->m[3] * b;
  return result;
}

//---------------------------------------------------------------------------//

void mathmorra::Matrix2::operator*=(const float& b) {
  this->m[0] *= b;
  this->m[1] *= b;
  this->m[2] *= b;
  this->m[3] *= b;
}

//---------------------------------------------------------------------------//

mathmorra::Matrix2 mathmorra::Matrix2::operator/(const float& b) const {
  mathmorra::Matrix2 result = mathmorra::Matrix2();
  result = this->m[0] / b;
  result = this->m[1] / b;
  result = this->m[2] / b;
  result = this->m[3] / b;
  return result;
}

//---------------------------------------------------------------------------//

void mathmorra::Matrix2::operator/=(const float& b) {
  this->m[0] /= b;
  this->m[1] /= b;
  this->m[2] /= b;
  this->m[3] /= b;
}

//---------------------------------------------------------------------------//

bool mathmorra::Matrix2::operator==(const mathmorra::Matrix2& b) const {
  return m[0] == b.m[0] && m[1] == b.m[1]
    && m[2] == b.m[2] && m[3] == b.m[3];
}

//---------------------------------------------------------------------------//

bool mathmorra::Matrix2::operator!=(const mathmorra::Matrix2& b) const {
  return m[0] != b.m[0] || m[1] != b.m[1]
    || m[2] != b.m[2] || m[3] != b.m[3];
}

//---------------------------------------------------------------------------//

void mathmorra::Matrix2::operator=(const mathmorra::Matrix2& b) {
  this->m[0] = b.m[0];
  this->m[1] = b.m[1];
  this->m[2] = b.m[2];
  this->m[3] = b.m[3];
}

//---------------------------------------------------------------------------//
