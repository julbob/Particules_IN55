#include "vector3f.h"

Vector3f::Vector3f()
{
}

Vector3f::Vector3f(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3f& Vector3f::operator= (const Vector3f v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;

    return *this;
}

Vector3f Vector3f::operator+(const Vector3f& v)const{
    Vector3f V (this->x + v.x,this->y + v.y,this->z + v.z);
    return V;
}

Vector3f Vector3f::operator-(const Vector3f& v)const{
    Vector3f V (this->x - v.x,this->y - v.y,this->z - v.z);
    return V;
}

Vector3f Vector3f::operator*(const float f) const{
   Vector3f V (this->x * f,this->y  *f,this->z * f);
   return V;
}

float Vector3f::scalaire(const Vector3f& v)const{
    return (this->x * v.x) + (this->y * v.y) + (this->z * v.z);
}

Vector3f Vector3f::vectoriel(const Vector3f& v)const{
    Vector3f V ((this->y * v.z) - (this->z * v.y) , (this->z * v.x) - (this->x * v.z) , (this->x * v.y) - (this->y * v.x));
    return V;
}

void Vector3f::normalize(){
    this->x = this->x / sqrt( (this->x*this->x) + (this->y*this->y) + (this->z*this->z) );
    this->y = this->y / sqrt( (this->x*this->x) + (this->y*this->y) + (this->z*this->z) );
    this->z = this->z / sqrt( (this->x*this->x) + (this->y*this->y) + (this->z*this->z) );
}

float Vector3f::getX()const{
    return this->x;
}

float Vector3f::getY()const{
    return this->y;
}
float Vector3f::getZ()const{
    return this->z;
}

void Vector3f::setX(float x){
    this->x = x;
}

void Vector3f::setY(float y){
    this->y = y;
}

void Vector3f::setZ(float z){
    this->z = z;
}
