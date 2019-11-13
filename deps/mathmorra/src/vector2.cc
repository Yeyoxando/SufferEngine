/*
Author: Pablo Bano Benito <pablo.bano.benito@gmail.com>
Date: 02-01-2019
Vector2
*/

#include "vector2.h"


const mathmorra::Vector2 mathmorra::Vector2::down = mathmorra::Vector2(0.0f, -1.0f);
const mathmorra::Vector2 mathmorra::Vector2::left = mathmorra::Vector2(-1.0f, 0.0f);
const mathmorra::Vector2 mathmorra::Vector2::one = mathmorra::Vector2(1.0f, 1.0f);
const mathmorra::Vector2 mathmorra::Vector2::right = mathmorra::Vector2(1.0f, 0.0f);
const mathmorra::Vector2 mathmorra::Vector2::up = mathmorra::Vector2(0.0f, 1.0f);
const mathmorra::Vector2 mathmorra::Vector2::zero = mathmorra::Vector2(0.0f, 0.0f);

//---------------------------------------------------------------------------//

mathmorra::Vector2::Vector2() {

  this->x_ = 0.0f;
  this->y_ = 0.0f;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2::Vector2(float x_, float y_) {

  this->x_ = x_;
  this->y_ = y_;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2::Vector2(const mathmorra::Vector2& copy) {

  this->x_ = copy.x_;
  this->y_ = copy.y_;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2::~Vector2() {

}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Vector2::operator+(const mathmorra::Vector2& b) const {

  mathmorra::Vector2 result;

  result.x_ = this->x_ + b.x_;
  result.y_ = this->y_ + b.y_;

  return result;
}


//---------------------------------------------------------------------------//

mathmorra::Vector2& mathmorra::Vector2::operator+(const float& b) {

  this->x_ = this->x_ + b;
  this->y_ = this->y_ + b;

  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2& mathmorra::Vector2::operator+=(const mathmorra::Vector2& b) {

  this->x_ += b.x_;
  this->y_ += b.y_;

  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2& mathmorra::Vector2::operator+=(const float& b) {

  this->x_ = this->x_ + b;
  this->y_ = this->y_ + b;

  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Vector2::operator-(const float& b) const {

  mathmorra::Vector2 result;

  result.x_ = this->x_ - b;
  result.y_ = this->y_ - b;

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Vector2::operator-(const mathmorra::Vector2& b) const {

  mathmorra::Vector2 result;

  result.x_ = this->x_ - b.x_;
  result.y_ = this->y_ - b.y_;

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2& mathmorra::Vector2::operator-() {

  this->x_ *= -1.0f;
  this->y_ *= -1.0f;

  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2& mathmorra::Vector2::operator-=(const mathmorra::Vector2& b) {

  this->x_ -= b.x_;
  this->y_ -= b.y_;
  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2& mathmorra::Vector2::operator-=(const float& b) {

  this->x_ -= b;
  this->y_ -= b;

  return *this;

}

//---------------------------------------------------------------------------//

bool mathmorra::Vector2::operator==(const mathmorra::Vector2& b) const {

  return ((b.x_ == this->x_) && 
          (b.y_ == this->y_));

}

//---------------------------------------------------------------------------//

bool mathmorra::Vector2::operator!=(const mathmorra::Vector2& b) const {

  return ((b.x_ != this->x_) || 
          (b.y_ != this->y_));

}

//---------------------------------------------------------------------------//

void mathmorra::Vector2::operator=(const float& b) {

  this->x_ = b;
  this->y_ = b;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector2::operator=(const mathmorra::Vector2& b) {

  this->x_ = b.x_;
  this->y_ = b.y_;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Vector2::operator*(const float& b) {

  mathmorra::Vector2 result;

  result.x_ = this->x_ * b;
  result.y_ = this->y_ * b;

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2& mathmorra::Vector2::operator*=(const float& b) {

  this->x_ *= b;
  this->y_ *= b;
  return *this;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Vector2::operator/(const float& b) {

 mathmorra::Vector2 result;
  result.x_ = this->x_ / b;
  result.y_ = this->y_ / b;
  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2& mathmorra::Vector2::operator/=(const float& b) {

  this->x_ /= b;
  this->y_ /= b;
  return *this;

}

//---------------------------------------------------------------------------//

float mathmorra::Vector2::SqrMagnitude() const {

  return (powf(this->x_, 2.0f) + 
          powf(this->y_, 2.0f));

}

//---------------------------------------------------------------------------//

float mathmorra::Vector2::Magnitude() const {

  return sqrt(SqrMagnitude());

}

//---------------------------------------------------------------------------//

void mathmorra::Vector2::Normalize() {

  float inverted_module = 1.0f / this->Magnitude();

  this->x_ *= inverted_module;
  this->y_ *= inverted_module;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Vector2::Normalized() const {

 mathmorra::Vector2 normalized_vector;

  float inverted_module = 1.0f / this->Magnitude();

  normalized_vector.x_ = (this->x_ * inverted_module);
  normalized_vector.y_ = (this->y_ * inverted_module);

  return normalized_vector;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector2::Scale(const mathmorra::Vector2 scale) {

  this->x_ *= scale.x_;
  this->y_ *= scale.y_;

}

//---------------------------------------------------------------------------//

float mathmorra::Vector2::Distance(const mathmorra::Vector2 a,
                                   const mathmorra::Vector2 b) {

  mathmorra::Vector2 c;
  float distance = 0.0f;

  c.x_ = b.x_ - a.x_;
  c.y_ = b.y_ - a.y_;

  distance = c.Magnitude();
  return distance;

}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Vector2::Lerp(const mathmorra::Vector2 a, 
                                            const mathmorra::Vector2 b,
                                            float t) {

  if (t >= 1.0f) return b;
  if (t <= 0.0f) return a;

  return ((b - a) * t + a);

}

//---------------------------------------------------------------------------//

mathmorra::Vector2 mathmorra::Vector2::LerpUnclamped(const mathmorra::Vector2 a, 
                                                     const mathmorra::Vector2 b, float t) {

  return ((b - a) * t + a);

}

//---------------------------------------------------------------------------//

float mathmorra::Vector2::DotProduct(mathmorra::Vector2 a, 
                                     mathmorra::Vector2 b) {

  return (a.x_ * b.x_ +
          a.y_ * b.y_);

}

//---------------------------------------------------------------------------//