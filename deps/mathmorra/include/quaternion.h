/*

                        __| ? .',     ,'     _ _  ' c  _ _
                        (_| |  |  |~)  | \/ | ) ) | | | ) )
                                  |      (,

 .d88888b.                    888                              d8b
d88P" "Y88b                   888                              Y8P
888     888                   888
888     888 888  888  8888b.  888888  .d88b.  888d888 88888b.  888  .d88b.  88888b.
888     888 888  888     "88b 888    d8P  Y8b 888P"   888 "88b 888 d88""88b 888 "88b
888 Y8b 888 888  888 .d888888 888    88888888 888     888  888 888 888  888 888  888
Y88b.Y8b88P Y88b 888 888  888 Y88b.  Y8b.     888     888  888 888 Y88..88P 888  888
 "Y888888"   "Y88888 "Y888888  "Y888  "Y8888  888     888  888 888  "Y88P"  888  888
       Y8b

A quaternion is an alternative way of representing rotations through any axis.
Mathematically, they are an extension of the set of complex numbers.

They are compact, don't suffer from gimbal lock and can easily be interpolated.
We uses Quaternions to represent all rotations.


Author: Pablo Bano Benito <pablo.bano.benito@gmail.com>
Date: 16-02-2019
Quaternions Header
*/

#ifndef __QUATERNION_H__
#define __QUATERNION_H__ 1

#include <vector3.h>
#include <math.h>

/*
*/

namespace mathmorra {

  class Quaternion {

  public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(float a);
    Quaternion(const Quaternion& other);
    ~Quaternion();

    Quaternion operator*(const Quaternion q) const;
    void operator*(const Quaternion q);
    void operator=(const Quaternion& q);
    bool operator==(const Quaternion& q);

    /**
      * @brief    Change every imaginary part of the quaternion 
      *           by its negative.
      * @param    q: The quaternion to conjugate.
      * @return   The quaternion conjugated.
      */
    Quaternion Conjugate(const Quaternion q);

    /**
      * @brief    Returns the opposite of a quaternion.
      * @param    q: The quaternion to oppose.
      * @return   The quaternion opposite.
      */
    Quaternion Opposite(const Quaternion q);

    /**
      * @brief    Multiply two quaternions (combine rotations).
      * @param    q: First quaternion to combine.
      * @param    u: Second quaternion to combine.
      * @return   The rotations combined.
      */
    Quaternion Multiply(const Quaternion q, const Quaternion u);

    /**
      * @brief    Returns the inverse of rotation.
      * @param    q: The quaternion to invest.
      * @return   The quaternion inverted.
      */
    Quaternion Inverse(Quaternion q);

    //TODO: research
    Quaternion FromYawPitchRoll(const float yaw, const float pitch, const float roll);

    /**
      * @brief    Interpolates between q and u by index
      *           and normalizes the result afterwards.
      *           The parameter index is clamped to the range [0, 1].
      * @param    q: From.
      * @param    u: To.
      * @param    index: the value to interpolate.
      * @return   The quaternion normalized.
      */
    Quaternion Lerp(const Quaternion q, const Quaternion u, const float index);

    /**
      * @brief    Spherically interpolates between q and u by index. 
                  The parameter index is clamped to the range [0, 1].
      * @return   The quaternion normalized.
      */
    Quaternion Slerp(const Quaternion q, const Quaternion u, const float index);
    Quaternion EulerAngles(Vector3 axis, float grades);

    /**
      * @brief    Returns a quaternion with a magnitude of 1.
      * @return   The quaternion normalized.
      */
    Quaternion Normalized();

    /**
      * @brief    A quaternion is pure when its real part is equal 
      *           to 0 and the rest of components other than 0.
      * @return   The pure quaternion.    
      */
    Quaternion Pure();

    /**
      * @brief    This quaternion corresponds to "no rotation" - 
      *           the object must be perfectly aligned with the 
      *           world or parent axes.
      * @return   The identity quaternion.
      */
    Quaternion Identity();

    /**
      * @brief    Creates a rotation which rotates angle radians around axis.
      * @return   The vector rotated.
      */
    mathmorra::Vector3 RotateVectorByQuaternion(const Vector3 v, const Quaternion q) const;

    /**
      * @brief    Returns this quaternion with a magnitude of 1.
      * @return   The quaternion normalized.
      */
    void Normalize();

    /**
      * @brief    Calculate the length of the quaternion.
      * @return   Length.
      */
    float Length();

    /**
      * @brief    Calculate the length of the quaternion
                  without the previous calculation of square root.
      * @return   Sqr Length.
      */
    float SqrLength();

    static const Quaternion yaw;
    static const Quaternion pitch;
    static const Quaternion roll;

    float x;
    float y;
    float z;
    float w;

  };

}


#endif // __QUATERNION_H__