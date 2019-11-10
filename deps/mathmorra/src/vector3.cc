/*
Author: Adrian Garvia Arrogante <adriangarviasmr@gmail.com>
--Revision 10-02-2019 - Pablo Bano Benito <pablo.bano.benito@gmail.com>
Date: 02-01-2019
Vector3
*/

#include "vector3.h"
#include "math.h"

const mathmorra::Vector3 mathmorra::Vector3::up = Vector3(0.0f, 1.0f, 0.0f);
const mathmorra::Vector3 mathmorra::Vector3::down = Vector3(0.0f, -1.0f, 0.0f);
const mathmorra::Vector3 mathmorra::Vector3::right = Vector3(1.0f, 0.0f, 0.0f);
const mathmorra::Vector3 mathmorra::Vector3::left = Vector3(-1.0f, 0.0f, 0.0f);
const mathmorra::Vector3 mathmorra::Vector3::forward = Vector3(0.0f, 0.0f, 1.0f);
const mathmorra::Vector3 mathmorra::Vector3::back = Vector3(0.0f, 0.0f, -1.0f);
const mathmorra::Vector3 mathmorra::Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
const mathmorra::Vector3 mathmorra::Vector3::unit = Vector3(1.0f, 1.0f, 1.0f);

//---------------------------------------------------------------------------//

