#ifndef CAMERA_H
#define CAMERA_H

#include "Quaternion.h"
#include "Vector3f.h"
#include <GlFramework.h>

class Camera
{

private:
    Vector3f m_Position;
    Quaternion m_Orientation;

    GLMatrix m_ViewMatrix;
    GLMatrix m_ProjectionMatrix;

    float ar;
    float np;
    float fp;
    float FOV;

public:
    Camera();

    void translate(float x, float y, float z);
    void translateX(float shift);
    void translateY(float shift);
    void translateZ(float shift);

    void rotate(float angle, float ax, float ay, float az);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    const GLMatrix getViewMatrix();

    void setAspectRatio(float ar);
    void setPlanes(float np, float  fp);
    void setFOV(float angle);

    const GLMatrix getProjectionMatrix();

protected:
    void buildViewMatrix();
    void buildProjectionMatrix();

};

#endif // CAMERA_H
