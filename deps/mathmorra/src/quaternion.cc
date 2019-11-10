/*
Author: Pablo Bano Benito <pablo.bano.benito@gmail.com>
Date: 16-02-2019
Quaternions
*/

#include "quaternion.h"

const mathmorra::Quaternion yaw;
const mathmorra::Quaternion pitch;
const mathmorra::Quaternion roll;

//------------------------------- Constructor --------------------------------//

 mathmorra::Quaternion::Quaternion() {

  this->x = 0.0f;
  this->y = 0.0f;
  this->z = 0.0f;
  this->w = 0.0f;

}

//---------------------------------------------------------------------------//

 mathmorra::Quaternion::Quaternion::~Quaternion() {

}

//---------------------------------------------------------------------------//

 mathmorra::Quaternion::Quaternion::Quaternion(float x, float y, float z, float w) {

  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;

}

//---------------------------------------------------------------------------//

 mathmorra::Quaternion::Quaternion::Quaternion(float a) {

   this->x = a;
   this->y = a;
   this->z = a;
   this->w = a;

 }

 //---------------------------------------------------------------------------//

 mathmorra::Quaternion::Quaternion::Quaternion(const Quaternion& other) {

  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  this->w = other.w;

}

//---------------------------------------------------------------------------//

//TODO: Research
mathmorra::Quaternion mathmorra::Quaternion::Pure() {

  Quaternion pure;

  pure.x = 1.0f;
  pure.y = 1.0f;
  pure.z = 1.0f;
  pure.w = 0.0f;

  return pure;

}

//---------------------------------------------------------------------------//

mathmorra::Quaternion mathmorra::Quaternion::Identity() {

  Quaternion identity;

  identity.x = 0.0f;
  identity.y = 0.0f;
  identity.z = 0.0f;
  identity.w = 1.0f;

  return identity;

}

//---------------------------------------------------------------------------//

mathmorra::Quaternion mathmorra::Quaternion::operator*(Quaternion q) const {

  Quaternion result;

  result.x = ((q.x * this->w) + (this->x * q.w)) + (q.y * this->z) - (q.z * this->y);
  result.y = ((q.y * this->w) + (this->y * q.w)) + (q.z * this->x) - (q.x * this->z);
  result.z = ((q.z * this->w) + (this->z * q.w)) + (q.x * this->y) - (q.y * this->x);
  result.w = ((q.w * this->w) - ((q.x * this->x) + (q.y * this->y)) + (q.z * this->z));

  return result;

}

//---------------------------------------------------------------------------//


 void mathmorra::Quaternion::operator*(Quaternion q) {

  this->x = ((q.x * this->w) + (this->x * q.w)) + (q.y * this->z) - (q.z * this->y);
  this->y = ((q.y * this->w) + (this->y * q.w)) + (q.z * this->x) - (q.x * this->z);
  this->z = ((q.z * this->w) + (this->z * q.w)) + (q.x * this->y) - (q.y * this->x);
  this->w = ((q.w * this->w) - ((q.x * this->x) + (q.y * this->y)) + (q.z * this->z));

}

//---------------------------------------------------------------------------//

 void mathmorra::Quaternion::operator=(const Quaternion& q) {

  this->x = q.x;
  this->y = q.y;
  this->z = q.z;
  this->w = q.w;

}

//---------------------------------------------------------------------------//

 mathmorra::Quaternion mathmorra::Quaternion::Normalized() {

  Quaternion result;

  float inverseModule = 1.0f / this->Length();

  result.x = (this->x * inverseModule);
  result.y = (this->y * inverseModule);
  result.z = (this->z * inverseModule);
  result.w = (this->w * inverseModule);

  return result;

}

//---------------------------------------------------------------------------//

 void mathmorra::Quaternion::Normalize() {

  float inverseModule = 1.0f / this->Length();

  this->x *= inverseModule;
  this->y *= inverseModule;
  this->z *= inverseModule;
  this->w *= inverseModule;

}

//---------------------------------------------------------------------------//

 bool mathmorra::Quaternion::operator==(const Quaternion& b) {

  return ((b.x == this->x) &&
          (b.y == this->y) &&
          (b.z == this->z) &&
          (b.w == this->w));

}

