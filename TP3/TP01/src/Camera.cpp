#include "Camera.h"

Camera::Camera()
{
}

void Camera::translate(float x, float y, float z){
    this->m_Position.setX(this->m_Position.getX() + x);
    this->m_Position.setY(this->m_Position.getY() + y);
    this->m_Position.setZ(this->m_Position.getZ() + z);
}

void Camera::translateX(float shift){
    this->m_Position.setX(this->m_Position.getX() + shift);
}

void Camera::translateY(float shift){
    this->m_Position.setY(this->m_Position.getY() + shift);
}

void Camera::translateZ(float shift){
    this->m_Position.setZ(this->m_Position.getZ() + shift);
}

void Camera::rotate(float angle, float ax, float ay, float az){
    Quaternion rotation;
    rotation.setFromAxis(angle,ax,ay,az);
    this->m_Orientation = rotation * this->m_Orientation * rotation.inverse();
}

void Camera::rotateX(float angle){
    Quaternion rotation;
    rotation.setFromAxis(angle,1,0,0);
    this->m_Orientation = rotation * this->m_Orientation * rotation.inverse();
}

void Camera::rotateY(float angle){
    Quaternion rotation;
    rotation.setFromAxis(angle,0,1,0);
    this->m_Orientation = rotation * this->m_Orientation * rotation.inverse();
}

void Camera::rotateZ(float angle){
    Quaternion rotation;
    rotation.setFromAxis(angle,0,0,1);
    this->m_Orientation = rotation * this->m_Orientation * rotation.inverse();
}

const GLMatrix Camera::getViewMatrix(){
    return this->m_ViewMatrix;
}

void Camera::setAspectRatio(float ar){
    this->ar = ar;
}

void Camera::setPlanes(float np, float  fp){
    this->np = np; this->fp = fp;
}

void Camera::setFOV(float angle){
    this->FOV = angle;
}

const GLMatrix Camera::getProjectionMatrix(){
    return this->m_ProjectionMatrix;
}

/* protected */

void Camera::buildViewMatrix(){
    GLMatrix V;
    float r[9];
    this->m_Orientation.setRotationMarix(r);

   float  T[3];

   T[0] = - (r[0] * this->m_Position.getX() + r[1] * this->m_Position.getY() + r[2] * this->m_Position.getZ() );
   T[1] = - (r[3] * this->m_Position.getX() + r[4] * this->m_Position.getY() + r[5] * this->m_Position.getZ() );
   T[2] = - (r[6] * this->m_Position.getX() + r[7] * this->m_Position.getY() + r[8] * this->m_Position.getZ() );

   V.data[0] = r[0];V.data[4] = r[1]; V.data[8] = r[2]; V.data[12] = T[0];
   V.data[1] = r[3]; V.data[5] = r[4]; V.data[9] = r[5]; V.data[13] = T[1];
   V.data[2] = r[6]; V.data[6] = r[7]; V.data[10] = r[8]; V.data[14] = T[2];

   V.data[3] = 0; V.data[7] = 0; V.data[11] = 0; V.data[15] = 1;

   this->m_ViewMatrix = V;
}

void Camera::buildProjectionMatrix(){
    GLMatrix P;

    float n = 1/(tan(this->FOV/2));
    P.data[0] = n; P.data[4] = 0; P.data[8] = 0; P.data[12] = 0;
    P.data[1] = 0; P.data[5] = n/ar; P.data[9] = 0; P.data[13] = 0;
    P.data[2] = 0; P.data[6] = 0; P.data[10] = -(this->fp + this->np) / (this->fp - this->np); P.data[14] = -2* ((this->fp + this->np) / (this->fp - this->np));
    P.data[3] = 0; P.data[7] = 0; P.data[11] = -1; P.data[15] = 0;

    this->m_ProjectionMatrix = P;
}
