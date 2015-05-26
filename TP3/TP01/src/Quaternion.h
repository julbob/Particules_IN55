#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector3f.h"
#include <math.h>
class Quaternion
{
public:
    Quaternion();
    Quaternion operator*(const Quaternion& q)const;
    Vector3f operator* (const Vector3f& v)const;
    Quaternion operator*(float f)const;

    Quaternion operator+ (const Quaternion& q)const;
    Quaternion& operator *=(const Quaternion& q);

    Quaternion& operator = (const Quaternion& q);

    float dot(const Quaternion& q)const;
    void set(float w,float x, float y, float z);
    void setFromAxis(float angle, float ax, float ay, float az);
    Quaternion conjugate()const;
    Quaternion inverse()const;
    Quaternion slerp(const Quaternion& q1, const Quaternion& q2, float t)const;
    void normalize();
    void setRotationMarix(float* mat);

protected:
    float w;
    Vector3f v;
};

#endif // QUATERNION_H
