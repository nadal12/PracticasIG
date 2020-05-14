#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include "lightsMaterials.hpp"
#include <cmath>
#include <iostream>
#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 

// init of colors (static members)
GLfloat LightsMaterials::black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat LightsMaterials::white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightsMaterials::red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat LightsMaterials::green[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat LightsMaterials::blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat LightsMaterials::yellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
GLfloat LightsMaterials::magenta[] = { 1.0f, 0.0f, 1.0f, 1.0f };
GLfloat LightsMaterials::cyan[] = { 0.0f, 1.0f, 1.0f, 1.0f };
static GLfloat lightDiffuseColor[] = { 1.0, 1.5, 1.0, 1.0 };  /* XXX Green = 1.5 */


LightsMaterials::LightsMaterials() : nRot(0), precRot(128)
{
    init();
}


void LightsMaterials::init()
{
    // ==== SET UP LIGHTS
    glEnable(GL_LIGHTING);
    // disable the default qglviewer light !!
    glEnable(GL_LIGHT0);
    // create a new light on GL_LIGHT1
    //glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);
    // directional light (4th parameter w=0), coming along +z axis :
    //  ==> IN THE DRAW METHOD!
    // 	GLfloat light1_position[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    // 	glLightfv(GL_LIGHT1, GL_POSITION, light1_position); 

    // colors in each light component of the reflection
    // the second parameters can be: GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR,
    //   GL_POSITION, GL_SPOT_DIRECTION, GL_SPOT_EXPONENT, GL_SPOT_CUTOFF,
    //   GL_CONSTANT_ATTENUATION, GL_LINEAR_ATTENUATION
    glLightfv(GL_LIGHT1, GL_AMBIENT, black);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);

    // greenish light for the ambient
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuseColor);
    GLfloat lightPosition[4] = { 0.0, 0.0, 5.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // TODO 
    //  1. remove light components, change colors... what to expect? what result do you have?
    //  2. add new lights! (spot, ...)

    glLightfv(GL_LIGHT2, GL_AMBIENT, black);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, red);
    glLightfv(GL_LIGHT2, GL_SPECULAR, red);

    glClearColor(0.0f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < 4; i++)
        light2Pos[i] = 0;
}

void LightsMaterials::animate()
{
    float r = 5.f * M_PI * 2.f * nRot / (float)precRot;
    light2Pos[0] = cos(r) * 5.f;
    light2Pos[1] = sin(r) * 5.f;
    nRot++; nRot %= precRot;
    glLightfv(GL_LIGHT2, GL_POSITION, light2Pos);
}

void LightsMaterials::draw(int pass)
{
    init();
    // ==== PLACE LIGHTS
    // Most set up are in the init() method.
    // However, lights defined in the scene referentiel must be positionned 
    // at each draw() invocation.
    //
    // directional light (4th parameter w=0), coming along +z axis :
    GLfloat light1_position[] = { 0.0f, 0.0f, 1.0f, 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


    // TODO ?
    //  1. animated light: change the position at each draw?


    exampleMaterial();
    exampleColorMaterial();
    exampleBlending();
}


void LightsMaterials::exampleMaterial()
{
    GLfloat* no_color = black;

    // === CREATE SPHERES WITH DIFFERENT MATERIALS
    // Exemple adapted from the OpenGL Programming Guide (The Red Book)
    // Note that since OpenGL is a state machine, some glMaterial* calls 
    // are only here for clarity.

    glDisable(GL_COLOR_MATERIAL);  // MANDATORY to use glMaterial!!

    // 	glMaterial*(face, pname, param)
    // specifies a light property for a given reflection component
    // with face in: GL_FRONT_AND_BACK (default), GL_FRONT or GL_BACK
    // and pname in: GL_AMBIENT, GL_DIFFUSE, GL_AMBIENT_AND_DIFFUSE, 
    //          GL_SPECULAR, GL_SHININESS, GL_EMISSION, GL_COLOR_INDEXES

    GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_ambient_color[] = { 0.8f, 0.8f, 0.2f, 1.0f };
    GLfloat mat_diffuse[] = { 0.1f, 0.5f, 0.8f, 1.0f };
    GLfloat no_shininess[] = { 0.0f };
    GLfloat low_shininess[] = { 5.0f };
    GLfloat high_shininess[] = { 100.0f };
    GLfloat mat_emission[] = { 0.3f, 0.2f, 0.2f, 0.0f };

    glPushMatrix();

    glPushMatrix();
    glTranslatef(-3.75F, 3.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_color);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25, 3.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.25, 3.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75, 3.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_color);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.75, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_color);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25f, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.25, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75, 0.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_color);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.75f, -3.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_color);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.25, -3.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.25, -3.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_color);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75F, -3.0f, 0.0f);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_color);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glutSolidSphere(1.0f, 24, 24);
    glPopMatrix();

    glPopMatrix();
}



// Another method to set up materials :
// 	glColorMaterial(face, mode)
// with face in: GL_FRONT_AND_BACK (default), GL_FRONT or GL_BACK
// and mode in:  GL_AMBIENT_AND_DIFFUSE (default), GL_AMBIENT, GL_DIFFUSE,
//               GL_SPECULAR or GL_EMISSION
// Next calls to gelColor* applies to the selection reflection component
//
void LightsMaterials::exampleColorMaterial()
{
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.0f);

    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_AMBIENT);
    // 	glColor3f(0.2f, 0.2f, 0.2f);
    glColor3fv(black);
    glColorMaterial(GL_FRONT, GL_EMISSION);
    glColor3fv(black);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColor3fv(red);		// no glColor changes diffuse reflection

    glutSolidSphere(1.5f, 24, 24);

    glDisable(GL_COLOR_MATERIAL);

    glPopMatrix();
}



// 	glBlendFunction(srcFactor, destFactor)
// with factor in: GL_ZERO, GL_ONE, GL_DST_COLOR, GL_SRC_COLOR, 
//                 GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR,
//                 GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, DL_DST_ALPHA,
//                 GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA_SATURATE

void LightsMaterials::exampleBlending()
{
    glEnable(GL_CULL_FACE);	// do not display back faces
    // TODO disable backface culling: what happens?

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -3.0f);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_BLEND);

    // 1. draw a green sphere (no transparency)
    glColor3fv(green);
    // override the dst with src value
    glBlendFunc(GL_ONE, GL_ZERO);
    glutSolidSphere(1.5f, 24, 24);

    // 2. draw a second yellow sphere, with alpha = 0.25
    //    => 0.75 of the dst color, .25 of src one
    glTranslatef(3.0f, 0.0f, 0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 0.0f, 0.25f);
    glutSolidSphere(2.0f, 24, 24);


    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);

    glPopMatrix();
}