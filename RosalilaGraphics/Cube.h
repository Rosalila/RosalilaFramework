#ifdef LINUX
#include <SDL2/SDL_image.h>
#endif

#ifdef OSX
#include <SDL2_image/SDL_image.h>
#endif

#include <SDL2/SDL_opengl.h>
#include <stdio.h>
#include <math.h>

#define NUM_PARTICLES    50          /* Number of particles  */
#define NUM_DEBRIS       50            /* Number of debris     */

/* GLUT menu entries */

#define PAUSE              0
#define NORMALIZE_SPEED    1
#define QUIT               2

class Cube
{
public:
    /* A particle */

    struct particleData
    {
      float   position[3];
      float   speed[3];
      float   color[3];
    };
    typedef struct particleData    particleData;


    /* A piece of debris */

    struct debrisData
    {
      float   position[3];
      float   speed[3];
      float   orientation[3];        /* Rotation angles around x, y, and z axes */
      float   orientationSpeed[3];
      float   color[3];
      float   scale[3];
    };
    typedef struct debrisData    debrisData;


    /* Globals */

    float pos_x;
    float pos_y;

    particleData     particles[NUM_PARTICLES];
    debrisData       debris[NUM_DEBRIS];
    int fuel;                /* "fuel" of the explosion */

    float angle;             /* camera rotation angle */

    int wantNormalize;   /* Speed vector normalization flag */
    int wantPause;       /* Pause flag */


    /* Light sources and material */

    GLfloat  light0Amb[4];
    GLfloat  light0Dif[4];
    GLfloat  light0Spec[4];
    GLfloat  light0Pos[4];

    GLfloat  light1Amb[4];
    GLfloat  light1Dif[4];
    GLfloat  light1Spec[4];
    GLfloat  light1Pos[4];

    GLfloat  materialAmb[4];
    GLfloat  materialDif[4];
    GLfloat  materialSpec[4];
    GLfloat  materialShininess;

    Cube();

    void setMaterialColor(float r,float g,float b,float a);

//    GLfloat  light0Amb[4] =  { 1.0, 0.6, 0.2, 1.0 };
//    GLfloat  light0Dif[4] =  { 1.0, 0.6, 0.2, 1.0 };
//    GLfloat  light0Spec[4] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat  light0Pos[4] =  { 0.0, 0.0, 0.0, 1.0 };
//
//    GLfloat  light1Amb[4] =  { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat  light1Dif[4] =  { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat  light1Spec[4] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat  light1Pos[4] =  { 0.0, 5.0, 5.0, 0.0 };
//
//    GLfloat  materialAmb[4] = { 0.25, 0.22, 0.26, 1.0 };
//    GLfloat  materialDif[4] = { 0.63, 0.57, 0.60, 1.0 };
//    GLfloat  materialSpec[4] = { 0.99, 0.91, 0.81, 1.0 };
//    GLfloat  materialShininess = 27.8;

    void logic();
    void newExplosion (float pos_x,float pos_y);
    void newSpeed (float dest[3]);
};
