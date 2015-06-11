#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3f.h"
#include <GL/glew.h>

class Particle
{
private:
    Vector3f pos,speed;
    GLfloat size, weight;
    GLuint life;
    GLfloat age;
    GLuint color[4]; //r,g,b,a

    const float g = 9.8;

public:

    Particle(Vector3f* pos, Vector3f* speed, GLfloat size, GLfloat weight);

    bool operator<(const Particle& p) const;
    Vector3f getPos();
    Vector3f getSpeed();
    GLfloat getAge();
    void decreaseLife();


    void updateStats(float delta);

};

#endif // PARTICLE_H
