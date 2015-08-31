#include "Explosion.h"

Explosion::Explosion(int x, int y)
{
    iteration=0;
    duration=100;
    pos_x=0;
    pos_y=0;

    fuel = 0;                /* "fuel" of the explosion */

    angle = 0.0;             /* camera rotation angle */

    wantNormalize = 0;   /* Speed vector normalization flag */
    wantPause = 0;       /* Pause flag */


    /* Light sources and material */
//
    light0Amb[0]=1.0;
    light0Amb[1]=1.0;
    light0Amb[2]=1.0;
    light0Amb[3]=1.0;

    light0Dif[0]=1.0;
    light0Dif[1]=1.0;
    light0Dif[2]=1.0;
    light0Dif[3]=1.0;

    light0Spec[0]=1.0;
    light0Spec[1]=1.0;
    light0Spec[2]=1.0;
    light0Spec[3]=1.0;

    light0Pos[0]=1.0;
    light0Pos[1]=1.0;
    light0Pos[2]=1.0;
    light0Pos[3]=1.0;

    light1Amb[0]=1.0;
    light1Amb[1]=1.0;
    light1Amb[2]=1.0;
    light1Amb[3]=1.0;

    light1Dif[0]=1.0;
    light1Dif[1]=0.0;
    light1Dif[2]=0.0;
    light1Dif[3]=1.0;

    light1Spec[0]=1.0;
    light1Spec[1]=1.0;
    light1Spec[2]=1.0;
    light1Spec[3]=1.0;

    light1Pos[0]=0.0;
    light1Pos[1]=5.0;
    light1Pos[2]=5.0;
    light1Pos[3]=0.0;

    materialAmb[0]=255.0/255.0;
    materialAmb[1]=0.0/255.0;
    materialAmb[2]=0.0/255.0;
    materialAmb[3]=128.0/255.0;

    materialDif[0]=255.0/255.0;
    materialDif[1]=0.0/255.0;
    materialDif[2]=0.0/255.0;
    materialDif[3]=128.0/255.0;

    materialSpec[0]=255.0/255.0;
    materialSpec[1]=0.0/255.0;
    materialSpec[2]=0.0/255.0;
    materialSpec[3]=128.0/255.0;

    materialShininess = 10.0;

    newExplosion(x,y);
}

void Explosion::setMaterialColor(float r,float g,float b,float a)
{
    materialAmb[0]=r/255.0;
    materialAmb[1]=g/255.0;
    materialAmb[2]=b/255.0;
    materialAmb[3]=a/255.0;

    materialDif[0]=r/255.0;
    materialDif[1]=g/255.0;
    materialDif[2]=b/255.0;
    materialDif[3]=a/255.0;

    materialSpec[0]=r/255.0;
    materialSpec[1]=g/255.0;
    materialSpec[2]=b/255.0;
    materialSpec[3]=a/255.0;
}

void Explosion::logic()
{
    if (this->fuel > 0)
    {
        for (int i = 0; i < NUM_PARTICLES; i++)
        {
            this->particles[i].position[0] += this->particles[i].speed[0] * 0.2;
            this->particles[i].position[1] += this->particles[i].speed[1] * 0.2;
            this->particles[i].position[2] += this->particles[i].speed[2] * 0.2;

            this->particles[i].color[0] -= 1.0 / 500.0;
            if (this->particles[i].color[0] < 0.0)
            {
                this->particles[i].color[0] = 0.0;
            }

            this->particles[i].color[1] -= 1.0 / 100.0;
            if (this->particles[i].color[1] < 0.0)
            {
                this->particles[i].color[1] = 0.0;
            }

            this->particles[i].color[2] -= 1.0 / 50.0;
            if (this->particles[i].color[2] < 0.0)
            {
                this->particles[i].color[2] = 0.0;
            }
        }

        for (int i = 0; i < NUM_DEBRIS; i++)
        {
            this->debris[i].position[0] += this->debris[i].speed[0] * 0.5;
            this->debris[i].position[1] += this->debris[i].speed[1] * 0.5;
            this->debris[i].position[2] += this->debris[i].speed[2] * 0.5;

            this->debris[i].orientation[0] += this->debris[i].orientationSpeed[0] * 10;
            this->debris[i].orientation[1] += this->debris[i].orientationSpeed[1] * 10;
            this->debris[i].orientation[2] += this->debris[i].orientationSpeed[2] * 10;
        }

        --this->fuel;
    }

    this->angle += 0.7;  /* Always continue to rotate the camera */
    iteration++;
}

