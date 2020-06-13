#include <stdio.h>
#include <windows.h>
#include <gl\gl.h>
#include <stdlib.h>
#include <math.h>
#include "tgload.h"
#include "Model_OBJ.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// angle of rotation for the camera direction
float angle = 0.0f;

// angle pel moviment de les aspes del molí: obj articulat
GLfloat fAngulo;

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;

// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 1.75f;
bool freeview = false;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove, gammaMove = 0;
int xOrigin = -1;

// width and height of the window
int h, w;

// variables to compute frames per second
int frame;
long time, timebase;
char s[50];

// variables to hold window identifiers
int mainWindow, subWindow1, subWindow2;
//border between subwindows
int border = 6;

bool niebla = false;
bool rotacio = true;
bool sun = true; 

//Menus
// menu status
// Constant definitions for Menus
#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

#define FILL 1
#define LINE 2

#define SHRINK 1
#define NORMAL 2

// Pop up menu identifiers
int fillMenu, menutextura, mainMenu, llumMenu;

int menuFlag = 0;
//

#define MAX_NO_TEXTURES 8

//Paredes y techo. 
#define CDAV 0
#define CDRE 1
#define CDAR 2
#define CESQ 3
#define CADA 5

#define TREE_WOOD 6
#define TREE_FLOWERS 7

GLuint texture_id[MAX_NO_TEXTURES];

//Llums
GLfloat streetLightPosition[] = { 0.0f, 1.0f, 1.0f };
GLfloat ambientLight[] = { 0.0f, 0.0f, 0.0f, 0.3f };

GLfloat especularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat difuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };

//Objectes (.obj)
Model_OBJ objecte;
Model_OBJ OSO;
Model_OBJ Vallas;
Model_OBJ pato;

GLfloat anglerotacio = 0;


