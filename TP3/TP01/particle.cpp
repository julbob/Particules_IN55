#include "particle.h"
#include "QDebug"

Particle::Particle(Vector3f* pos, Vector3f* speed, GLfloat size,GLfloat weight){
    this->pos = *pos;
    this->life =  rand()%75;
    this->size = size;
    this->speed = *speed;
    this->weight = weight;
   }


Vector3f Particle::getPos(){
    return this->pos;
}

GLfloat Particle::getAge(){
    return this->age;
}

Vector3f Particle::getSpeed(){
    return this->speed;
}

void Particle::decreaseLife(){
    life--;
    if (life == 0){
        this->pos.setX((float)rand()/(float)RAND_MAX * 4 - 4);
        this->pos.setY((float)rand()/(float)RAND_MAX * 4 - 4);
        this->pos.setZ((float)rand()/(float)RAND_MAX * 4 - 4);

        this->speed.setZ((float)rand()/(float)RAND_MAX * 8 - 8);
        this->speed.setX((float)rand()/(float)RAND_MAX * 8 - 8);
        this->speed.setY((float)rand()/(float)RAND_MAX * 8 - 8);

        this->life = rand()%75;
        this->age = 0.f;
    }
}

void Particle::updateStats(float delta){

    this->age =  this->age + delta/1000;
    //Pesanteur
    this->speed.setY(this->speed.getY() - (g * delta/1000));

    //this->pos.setX(this->pos.getX() + this->speed.getX()*delta/1000);
    //this->pos.setY(this->pos.getY() + this->speed.getY()*delta/1000);
    //this->pos.setZ(this->pos.getZ() + this->speed.getZ()*delta/1000);
}






