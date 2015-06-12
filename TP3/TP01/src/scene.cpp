#include "scene.h"

#include <iostream>
#include "QDebug"

using namespace std;

Scene::Scene():
particlesPos((GLfloat*) calloc(3 * maxParticles, sizeof(GLfloat))),
particlesColor((GLfloat*) calloc(3 * maxParticles, sizeof(GLfloat))),
particlesSpeed((GLfloat*) calloc(3 * maxParticles, sizeof(GLfloat))),
 particlesAge((GLfloat*) calloc(maxParticles, sizeof(GLfloat))),
indices((GLuint*) calloc(maxParticles, sizeof( GLuint)))
{
    setWindowTitle(trUtf8("Particles"));

    float x =(float)rand()/(float)RAND_MAX * 4 - 4;
    float y =(float)rand()/(float)RAND_MAX * 4 - 4;
    float z =(float)rand()/(float)RAND_MAX * 4 - 4;

    float vx =(float)rand()/(float)RAND_MAX * 8 - 8;
    float vy =(float)rand()/(float)RAND_MAX * 8 - 8;
    float vz =(float)rand()/(float)RAND_MAX * 8 - 8;

    for(int i = 0; i<maxParticles; i++){
        Particle *p = new Particle( new Vector3f(x,y,z), new Vector3f(vx,vy,vz) ,1,5);
        particles.append(p);
        x = (float)rand()/(float)RAND_MAX * 4 - 4;
        y =(float)rand()/(float)RAND_MAX * 4 - 4;
        z =(float)rand()/(float)RAND_MAX * 4 - 4;

        vx = (float)rand()/(float)RAND_MAX * 8 - 8;
        vy =(float)rand()/(float)RAND_MAX * 8 - 8;
        vz =(float)rand()/(float)RAND_MAX * 8 - 8;

        indices[i] = i;
    }

    lifeTimer = startTimer(50);

}

Scene::~Scene(){
    this->particles.clear();
    delete &particles;
    delete[] particlesPos;
    delete[] particlesColor;
}

bool
Scene::initializeObjects()
{
    // Fond gris
    glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );

    base = new Basis(1.0f);

    //Initialisation des couleurs des particules
    for(int i = 0; i < maxParticles; i++){
        particlesColor[i*3 + 0] = 1;
        particlesColor[i*3 + 1] = 1;
        particlesColor[i*3 + 2] = 0;
    }

     //Chargement des shaders
    createShader( "Shaders/color" );

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }

    return true;
}

void
Scene::render()
{

    // Initialisation de la caméra
        float eyeX, eyeY, eyeZ;
        eyeX = 5.0*cos(-moveX/300.0)*cos(moveY/300.0);
        eyeY = 5.0*sin(-moveX/300.0)*cos(moveY/300.0);
        eyeZ = 5.0*sin(moveY/300.0);
        lookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 0, 1 );
        scale( zoom, zoom, zoom );
        zoom = 1;

    //GLMatrix MVP = camera.getProjectionMatrix() * camera.getViewMatrix();
    //glUniformMatrix4fv( 0, 1, GL_TRUE, MVP.data );

    transmitMVP(0);
    pushMatrix();
        base->draw();
     popMatrix();
    pushMatrix();
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, particlesPos );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, particlesColor );
        glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, particlesSpeed );
        glVertexAttribPointer( 3, 1, GL_FLOAT, GL_FALSE, 0, particlesAge );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glEnableVertexAttribArray( 2 );
        glEnableVertexAttribArray( 3 );
        glDrawElements( GL_POINTS, maxParticles, GL_UNSIGNED_INT, indices );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glDisableVertexAttribArray( 2 );
        glDisableVertexAttribArray( 3 );
    popMatrix();

}

void Scene::timerEvent(QTimerEvent* event){
    //qDebug()<< "time event";

    if (event->timerId() == lifeTimer){
        for(int i = 0; i < maxParticles; i++){
            particles[i]->decreaseLife();
        }
    }
    else{
        for(int i = 0; i < maxParticles; i++){
            particles[i]->updateStats(this->interval);
            particlesPos[i*3 + 0] = particles[i]->getPos().getX();
            particlesPos[i*3 + 1] = particles[i]->getPos().getY();
            particlesPos[i*3 + 2] = particles[i]->getPos().getZ();

            particlesSpeed[i*3 + 0] = particles[i]->getSpeed().getX();
            particlesSpeed[i*3 + 1] = particles[i]->getSpeed().getY();
            particlesSpeed[i*3 + 2] = particles[i]->getSpeed().getZ();

            particlesAge[i] = particles[i]->getAge();

            /*if (i%10 == 0){
                qDebug()<< i;
                qDebug()<< particlesPos[i*3 + 0];
                qDebug()<< particlesPos[i*3 + 1];
                qDebug()<< particlesPos[i*3 + 2];
            }*/
        }
    }

    updateGL();
}

void Scene::mousePressEvent(QMouseEvent* p_event){
    moveStartX = p_event->x();
    moveStartY = p_event->y();
}

void Scene::mouseMoveEvent(QMouseEvent* p_event){
    moveX += p_event->x() - moveStartX;
    moveY += p_event->y() - moveStartY;
    if(moveY > 300) moveY = 300;
    else if(moveY < -300) moveY = -300;

    moveStartX = p_event->x();
    moveStartY = p_event->y();
}


void Scene::wheelEvent(QWheelEvent* p_event){
    zoom *= 1 + (float)p_event->delta()/5000.0;
}