void initTexture(void)
{

	image_t temp_image; // variável que irá armazenar a textura a ser usada

	// Habilita o uso de textura 
	glEnable(GL_TEXTURE_2D);

	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Define quantas texturas serão usadas no programa 
	glGenTextures(1, texture_id);  // 1 = uma textura;
									// texture_id = vetor que guardas os números das texturas

	// Define os números da textura dos cubos
	//Paredes y techo. 
	texture_id[CDAV] = 1001;
	texture_id[CDRE] = 1002;
	texture_id[CDAR] = 1003;
	texture_id[CESQ] = 1004;
	texture_id[CADA] = 1005;

	//Trees.
	texture_id[TREE_WOOD] = 1006;
	texture_id[TREE_FLOWERS] = 1007; 

	// ****
	// Define a textura do objeto da ESQUERDA
	// ****
	glBindTexture(GL_TEXTURE_2D, texture_id[CDAV]);
	tgaLoad( "textures/skybox2_pz.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[CDRE]);
	tgaLoad("textures/skybox2_px.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[CDAR]);
	tgaLoad("textures/skybox2_nz.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[CESQ]);
	tgaLoad("textures/skybox2_nx.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[CADA]);
	tgaLoad("textures/skybox2_py.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[TREE_WOOD]);
	tgaLoad("textures/treeWood.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);

	glBindTexture(GL_TEXTURE_2D, texture_id[TREE_FLOWERS]);
	tgaLoad("textures/TreeFlowers.tga", &temp_image, TGA_FREE | TGA_LOW_QUALITY);
}

void PintarCel()
{
	glColor3f(1, 1, 1);
	// Desenha Cubo 1

	// define qual das texturas usar
	glBindTexture(GL_TEXTURE_2D, texture_id[CDAV]);

	glBegin(GL_QUADS);
	//Davant
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100.0f, -100.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0f, -100.0f, -100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, 100.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, 100.0f, -100.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	//Dreta
	glBindTexture(GL_TEXTURE_2D, texture_id[CESQ]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(100, -100.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0f, -100.0f, 100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100.0f, 100.0f, -100.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	//Darrera
	glBindTexture(GL_TEXTURE_2D, texture_id[CDAR]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(100, -100.0f, 100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100.0f, -100.0f, 100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100.0f, 100.0f, 100.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	//Esquerra
	glBindTexture(GL_TEXTURE_2D, texture_id[CDRE]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, -100.0f, 100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100.0f,-100.0f, -100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-100.0f, 100.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-100.0f, 100.0f, 100.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	//Adalt
	glBindTexture(GL_TEXTURE_2D, texture_id[CADA]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-100, 100.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-100.0f, 100.0f, 100.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(100.0f, 100.0f, -100.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

///////////////////////////////////////////////////////////////////////////////
//							EXPERIMENT COORD ESF?RIQUES						 //
GLdouble PI = 3.1415926535897932384626433832795;
GLdouble beta = PI / 2;
// Tecles d'estat. Aquestes variables seran 0 quan no s'apretin les tecles
float betaAngle = 0.0f;
int yOrigin = -1;
//===========================================================================//
void setProjection(int w1, int h1)
{
	float ratio;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	ratio = 1.0f * w1 / h1;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w1, h1);

	// Set the clipping volume
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void changeSize(int w1, int h1) {

	if (h1 == 0)
		h1 = 1;

	// we're keeping these values cause we'll need them latter
	w = w1;
	h = h1;


	// set subwindow 2 as the active window
	glutSetWindow(subWindow2);
	// resize and reposition the sub window
	glutPositionWindow((w + border) *0.75, border);
	glutReshapeWindow(w / 4 - border * 3 / 2, h / 4 - border * 3 / 2);
	setProjection(w / 4 - border * 3 / 2, h / 4 - border * 3 / 2); 
	
	
	// set subwindow 1 as the active window
	glutSetWindow(subWindow1);
	// resize and reposition the sub window
	glutPositionWindow(border, border);
	glutReshapeWindow(w,h);
	setProjection(w,h);

	
	
}

//////////////////////////////////////////////////////////////////////////////
//				TOT LO QUE ÉS PER CONSTRUIR ELS OBJECTES					//
void drawCylinder(int numMajor, int numMinor, float height, float radius) {
	
	double majorStep = height / numMajor;
	double minorStep = 2.0 * PI / numMinor;
	int i, j;

	for (i = 0; i < numMajor; ++i) {
		GLfloat z0 = 0.5 * height - i * majorStep;
		GLfloat z1 = z0 - majorStep;
		glPushMatrix();
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0; j <= numMinor; ++j) {
			
			double a = j * minorStep;
			GLfloat x = radius * cos(a);
			GLfloat y = radius * sin(a);
			glNormal3f(x / radius, y / radius, 0.0);
			glTexCoord2f(j / (GLfloat)numMinor, i / (GLfloat)numMajor);
			glVertex3f(x, y, z0);

			glNormal3f(x / radius, y / radius, 0.0);
			glTexCoord2f(j / (GLfloat)numMinor, (i + 1) / (GLfloat)numMajor);
			glVertex3f(x, y, z1);
		}
		glEnd();
		glPopMatrix();
	}
}

void drawPyramid(float x, float y, float z) {

	glPushMatrix();

	glBegin(GL_QUADS);
	glVertex3d(-4, 0, -4);//4
	glVertex3d(-4, 0, 4);//3
	glVertex3d(4, 0, 4);//2
	glVertex3d(4, 0, -4);//1
	glEnd();

	//--------Cara 4 
	glBegin(GL_TRIANGLES);
	//vértices en 3d
	glVertex3d(0, 4, 0);
	glVertex3d(-4, 0, -4);//1
	glVertex3d(4, 0, -4);//4
	glEnd();

	//--------Cara 1
	glBegin(GL_TRIANGLES);
	//vértices en 3d
	glVertex3d(0, 4, 0);
	glVertex3d(4, 0, -4);
	glVertex3d(4, 0, 4);
	glEnd();

	//--------Cara 3
	glBegin(GL_TRIANGLES);
	//vértices en 3d
	glVertex3d(0, 4, 0);
	glVertex3d(-4, 0, 4);
	glVertex3d(-4, 0, -4);
	glEnd();

	//-------Cara 2
	glBegin(GL_TRIANGLES);
	//vértices en 3d
	glVertex3d(0, 4, 0);
	glVertex3d(4, 0, 4);
	glVertex3d(-4, 0, 4);
	glEnd();
	glPopMatrix();
}

void drawlightbulb() {

}

// FAROLA
void draw_streetlight(float x, float y, float z) {

	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(0.5, 0.5, 0.5);

	glRotatef(-90, 1, 0, 0);
	drawCylinder(6, 16, 1.0, 0.1);
	glTranslatef(0, 0, 2.0f);
	glColor3f(0.8, 0.8, 0.8);
	drawCylinder(6, 16, 3.0, 0.09);

	glPushMatrix();
	glTranslatef(0, -0.09, 1);
	glScalef(1, 0.1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 2);
	glColor3f(0.6, 0.6, 0.6);
	glutWireCone(0.4, 0.25, 25, 25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 1.8);
	glColor3f(1, 1, 1);
	glScalef(0.2, 0.2, 0.2);
	glutWireDodecahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 1.8);
	glColor3f(1, 0.9, 0);
	glScalef(0.2, 0.4, 0.2);

	//LLum de la farola. 
	glLightfv(GL_LIGHT0, GL_POSITION, streetLightPosition);
	glutSolidOctahedron();
	glPopMatrix();
	glPopMatrix();
}

// Aspa vertical
void drawBladeV(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(1, 1, 1);
	glRotated(90, 0, 1, 0);
	drawCylinder(10, 10, 8, 0.04);
	glPopMatrix();
}
//Aspa horitzontal
void drawBladeH(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(1, 1, 1);
	glRotated(90, 1, 0, 0);
	drawCylinder(10, 10, 8, 0.04);
	glPopMatrix();
}

// MOLÍ
void draw_windmill(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);

	//Paret
	glPushMatrix();
	glColor3f(0.6, 0.3, 0.1);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	drawCylinder(6, 16, 18, 4);

	//Teulada
	glPushMatrix();
	glColor3f(0.7, 0.4, 0.2);
	glTranslatef(0.0, 0.0, -9.0);
	glRotatef(-180, 1.0f, 0.0f, 0.0f);
	glutSolidCone(4, 3, 25, 25);
	glPopMatrix();
	glPopMatrix();

	//Palito
	glPushMatrix();
	glColor3f(0.4, 0.1, -0.1);
	glTranslatef(0.0, 7.0 , -4.0);
	drawCylinder(6, 16, 1, 0.1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.4, 0.1, -0.1);
	glTranslatef(0.0, 7.0 , -4.5);
	glutSolidSphere(0.1, 100, 100);
	glPopMatrix();
	
	//Aspes moli
	glPushMatrix();
	glTranslatef(0, 7, 0);
	glRotatef(fAngulo, 0.0f, 0.0f, -1.0f);
	glTranslatef(0, -7, 0);
	drawBladeV(0.0, 7.0, -4.5);
	drawBladeH(0.0, 7.0, -4.5);
	glPopMatrix();


	glPopMatrix();
}


void drawFence(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(0, 1, 0);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	drawCylinder(6, 16, 1, 0.05);
	glColor3f(0, 1, 1);
	glTranslatef(0, 0, 0.7);
	drawCylinder(6, 16, 1, 0.05);
	glTranslatef(1.5, 0, 0);
	glColor3f(1, 1, 0);
	drawCylinder(6, 16, 1, 0.05);
	glTranslatef(0, 0, 0.5);
	drawCylinder(6, 16, 1, 0.05);
	glPopMatrix();
}

// ARBRE
void drawCircularTree(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);

	glPushMatrix();
	glColor3f(0.6, 0.3, 0.1);
	glRotatef(90, 1.0f, 0.0f, 0.0f);


	glBindTexture(GL_TEXTURE_2D, texture_id[TREE_WOOD]);
	drawCylinder(6, 16, 12.0, 0.3);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Textures per sa part superior des arbres. 
	glEnable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, texture_id[TREE_FLOWERS]);

	glPushMatrix();
	glColor3f(0.0, 0.3, 0.0);
	glTranslatef(0.0, 0.0, -8.5);
	glutSolidSphere(2.0, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.0, 0.0, -6.5);
	glutSolidSphere(2.0, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0, 0.0, -6.5);
	glutSolidSphere(2.0, 20, 20);
	glPopMatrix();

	//Desactivar textures part superior des arbres. 
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_GEN_S); //enable texture coordinate generation
	glDisable(GL_TEXTURE_GEN_T);

	glPopMatrix();
	glPopMatrix();
}

// CEDRO
void drawTriangularTree(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);

	glPushMatrix();
	glColor3f(0.6, 0.3, 0.1);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	drawCylinder(6, 16, 8.0, 0.3);
	
	//Primera pirámide
	glPushMatrix();
	glColor3f(0.0, 0.3, 0.0);
	glTranslatef(0.0, 0.0, -4.0);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	drawPyramid(0.0, 0.0f, 0.0f);
	glPopMatrix();

	//Segunda pirámide
	glPushMatrix();
	glColor3f(0.0, 0.3, 0.0);
	glTranslatef(0.0, 0.0, -6.0);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	drawPyramid(0.0, 0.0f, 0.0f);
	glPopMatrix();

	//Tercera Pirámide
	glPushMatrix();
	glColor3f(1.0, 0.3, 0.0);
	glTranslatef(0.0, 0.0, -8.0);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	drawPyramid(0.0, 0.0f, 0.0f);
	glPopMatrix();
	

	glPopMatrix();
	glPopMatrix();
	
}

//==========================================================================//

GLfloat decrementarAngulo(GLfloat angulo) {
	if (angulo > 360) {
		angulo -= 360;
	}
	return angulo;
}

void renderBitmapString(
	float x,
	float y,
	float z,
	void* font,
	char* string) {

	char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, w, h, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

//////////////////////////////////////////////////////////
//				ACTUALITZACIÓ COORDENADES X i Z			//
void computePos(float deltaMove,float gammaMove) {
	// deltaMove => moviment eix z
	// gammaMove => moviment eix x
	if (deltaMove != 0) {
		x += deltaMove * lx * 0.1f;
		z += deltaMove * lz * 0.1f;
	}
	if (gammaMove != 0) {
		x += gammaMove * lz * 0.1f;
		z += gammaMove * (-lx) * 0.1f;
	}
	//Si volem camera free view
	if (freeview)
	{
		y += deltaMove * ly * 0.1f;
	}
	else
	{
		y = 1.75;
	}
}

void angles() {
	anglerotacio += 1;
	if (anglerotacio > 360) {
		anglerotacio -= 360;
	}

}


void renderItems() {//======================================================//

	//glLoadIdentity();
	
	// Terra
	/*
	glPushMatrix();
	glColor3f(1.0f, 0.6f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
	glPopMatrix();
	*/
	printf("%lf\n", x);
	printf("%lf\n", y);
	printf("%lf\n", z);
	
	drawCircularTree(38.0f, 1.0f,-30.0f);
	drawCircularTree(44.0f, 1.0f, -35.0f);
	glPushMatrix();
	glTranslatef(44, 1, -30);
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	draw_streetlight(-3, 0, 0);
	glPopMatrix();
	glColor3f(1.5, 0.7, 0.3);
	OSO.Draw();
	glEnable(GL_CULL_FACE);
	glPopMatrix();
	drawCircularTree(50.0f, 1.0f, -30.0f);
	drawCircularTree(44.5f, 1.0f, -25.0f);

	drawCircularTree(20, 1.0f, -10);
	drawCircularTree(30, 1.0f, -20);
	drawCircularTree(10, 1.0f, -30);
	drawCircularTree(0, 1.0f, -40);

	// Molí
	draw_windmill(50, 0, -10);

	//Valla
	glPushMatrix();
	glTranslated(40, -0.5, -20);
	glColor3f(0.7, 0.5, 0.3);
	Vallas.Draw();

	glScalef(0.02f, 0.02f,0.02f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);

	glTranslated(50, -5.0, 65);
	pato.Draw();

	glTranslated(40, -5.0, 0);
	pato.Draw();

	glRotatef(-45, 0.0f, 0.0f, 1.0f);
	glTranslated(50, -10.0, 0);
	pato.Draw();

	glTranslated(45, -10.0, 0);
	pato.Draw();

	draw_streetlight(0,1,15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(0,4,0);
	//Textures per sa part superior des arbres. 
	glColor3f(1.39, .69, .19);
	
	objecte.Draw();
	

	glPopMatrix();



	if (niebla) {
		glEnable(GL_FOG);

	}
	else {
		glDisable(GL_FOG);
	}

	//Activam pntar cares per dedins
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	PintarCel();
	glPopMatrix();
	glEnable(GL_CULL_FACE);

	

}
//==============================================//



//////////////////////////////////////////////////////////
//									ESCENA				//
// Display func for main window
void renderScene() {
	glutSetWindow(mainWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

// WINDOW 1: VISIÓ PRINCIPAL 1a PERSONA ESCENA
void renderScenesw1() {

	glutSetWindow(subWindow1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x, y, z,
		(GLdouble)x + lx, (GLdouble)y + ly, (GLdouble)z + lz,
		0.0f, 1.0f, 0.0f);

	
	// display fps in the top window
	frame++;

	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf_s(s, "Lighthouse3D - FPS:%4.2f",
			frame * 1000.0 / (time - (GLdouble) timebase));
		timebase = time;
		frame = 0;
	}

	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1, 0, 0);
	renderBitmapString(5, 30, 0, GLUT_BITMAP_HELVETICA_12, s);
	glPopMatrix();

	restorePerspectiveProjection();
	

	renderItems();

	

	glutSwapBuffers();
}

// WINDOW 2: Mini mapa
void renderScenesw2() {

	glutSetWindow(subWindow2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x, (GLdouble) y + 13, z,
		x, (GLdouble) y - 1, z,
		lx, 0, lz);

	// Draw red cone at the location of the main camera
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(x, y, z);
	glRotatef(180 - ((double)angle + deltaAngle) * 180.0 / 3.14, 0.0, 1.0, 0.0);
	glutSolidCone(0.2, 0.8f, 4, 4);
	glPopMatrix();

	renderItems();

	glutSwapBuffers();
}

// Display func for sub window 3
/*void renderScenesw3() {

	glutSetWindow(subWindow3);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x - lz * 10, y, z + lx * 10,
		x, y, z,
		0.0f, 1.0f, 0.0f);

	// Draw red cone at the location of the main camera
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(x, y, z);
	glRotatef(180 - (angle + deltaAngle) * 180.0 / 3.14, 0.0, 1.0, 0.0);
	glutSolidCone(0.2, 0.8f, 4, 4);
	glPopMatrix();

	renderScene2();

	glutSwapBuffers();
}*/

// Global render func: DISPLAY
void renderSceneAll() {
	// check for keyboard movement
	if (deltaMove || gammaMove) {
		computePos(deltaMove, gammaMove);
		glutSetWindow(mainWindow);
		glutPostRedisplay();
	}
	
	renderScene();
	renderScenesw1();
	renderScenesw2();
	//renderScenesw3();
}

void Idle(void) {
	// Incrementamos el ángulo
	if (rotacio) {
		fAngulo += 1.0f;
		// Si es mayor que dos pi la decrementamos
		if (fAngulo > 360)
			fAngulo -= 360;
		// Indicamos que es necesario repintar la pantalla
		glutPostRedisplay();
	}

	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);

	glLightfv(GL_LIGHT1, GL_SPECULAR, especularLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, difuseLight);

	if (sun) {
		//Apagar farolas
		glDisable(GL_LIGHT0);

		//Activar luz ambiente.
		glEnable(GL_LIGHT1);

		//Poner luz ambiente. 
		ambientLight[0] = 0.5f;
		ambientLight[1] = 0.5f;
		ambientLight[2] = 0.5f;

		especularLight[0] = 1.0f;
		especularLight[1] = 1.0f;
		especularLight[2] = 1.0f;

		difuseLight[0] = 0.5f;
		difuseLight[1] = 0.5f;
		difuseLight[2] = 0.5f;
	}
	else {
		//Encender farolas
		glEnable(GL_LIGHT0);

		//Desactivar luz ambiente.
		glDisable(GL_LIGHT1);

		//Quitar luz ambiente. 
		ambientLight[0] = 0.01f;
		ambientLight[1] = 0.01f;
		ambientLight[2] = 0.01f;		
	}
}
//======================================================//

// -----------------------------------
//             KEYBOARD
// -----------------------------------

void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27) {
		glutDestroyWindow(mainWindow);
		exit(0);
	}
	if (key == ' ') {
		//allibera eix y
		freeview = !freeview;
	}
	if (key == 'f') {
		niebla = !niebla;
	}
	if (key == 'r') {
		rotacio = !rotacio;
	}

}

void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP: deltaMove = 5.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -5.5f; break;
	case GLUT_KEY_RIGHT: gammaMove = -0.5f; break;
	case GLUT_KEY_LEFT: gammaMove = 0.5f; break;
	}
	glutSetWindow(mainWindow);
	glutPostRedisplay();
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	case GLUT_KEY_RIGHT:
	case GLUT_KEY_LEFT: gammaMove = 0; break;
	}
}

// -----------------------------------
//             MOUSE
// -----------------------------------

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngle = (x - xOrigin) * 0.001f;
		betaAngle = (y - yOrigin) * 0.001f;
		
		// update camera's direction
		lx = sin((double) angle + deltaAngle) * sin(beta + betaAngle);
		lz = -cos((double) angle + deltaAngle) * sin(beta + betaAngle);
		ly = cos(beta + betaAngle);
		glutSetWindow(mainWindow); 
		glutPostRedisplay();
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT) {

		// when the button is released
		if (state == GLUT_UP) {
			angle += deltaAngle;
			beta += betaAngle;
			deltaAngle = 0.0f;
			betaAngle = 0.0f;
			xOrigin = -1;
			yOrigin = -1;

		}
		else {// state = GLUT_DOWN

			xOrigin = x;
			yOrigin = y;
		}
	}
}
void processMenuStatus(int status, int x, int y) {

	if (status == GLUT_MENU_IN_USE)
		menuFlag = 1;
	else
		menuFlag = 0;
}

void processMainMenu(int option) {

	// nothing to do in here
	// all actions are for submenus
}

void processFillMenu(int option) {

	switch (option) {

	case FILL:niebla = true; break;
	case LINE: niebla = false; break;
	}
}



void processColorMenu(int option) {

	switch (option) {
	case RED:sun = true; break;
	case BLUE:sun = false; break;
	}
}

void processtexturemenu(int option) {

	switch (option) {
	case ORANGE:glEnable(GL_TEXTURE_2D); break;
	case GREEN: glDisable(GL_TEXTURE_2D); break;

	}
}

void createPopupMenus() {

	
	fillMenu = glutCreateMenu(processFillMenu);

	glutAddMenuEntry("Con niebla", FILL);
	glutAddMenuEntry("Sin niebla", LINE);

	llumMenu = glutCreateMenu(processColorMenu);
	glutAddMenuEntry("Día", RED);
	glutAddMenuEntry("Noche", BLUE);

	menutextura = glutCreateMenu(processtexturemenu);
	glutAddMenuEntry("Texturas activadas", ORANGE);
	glutAddMenuEntry("Texturas desactivadas", GREEN);
	

	mainMenu = glutCreateMenu(processMainMenu);

	glutAddSubMenu("Niebla", fillMenu);
	glutAddSubMenu("Luz", llumMenu);
	glutAddSubMenu("Texturas", menutextura);
	
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// this will allow us to know if the menu is active
	glutMenuStatusFunc(processMenuStatus);
}

// -----------------------------------
//             MAIN and INIT
// -----------------------------------

void init() {
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 1.0);
	glFogf(GL_FOG_END, 50.0);
	float color[] = { 0.5,0.5,0.5,0.001 };
	glFogfv(GL_FOG_COLOR, color);
	

	// register callbacks
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
}

