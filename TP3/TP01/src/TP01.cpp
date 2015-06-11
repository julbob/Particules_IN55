#include "TP01.h"

#include <iostream>
#include "particle.h"

using namespace std;


GLfloat angle1 = 00.0f;
GLfloat angle2 = 00.0f;
GLfloat taille = -2.0f;
const GLfloat g_AngleSpeed = 10.0f;

Particle* particle;


GLuint particles_position_buffer;
GLuint MaxParticles = 1;

static const GLfloat g_vertex_buffer_data[] = {
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
     -0.5f,  0.5f, 0.0f,
      0.5f,  0.5f, 0.0f,
};

static GLfloat* g_particule_position_size_data = new GLfloat[MaxParticles * 4];

GLuint billboard_vertex_buffer;

TP01::TP01()
{
	setWindowTitle(trUtf8("IN55-TP01"));

}


TP01::~TP01()
{
    delete particle;
}


bool
TP01::initializeObjects()
{
	// Fond gris
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glEnable( GL_DEPTH_TEST );

     //Chargement des shaders
    createShader( "Shaders/particle" );

    cout << "Shader particle: ";
    if (useShader( "particle" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }


    glGenBuffers(1, &billboard_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    glGenBuffers(1, &particles_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
    // Initialize with empty (NULL) buffer : it will be updated later, each frame.
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);


    /* Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "Particle.vertexshader", "Particle.fragmentshader" );

    // Vertex shader
    GLuint CameraRight_worldspace_ID  = glGetUniformLocation(programID, "CameraRight_worldspace");
    GLuint CameraUp_worldspace_ID  = glGetUniformLocation(programID, "CameraUp_worldspace");
    GLuint ViewProjMatrixID = glGetUniformLocation(programID, "VP");

    // fragment shader
    GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");*/

	return true;
}


void
TP01::render()
{

	// Initialisation de la caméra
    lookAt( 0 + angle2, 5 + angle1, 30, 0, 0, 0 );

    Vector3f pos = particle->getPos();
    g_particule_position_size_data[4*0+0] = pos.getX();
    g_particule_position_size_data[4*0+1] = pos.getY();
    g_particule_position_size_data[4*0+2] = pos.getZ();


    glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
    glBufferSubData(GL_ARRAY_BUFFER, 0, 0 * sizeof(GLfloat) * 4, g_particule_position_size_data);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
    glVertexAttribPointer(
        0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : positions of particles' centers
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        4,                                // size : x + y + z + size => 4
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    );



    /*pushMatrix();
        scale(4,4,4);
        particle->draw();
     popMatrix();*/

}


void
TP01::keyPressEvent( QKeyEvent* event )
{
	switch( event->key())
	{
		case Qt::Key_Escape:
			close();
			break;

		case Qt::Key_Left:
			angle1 -= g_AngleSpeed;
			break;

		case Qt::Key_Right:
			angle1 += g_AngleSpeed;
			break;

		case Qt::Key_Up:
			angle2 -= g_AngleSpeed;
            taille += 0.1;
            if (taille > 0)
                taille = 0;
			break;

		case Qt::Key_Down:
			angle2 += g_AngleSpeed;
            taille -= 0.1;
            if (taille < -6)
                taille = -6;
			break;

		case Qt::Key_R:
			angle1 = angle2 = 0.0f;
			break;
	}
}
