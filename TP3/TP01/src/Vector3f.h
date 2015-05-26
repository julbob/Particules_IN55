#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <math.h>

class Vector3f
{
public:
    Vector3f();
    Vector3f(float x, float y, float z);

    Vector3f& operator= (const Vector3f v);
    Vector3f operator+(const Vector3f& v) const;
    Vector3f operator-(const Vector3f& v) const;
    Vector3f operator*(const float f) const;

    float scalaire(const Vector3f& v) const;
    Vector3f vectoriel(const Vector3f& v) const;

    void normalize();

    float getX() const;
    float getY() const;
    float getZ()const;

    void setX(float x);
    void setY(float y);
    void setZ(float z);

private:
    float x;
    float y;
    float z;
};

#endif // VECTOR3F_H