void Explosion::newExplosion (float pos_x,float pos_y)
{
//    this->pos_x=pos_x;
//    this->pos_y=pos_y;
//  int    i;
//
//  for (i = 0; i < NUM_PARTICLES; i++)
//    {
//      particles[i].position[0] = 0.0;
//      particles[i].position[1] = 0.0;
//      particles[i].position[2] = 0.0;
//
//      particles[i].color[0] = 1.0;
//      particles[i].color[1] = 1.0;
//      particles[i].color[2] = 0.5;
//
//      newSpeed (particles[i].speed);
//    }
//
//  for (i = 0; i < NUM_DEBRIS; i++)
//    {
//      debris[i].position[0] = 0.0;
//      debris[i].position[1] = 0.0;
//      debris[i].position[2] = 0.0;
//
//      debris[i].orientation[0] = 0.0;
//      debris[i].orientation[1] = 0.0;
//      debris[i].orientation[2] = 0.0;
//
//      debris[i].color[0] = 0.7;
//      debris[i].color[1] = 0.7;
//      debris[i].color[2] = 0.7;
//
//      debris[i].scale[0] = (20.0 *
//			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
//      debris[i].scale[1] = (20.0 *
//			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
//      debris[i].scale[2] = (20.0 *
//			    ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
//
//      newSpeed (debris[i].speed);
//      newSpeed (debris[i].orientationSpeed);
//    }
//
//  fuel = 100;
}

void Explosion::newSpeed (float dest[3])
{
//  float    x;
//  float    y;
//  float    z;
//  float    len;
//
//  x = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
//  y = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
//  z = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
//
//  /*
//   * Normalizing the speed vectors gives a "fireball" effect
//   *
//   */
//
//  if (wantNormalize)
//    {
//      len = sqrt (x * x + y * y + z * z);
//
//      if (len)
//	{
//	  x = x / len;
//	  y = y / len;
//	  z = z / len;
//	}
//    }
//
//  dest[0] = x;
//  dest[1] = y;
//  dest[2] = z;
}

void Explosion::render(int screen_width, int screen_height)
{
//    //  glViewport (0.0, 0.0, (GLfloat) screen_width, (GLfloat) screen_height);
//    //glDisable(GL_BLEND);
//    glDisable(GL_TEXTURE_2D);
//    glEnable(GL_BLEND);
//    glMatrixMode (GL_PROJECTION);
//    glLoadIdentity ();
//    gluPerspective (45.0, (GLfloat) screen_width / (GLfloat) screen_height, 0.1, 100.0);
//    glMatrixMode (GL_MODELVIEW);
//
//    glEnable (GL_LIGHT0);
//    glEnable (GL_LIGHT1);
//    glLightfv (GL_LIGHT0, GL_AMBIENT, this->light0Amb);
//    glLightfv (GL_LIGHT0, GL_DIFFUSE, this->light0Dif);
//    glLightfv (GL_LIGHT0, GL_SPECULAR, this->light0Spec);
//    glLightfv (GL_LIGHT0, GL_POSITION, this->light0Pos);
////    glLightfv (GL_LIGHT1, GL_AMBIENT, this->light1Amb);
////    glLightfv (GL_LIGHT1, GL_DIFFUSE, this->light1Dif);
////    glLightfv (GL_LIGHT1, GL_SPECULAR, this->light1Spec);
////    glLightfv (GL_LIGHT1, GL_POSITION, this->light1Pos);
//    glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
//    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, this->materialAmb);
//    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, this->materialDif);
//    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, this->materialSpec);
//    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, this->materialShininess);
//    glEnable (GL_NORMALIZE);
//
//    this->logic();
//
//
//    //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glLoadIdentity ();
//
//    /* Place the camera */
//    //
//    glPushMatrix ();
//    float pos_x=this->pos_x;
//    float pos_y=this->pos_y;
//    //camera align
////    pos_x-=camera_x;
////    pos_y+=camera_y;
//
//    pos_x+=650.0;
//    pos_y+=400.0;
//    glTranslatef (-((screen_width-pos_x)/2.0)/5.0, ((screen_height-pos_y)/2.0)/5.0, -100.0);
//    glRotatef (this->angle, 0.0, 1.0, 0.0);
//
//
//    /* If no explosion, draw cube */
//
//    if (this->fuel > 0)
//    {
//        glPushMatrix ();
//
//        glDisable (GL_LIGHTING);
//        glDisable (GL_DEPTH_TEST);
//
//        glBegin (GL_POINTS);
//
//        for (int i = 0; i < NUM_PARTICLES; i++)
//        {
//            glColor3fv (this->particles[i].color);
//            glVertex3fv (this->particles[i].position);
//        }
//
//        glEnd ();
//
//        glPopMatrix ();
//
//        glEnable (GL_LIGHTING);
//        glEnable (GL_LIGHT0);
//        glEnable (GL_DEPTH_TEST);
//
//        glNormal3f (0.0, 0.0, 1.0);
//
//        for (int i = 0; i < NUM_DEBRIS; i++)
//        {
//            glColor3fv (this->debris[i].color);
//
//            glPushMatrix ();
//
//            glTranslatef (this->debris[i].position[0],
//            this->debris[i].position[1],
//            this->debris[i].position[2]);
//
//            glRotatef (this->debris[i].orientation[0], 1.0, 0.0, 0.0);
//            glRotatef (this->debris[i].orientation[1], 0.0, 1.0, 0.0);
//            glRotatef (this->debris[i].orientation[2], 0.0, 0.0, 1.0);
//
////            glScalef (this->debris[i].scale[0],
////            this->debris[i].scale[1],
////            this->debris[i].scale[2]);
////            drawObject();
//
//            glPopMatrix ();
//        }
//    }
//    glPopMatrix();
}
