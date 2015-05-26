#include "quaternion.h"

Quaternion::Quaternion()
{
}


Quaternion Quaternion::operator*(const Quaternion& q)const{
   Quaternion result;
   result.w = (this->w * q.w) - this->v.scalaire(q.v);
   result.v = q.v * w + this->v*q.w + this->v.vectoriel(q.v);
   return result;
}

Vector3f Quaternion::operator* (const Vector3f& v)const{
    Quaternion qp;
    Quaternion result;

    qp.w = 0;
    qp.v = v;

    result = (*this) * qp * (this->inverse());
    return result.v;
}

Quaternion Quaternion::operator*(float f)const{
    Quaternion result;
    result.w = this->w * f;
    result.v = this->v * f;
    return result;
}

Quaternion Quaternion::operator+ (const Quaternion& q)const{
    Quaternion result;
    result.w = this->w + q.w;
    result.v = this->v + q.v;

    return result;
}

Quaternion& Quaternion::operator *=(const Quaternion& q){
    this->w = (this->w * q.w) - this->v.scalaire(q.v);
    this->v = q.v*this->w + this->v*q.w + this->v.vectoriel(q.v);
    return *this;
}

Quaternion& Quaternion::operator = (const Quaternion& q){
    this->v = q.v;
    this->w = q.w;

    return *this;
}


float Quaternion::dot(const Quaternion& q)const{

    return this->v.scalaire(q.v) + (this->w*q.w);

}

void Quaternion::set(float w,float x, float y, float z){
    this->w = w; this->v.setX(x); this->v.setY(y); this->v.setZ(z);
}

void Quaternion::setFromAxis(float angle, float ax, float ay, float az){
    this->w = cos (angle/2);
    Vector3f v(ax,ay,az);
    v.normalize();
    this->v = v * sin(angle/2);

}

Quaternion Quaternion::conjugate()const{
    Quaternion result;
    result.w = this->w;
    result.v = this->v * (-1);
    return result;
}
Quaternion Quaternion::inverse()const{
    Quaternion result = this->conjugate() * (1/((this->w*this->w) + (this->v.getX()*this->v.getX()) + (this->v.getY()*this->v.getY()) + (this->v.getZ()*this->v.getZ()) ));
    return result;
}

Quaternion Quaternion::slerp(const Quaternion& q1, const Quaternion& q2, float t)const{
    float theta = acos( (q1.dot(q2)) );
    Quaternion result;
    result = q1* (float)((sin(theta*(1-t)))/sin(theta)) + q2* (float)((sin(theta*t))/(sin(theta)));
}

void Quaternion::normalize(){
    /* todo*/
}

void Quaternion::setRotationMarix(float* mat){
    mat[0] = 1 - (2 * this->v.getY() * this->v.getY()) - (2* this->v.getZ() * this->v.getZ());
    mat[1] = (2*this->v.getX() * this->v.getY()) - (2*this->w * this->v.getZ());
    mat[2] = (2*this->v.getX() * this->v.getZ()) + (2*this->w * this->v.getY());

    mat[3] = (2*this->v.getX() * this->v.getY()) + (2*this->w * this->v.getZ());
    mat[4] = 1 - (2 * this->v.getX() * this->v.getX()) - (2* this->v.getZ() * this->v.getZ());
    mat[5] = (2*this->v.getY() * this->v.getZ()) - (2*this->w * this->v.getX());

    mat[6] = (2*this->v.getX() * this->v.getZ()) - (2*this->w * this->v.getY());
    mat[7] = (2*this->v.getY() * this->v.getZ()) + (2*this->w * this->v.getX());
    mat[8] = 1 - (2 * this->v.getX() * this->v.getX()) - (2* this->v.getY() * this->v.getY());
}