mathmorra::Vector3::Vector3() {

  x_ = 0.0f;
  y_ = 0.0f;
  z_ = 0.0f;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3::Vector3(float x, float y, float z) {

  this->x_ = x;
  this->y_ = y;
  this->z_ = z;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3::Vector3(const Vector3& copy) {

  this->x_ = copy.x_;
  this->y_ = copy.y_;
  this->z_ = copy.z_;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::operator+(const Vector3& b) const {

  mathmorra::Vector3 result = mathmorra::Vector3();

  result.x_ = this->x_ + b.x_;
  result.y_ = this->y_ + b.y_;
  result.z_ = this->z_ + b.z_;

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::operator+(const float& b) {

  mathmorra::Vector3 result = mathmorra::Vector3();

  result.x_ = this->x_ + b;
  result.y_ = this->y_ + b;
  result.z_ = this->z_ + b;

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3& mathmorra::Vector3::operator+=(const Vector3& b) {

  this->x_ += b.x_;
  this->y_ += b.y_;
  this->z_ += b.z_;

  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3& mathmorra::Vector3::operator+=(const float& b) {

  this->x_ += b;
  this->y_ += b;
  this->z_ += b;

  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3  mathmorra::Vector3::operator-(const Vector3& b) const {

  mathmorra::Vector3 result = mathmorra::Vector3();

  result.x_ = this->x_ - b.x_;
  result.y_ = this->y_ - b.y_;
  result.z_ = this->z_ - b.z_;

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3  mathmorra::Vector3::operator-(const float& b) const {

  mathmorra::Vector3 result = mathmorra::Vector3();

  result.x_ = this->x_ - b;
  result.y_ = this->y_ - b;
  result.z_ = this->z_ - b;

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::operator-() {

  return *this * -1.0f;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3& mathmorra::Vector3::operator-=(const Vector3& b) {

  this->x_ -= b.x_;
  this->y_ -= b.y_;
  this->z_ -= b.z_;

  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3& mathmorra::Vector3::operator-=(const float& b) {

  this->x_ -= b;
  this->y_ -= b;
  this->z_ -= b;

  return *this;

}

//---------------------------------------------------------------------------//

bool mathmorra::Vector3::operator==(const Vector3& b) const {

  return this->x_ == b.x_ && 
         this->y_ == b.y_ && 
         this->z_ == b.z_;

}

//---------------------------------------------------------------------------//

bool mathmorra::Vector3::operator!=(const Vector3& b) const {

  return this->x_ != b.x_ || 
         this->y_ != b.y_ || 
         this->z_ != b.z_;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector3::operator=(const Vector3& b) {

  this->x_ = b.x_;
  this->y_ = b.y_;
  this->z_ = b.z_;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector3::operator=(const float& b) {

  this->x_ = b;
  this->y_ = b;
  this->z_ = b;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3  mathmorra::Vector3::operator*(const float& b) {

  mathmorra::Vector3 result = mathmorra::Vector3();

  result.x_ = this->x_ * b;
  result.y_ = this->y_ * b;
  result.z_ = this->z_ * b;

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3& mathmorra::Vector3::operator*=(const float& b) {

  this->x_ *= b;
  this->y_ *= b;
  this->z_ *= b;

  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3  mathmorra::Vector3::operator/(const float& b) {

  mathmorra::Vector3 result = mathmorra::Vector3();
  float inverted_b = 1.0f / b;

  result.x_ = x_ * inverted_b;
  result.y_ = y_ * inverted_b;
  result.z_ = z_ * inverted_b;

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3& mathmorra::Vector3::operator/=(const float& b) {

  float inverted_b = 1.0f / b;

  this->x_ *= inverted_b;
  this->y_ *= inverted_b;
  this->z_ *= inverted_b;

  return *this;

}

//---------------------------------------------------------------------------//

float mathmorra::Vector3::Magnitude() const {

  return sqrt(SqrMagnitude());

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::Normalized() const {

  mathmorra::Vector3 result = mathmorra::Vector3();
  float inverted_module = 1.0f / this->Magnitude();

  result.x_ = this->x_ * inverted_module;
  result.y_ = this->y_ * inverted_module;
  result.z_ = this->z_ * inverted_module;
  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::Max(const mathmorra::Vector3& a, const mathmorra::Vector3& b) {

  mathmorra::Vector3 c;

  c.x_ = (a.x_ >= b.x_) ? a.x_ : b.x_;
  c.y_ = (a.y_ >= b.y_) ? a.y_ : b.y_;
  c.z_ = (a.z_ >= b.z_) ? a.z_ : b.z_;

  return c;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::Min(const mathmorra::Vector3& a, const mathmorra::Vector3& b) {


  mathmorra::Vector3 c;

  c.x_ = (a.x_ <= b.x_) ? a.x_ : b.x_;
  c.y_ = (a.y_ <= b.y_) ? a.y_ : b.y_;
  c.z_ = (a.z_ <= b.z_) ? a.z_ : b.z_;

  return c;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::ClampMagnitude(const Vector3& a, float maxLen) {

  mathmorra::Vector3 result;
  float module_ = a.Magnitude();

  if (module_ <= maxLen) return a;

  result = a.Normalized();

  result.x_ *= maxLen;
  result.y_ *= maxLen;
  result.z_ *= maxLen;

  return result;


}

//---------------------------------------------------------------------------//

void mathmorra::Vector3::Normalize() {

  float inverted_module = 1.0f / this->Magnitude();

  this->x_ *= inverted_module;
  this->y_ *= inverted_module;
  this->z_ *= inverted_module;

}

//---------------------------------------------------------------------------//

float mathmorra::Vector3::SqrMagnitude() const {

  return powf(this->x_, 2.0f) + 
         powf(this->y_, 2.0f) + 
         powf(this->z_, 2.0f);

}

//---------------------------------------------------------------------------//

void mathmorra::Vector3::Scale(const mathmorra::Vector3& other) {

  this->x_ *= other.x_;
  this->y_ *= other.y_;
  this->z_ *= other.z_;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::Normalized(mathmorra::Vector3 a) {

  mathmorra::Vector3 result = mathmorra::Vector3();
  float inverted_module = 1.0f / a.Magnitude();
  
  result.x_ = a.x_ * inverted_module;
  result.y_ = a.y_ * inverted_module;
  result.z_ = a.z_ * inverted_module;
  
  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::Lerp(const mathmorra::Vector3& a, const mathmorra::Vector3& b, float t) {

  mathmorra::Vector3 c = mathmorra::Vector3();

  if (t >= 1.0f) return b;
  if (t <= 0.0f) return a;

  c.x_ = a.x_ + (t * (b.x_ - a.x_));
  c.y_ = a.y_ + (t * (b.y_ - a.y_));
  c.z_ = a.z_ + (t * (b.z_ - a.z_));

  return c;

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::LerpUnclamped(const mathmorra::Vector3& a, const mathmorra::Vector3& b, float t) {

  mathmorra::Vector3 c = mathmorra::Vector3();
  c.x_ = a.x_ + (t * (b.x_ - a.x_));
  c.y_ = a.y_ + (t * (b.y_ - a.y_));
  c.z_ = a.z_ + (t * (b.z_ - a.z_));
  return c;

}

//---------------------------------------------------------------------------//

float mathmorra::Vector3::DotProduct(const mathmorra::Vector3& a, const mathmorra::Vector3& b) {

  return (a.x_ * b.x_) + 
         (a.y_ * b.y_) + 
         (a.z_ * b.z_);

}

//---------------------------------------------------------------------------//

mathmorra::Vector3 mathmorra::Vector3::CrossProduct(const mathmorra::Vector3 a, const mathmorra::Vector3 b) {

  mathmorra::Vector3 c;

  c.x_ = a.y_ * b.z_ - a.z_ * b.y_;
  c.y_ = a.z_ * b.x_ - a.x_ * b.z_;
  c.z_ = a.x_ * b.y_ - a.y_ * b.x_;

  return c;

}

//---------------------------------------------------------------------------//

float mathmorra::Vector3::Angle(const mathmorra::Vector3& a, const mathmorra::Vector3& b) {

  return acos(DotProduct(a, b) / (a.Magnitude() * b.Magnitude()));

}

//---------------------------------------------------------------------------//

float mathmorra::Vector3::Distance(const mathmorra::Vector3& a, const mathmorra::Vector3& b) {

  return sqrt(powf(b.x_ - a.x_, 2.0f) + 
              powf(b.y_ - a.y_, 2.0f) + 
              powf(b.z_ - a.z_, 2.0f));

}

//---------------------------------------------------------------------------//
