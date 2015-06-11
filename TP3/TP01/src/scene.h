#ifndef SCENE_H
#define SCENE_H

#include "GlWindow.h"

#include "../particle.h"
#include "Camera.h"
#include "../Common/Shapes/Basis.h"

class Scene : public GlWindow{
public:
    Scene();
    ~Scene();

    /*!
    *\brief Initialization des objets.
    */
    bool initializeObjects();

    /*!
    *\brief Rendu de la scène.
    */
    void render();

    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent*);

private:
    static const int maxParticles = 5000;
    static const int interval = 30;

    QList<Particle*> particles;


    GLfloat* particlesPos;
    GLfloat* particlesColor;
    GLfloat* particlesSpeed;
    GLfloat* particlesAge;
    GLuint* indices;

    int timerId;
    int lifeTimer;

    Camera camera;
    Basis* base;
};

#endif // SCENE_H
