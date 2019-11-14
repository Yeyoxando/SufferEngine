/*
Author: Pablo Bano Benito <pablo.bano.benito@gmail.com>
Date: 02-01-2019
Vector4
*/

#include "vector4.h"

const mathmorra::Vector4 mathmorra::Vector4::one = mathmorra::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
const mathmorra::Vector4 mathmorra::Vector4::zero = mathmorra::Vector4(0.0f, 0.0f, 0.0f, 0.0f);

//---------------------------------------------------------------------------//

mathmorra::Vector4::Vector4() {

  this->x_ = 0.0f;
  this->y_ = 0.0f;
  this->z_ = 0.0f;
  this->w_ = 0.0f;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4::Vector4(float* a){

    this->x_ = a[0];
    this->y_ = a[1];
    this->z_ = a[2];
    this->w_ = a[3];

}

//---------------------------------------------------------------------------//

mathmorra::Vector4::Vector4(float x_, float y_, float z_, float w_) {

  this->x_ = x_;
  this->y_ = y_;
  this->z_ = z_;
  this->w_ = w_;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4::Vector4(mathmorra::Vector3 a, 
                            float w_) {

  this->x_ = a.x_;
  this->y_ = a.y_;
  this->z_ = a.z_;
  this->w_ = w_;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4::Vector4(float a) {

  this->x_ = a;
  this->y_ = a;
  this->z_ = a;
  this->w_ = a;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4::Vector4(const mathmorra::Vector4& copy) {

  this->x_ = copy.x_;
  this->y_ = copy.y_;
  this->z_ = copy.z_;
  this->w_ = copy.w_;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4::~Vector4() {

}

//-------------------------- Operand overload -------------------------------//

mathmorra::Vector4 mathmorra::Vector4::operator+(const mathmorra::Vector4& b) const {

  mathmorra::Vector4 result = { 0.0f };

  result.x_ = (this->x_ + b.x_);
  result.y_ = (this->y_ + b.y_);
  result.z_ = (this->z_ + b.z_);
  result.w_ = (this->w_ + b.w_);

  return result;
}

//---------------------------------------------------------------------------//

mathmorra::Vector4 mathmorra::Vector4::operator+(const float& b) const {

  mathmorra::Vector4 result = { 0.0f };

  result.x_ = (this->x_ + b);
  result.y_ = (this->y_ + b);
  result.z_ = (this->z_ + b);
  result.w_ = (this->w_ + b);

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector4::operator+=(const mathmorra::Vector4& b) {

  this->x_ += b.x_;
  this->y_ += b.y_;
  this->z_ += b.z_;
  this->w_ += b.w_;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector4::operator+=(const float& b) {

  this->x_ += b;
  this->y_ += b;
  this->z_ += b;
  this->w_ += b;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4 mathmorra::Vector4::operator-(const mathmorra::Vector4& b) const {

  Vector4 result = { 0.0f };

  result.x_ = (this->x_ - b.x_);
  result.y_ = (this->y_ - b.y_);
  result.z_ = (this->z_ - b.z_);
  result.w_ = (this->w_ - b.w_);

  return result;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4 mathmorra::Vector4::operator-(const float& b) const {

  mathmorra::Vector4 result = { 0.0f };

  result.x_ = (this->x_ - b);
  result.y_ = (this->y_ - b);
  result.z_ = (this->z_ - b);
  result.w_ = (this->w_ - b);

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector4::operator-=(const mathmorra::Vector4& b) {

  this->x_ -= b.x_;
  this->y_ -= b.y_;
  this->z_ -= b.z_;
  this->w_ -= b.w_;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector4::operator-=(const float& b) {

  this->x_ -= b;
  this->y_ -= b;
  this->z_ -= b;
  this->w_ -= b;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4 mathmorra::Vector4::operator*(const float& b) const {

  mathmorra::Vector4 result = { 0.0f };

  result.x_ = this->x_ * b;
  result.y_ = this->y_ * b;
  result.z_ = this->z_ * b;
  result.w_ = this->w_ * b;

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector4::operator*=(const float& b) {

  this->x_ *= b;
  this->y_ *= b;
  this->z_ *= b;
  this->w_ *= b;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4 mathmorra::Vector4::operator/(const float& b) const {

  Vector4 result = { 0.0f };
  float inverted_param = 1.0f / b;

  result.x_ = this->x_ * inverted_param;
  result.y_ = this->y_ * inverted_param;
  result.z_ = this->z_ * inverted_param;
  result.w_ = this->w_ * inverted_param;

  return result;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector4::operator/=(const float& b) {

  float inverted_param = 1.0f / b;

  this->x_ *= inverted_param;
  this->y_ *= inverted_param;
  this->z_ *= inverted_param;
  this->w_ *= inverted_param;

}

//---------------------------------------------------------------------------//

bool mathmorra::Vector4::operator==(const mathmorra::Vector4& b) {

  return ((b.x_ == this->x_) && 
          (b.y_ == this->y_) && 
          (b.z_ == this->z_) &&
          (b.w_ == this->w_));

}

//---------------------------------------------------------------------------//

bool mathmorra::Vector4::operator!=(const mathmorra::Vector4& b) {

  return ((b.x_ != this->x_) || 
          (b.y_ != this->y_) || 
          (b.z_ != this->z_) || 
          (b.w_ != this->w_));

}

//---------------------------------------------------------------------------//

void mathmorra::Vector4::operator=(const mathmorra::Vector4& b) {

  this->x_ = b.x_;
  this->y_ = b.y_;
  this->z_ = b.z_;
  this->w_ = b.w_;

}

//------------------------------- Methods -----------------------------------//

float mathmorra::Vector4::SqrMagnitude() const {

  return (powf(this->x_, 2.0f) + 
          powf(this->y_, 2.0f) + 
          powf(this->z_, 2.0f) + 
          powf(this->w_, 2.0f));

}

//---------------------------------------------------------------------------//

float mathmorra::Vector4::Magnitude() const {
  return sqrt(SqrMagnitude());
}

//---------------------------------------------------------------------------//


void mathmorra::Vector4::Normalize() {

  float inverseModule = 1.0f / this->Magnitude();

  this->x_ *= inverseModule;
  this->y_ *= inverseModule;
  this->z_ *= inverseModule;
  this->w_ *= inverseModule;

}

//---------------------------------------------------------------------------//

mathmorra::Vector4 mathmorra::Vector4::Normalized() const {

  mathmorra::Vector4 normalized_vector;

  float inverseModule = 1.0f / this->Magnitude();

  normalized_vector.x_ = (this->x_ * inverseModule);
  normalized_vector.y_ = (this->y_ * inverseModule);
  normalized_vector.z_ = (this->z_ * inverseModule);
  normalized_vector.w_ = (this->w_ * inverseModule);

  return normalized_vector;

}

//---------------------------------------------------------------------------//

void mathmorra::Vector4::Scale(mathmorra::Vector4 scale) {

  this->x_ *= scale.x_;
  this->y_ *= scale.y_;
  this->z_ *= scale.z_;
  this->w_ *= scale.w_;

}

//---------------------------------------------------------------------------//

float mathmorra::Vector4::Distance(const mathmorra::Vector4& a, 
                                   const mathmorra::Vector4& b) {

  mathmorra::Vector4 c;
  float distance = 0.0f;

  c.x_ = b.x_ - a.x_;
  c.y_ = b.y_ - a.y_;
  c.z_ = b.z_ - a.z_;
  c.w_ = b.w_ - a.w_;

  distance = c.Magnitude();

  return distance;

}

//---------------------------------------------------------------------------//

float mathmorra::Vector4::DotProduct(mathmorra::Vector4 a, 
                                     mathmorra::Vector4 b) {

  return (a.x_ * b.x_ +
          a.y_ * b.y_ +
          a.z_ * b.z_ +
          a.w_ * b.w_);

}

//---------------------------------------------------------------------------//

mathmorra::Vector4 mathmorra::Vector4::Lerp(const mathmorra::Vector4& a, 
                                            const mathmorra::Vector4& b, 
                                            float index) {

  if (index >= 1.0f) return b;
  if (index <= 0.0f) return a;

  return (a.x_ + index * (b.x_ - a.x_), 
          a.y_ + index * (b.y_ - a.y_),
          a.z_ + index * (b.z_ - a.z_), 
          a.w_ + index * (b.w_ - a.w_));

}

//---------------------------------------------------------------------------//

mathmorra::Vector4 mathmorra::Vector4::Projection(mathmorra::Vector4 a, 
                                                  mathmorra::Vector4 b) {

  mathmorra::Vector4 projection = { 0.0f };
  float num = ((b.x_ * a.x_) + (b.y_ * a.y_) + (b.z_ * a.z_) + (b.w_ * a.w_));

  projection = a * (num / powf(a.Magnitude(), 2.0f));

  return projection;

}

//---------------------------------------------------------------------------//

float* mathmorra::Vector4::GetValues(){
  float value[] = {x_, y_, z_, w_};
    return value;
}

//---------------------------------------------------------------------------//