void initLighting() {
	//Renderización de luz
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	//Activar llum de la farola.
	glEnable(GL_LIGHT0);
}

int main(int argc, char** argv) {

	// init GLUT and create main window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	mainWindow = glutCreateWindow("Etapa 6 Informática Gráfica");

	// callbacks for main window
	glutDisplayFunc(renderSceneAll);
	glutReshapeFunc(changeSize);


	// Removing the idle function to save CPU and GPU
	glutIdleFunc(Idle);
	init();
	
	subWindow2 = glutCreateSubWindow(mainWindow, (w + border) * 0.75, border, w / 4 - border * 3 / 2, h / 4 - border * 3 / 2);
	glutDisplayFunc(renderScenesw2);
	init();
	initTexture();
	initLighting();

	// sub windows
	subWindow1 = glutCreateSubWindow(mainWindow, border, border, w - 2 * border, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw1);
	init();
	initTexture();
	initLighting();

	/*subWindow3 = glutCreateSubWindow(mainWindow, (w + border) / 2, (h + border) / 2, w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw3);
	init();
	*/
	// enter GLUT event processing cycle

	//Carregar objecte. 

	char buffer[100];
	strcpy_s(buffer, "objects/Landscape.obj");
	objecte.Load(buffer);

	strcpy_s(buffer, "objects/granero.obj");
	OSO.Load(buffer);

	strcpy_s(buffer, "objects/vallas.obj");
	Vallas.Load(buffer);

	strcpy_s(buffer, "objects/pato.obj");
	pato.Load(buffer);

	// init Menus
	createPopupMenus();

	glutMainLoop();

	return 1;
}