//---------------------------------------------------------------------------//

 mathmorra::Vector3 mathmorra::Quaternion::RotateVectorByQuaternion(const Vector3 v, const Quaternion q) const {

   Vector3  qv = { q.x, q.y, q.z };

   mathmorra::Vector3 vcv = vcv.CrossProduct(qv, v);

   mathmorra::Vector3 cross = cross.CrossProduct(qv, vcv);
   mathmorra::Vector3 rotated = { v.x_ + vcv.x_ * 2.0f * q.w + cross.x_ * 2.0f,
                                  v.y_ + vcv.y_ * 2.0f * q.w + cross.y_ * 2.0f,
                                  v.z_ + vcv.z_ * 2.0f * q.w + cross.z_ * 2.0f };

   return rotated;

 }


//---------------------------------------------------------------------------//

 float mathmorra::Quaternion::SqrLength() {

  return (((powf(this->x, 2.0f)) +
           (powf(this->y, 2.0f))) +
           (powf(this->z, 2.0f))) +
           (powf(this->w, 2.0f));

}

//---------------------------------------------------------------------------//

 float mathmorra::Quaternion::Length() {

  return sqrt(this->SqrLength());

}

//---------------------------------------------------------------------------//

 mathmorra::Quaternion mathmorra::Quaternion::Multiply(const Quaternion q, 
                                                       const Quaternion u) {

  Quaternion result;

  result.x = ((q.x * u.w) + (u.x * q.w)) + (q.y * u.z) - (q.z * u.y);
  result.y = ((q.y * u.w) + (u.y * q.w)) + (q.z * u.x) - (q.x * u.z);
  result.z = ((q.z * u.w) + (u.z * q.w)) + (q.x * u.y) - (q.y * u.x);
  result.w = ((q.w * u.w) - ((q.x * u.x) + (q.y * u.y)) + (q.z * u.z));

  return result;

}

//---------------------------------------------------------------------------//

 mathmorra::Quaternion mathmorra::Quaternion::Conjugate(const Quaternion q) {

  Quaternion result;

  result.x = -q.x;
  result.y = -q.y;
  result.z = -q.z;
  result.w = q.w;

  return result;

}

//---------------------------------------------------------------------------//

 mathmorra::Quaternion mathmorra::Quaternion::Opposite(const Quaternion q) {

  Quaternion result;

  result.x = -q.x;
  result.y = -q.y;
  result.z = -q.z;
  result.w = q.w;

  return result;

}

//---------------------------------------------------------------------------//

 mathmorra::Quaternion mathmorra::Quaternion::Inverse(Quaternion q) {

  Quaternion result;
  float lenght = q.Length();

  float num = 1.0f / lenght;

  result.x = -q.x * num;
  result.y = -q.y * num;
  result.z = -q.z * num;
  result.w =  q.w * num;

  return result;

}


//---------------------------------------------------------------------------//

 mathmorra::Quaternion mathmorra::Quaternion::EulerAngles(const Vector3 axis, 
                                                          const float grades) {

  Quaternion result;

  //float half = grades >> 1;
  float new_angle = grades * 0.5;
  float angle = sin(new_angle);


  result.w = cos(new_angle);

  result.x = axis.x_ * angle;
  result.y = axis.y_ * angle;
  result.z = axis.z_ * angle;

  return result;

}

//---------------------------------------------------------------------------//
 //TODO: research
 mathmorra::Quaternion mathmorra::Quaternion::FromYawPitchRoll(const float yaw, 
                                                               const float pitch, 
                                                               const float roll) {

  Quaternion result;


  return result;

}

//---------------------------------------------------------------------------//

 mathmorra::Quaternion mathmorra::Quaternion::Lerp(Quaternion q, Quaternion u, float index) {

  float negative = 1 - index;
  Quaternion result;

  if ((((q.x * u.x) + (q.y * u.y)) + (q.z * u.z)) + (q.w * u.w) >= 0) {
    result.x = (negative * q.x) + (index * u.x);
    result.y = (negative * q.y) + (index * u.y);
    result.z = (negative * q.z) + (index * u.z);
    result.w = (negative * q.w) + (index * u.w);
  } else {
    result.x = (negative * q.x) - (index * u.x);
    result.y = (negative * q.y) - (index * u.y);
    result.z = (negative * q.z) - (index * u.z);
    result.w = (negative * q.w) - (index * u.w);
  }

  float inverted_magnitude = 1.0f / result.Length();
  result.x *= inverted_magnitude;
  result.y *= inverted_magnitude;
  result.z *= inverted_magnitude;
  result.w *= inverted_magnitude;

  return result;

}

//---------------------------------------------------------------------------//