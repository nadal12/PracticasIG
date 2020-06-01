#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>

//////////////////////////////////////////////////////////////////
//                               DEFINICI? DE VARIABLES         //
#define BASE_HEIGHT  0.25
#define BASE_WIDE    0.05

// angle of rotation for the camera direction
GLdouble angle = 0.0f;
GLfloat fAnguloFig2;

// actual vector representing the camera's direction
GLdouble lx = 0.0f, lz = -1.0f, ly = 0.0f;

// XZ position of the camera
GLdouble x = 0.0f, z = 5.0f, y = 1.5f;

// the key states. These variables will be zero
// when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

// width and height of the window
int h, w;

// variables to compute frames per second
int frame;
GLdouble time, timebase;
char s[50];

// variables to hold window identifiers
int mainWindow, subWindow1, subWindow2, subWindow3;
//border between subwindows
int border = 5;
//nombre per decidir quina figura pintam
int figura = 1;

bool forapitjar = false;
int prespect = 1;
bool freeview = false;
//Lorenz Atracctor
float xlorenz = 0.01;
float ylorenz = 0;
float zlorenz = 0;

float dx;
float dy;
float dz;

float dt = 0.01;

float a = 10;
float b = 5;
float c = 8.0 / 3.0;
struct Point
{
	float x, y, z;
	//unsigned char r, g, b, a;
};
std::vector< Point > points;

//Trajectoria
const int trajectoryLenght = 1000;
float trajectoryX[trajectoryLenght];
float trajectoryY[trajectoryLenght];
float trajectoryZ[trajectoryLenght];

int indexQ2 = 0;
//==============================================================//



///////////////////////////////////////////////////////////////////////////////
//							EXPERIMENT COORD ESF?RIQUES						 //
GLdouble PI = 3.1415926535897932384626433832795;
GLdouble beta = PI / 2;
// Tecles d'estat. Aquestes variables seran 0 quan no s'apretin les tecles
float betaAngle = 0.0f;
int yOrigin = -1;
//===========================================================================//



//////////////////////////////////////////////////////
//                                RESHAPE           //
// Aquesta funci? l'usarem pes reshape des viewport //
void setProjection(int w1, int h1)
{
	float ratio;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	ratio = 1.0f * w1 / h1;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION); //ProjectionView is the matrix that represents your camera's lens (aperture, far-field, near-field, etc).
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w1, h1);

	// Set the clipping volume
	gluPerspective(45, ratio, 0.1, 1000); //Referent a s'entorn, com el veus
	glMatrixMode(GL_MODELVIEW); //ModelView is the matrix that represents your camera (position, pointing, and up vector).
}
//Lo que a ses anteriors etapes li deiem reshape :D //
void changeSize(int w1, int h1) {

	if (h1 == 0)
		h1 = 1;

	// we're keeping these values cause we'll need them latter
	w = w1;
	h = h1;

	// set subwindow 1 as the active window
	// resize and reposition the sub window
	//glutPositionWindow(border, border);
	glutReshapeWindow(w, h);
	setProjection(w, h);
}
//==================================================//



//////////////////////////////////////////////////////////////////////////////
//				TOT LO QUE ÉS PER CONSTRUIR ELS OBJECTES					//
void drawCylinder(int numMajor, int numMinor, float height, float radius) {
	double majorStep = height / numMajor;
	double minorStep = 2.0 * PI / numMinor;
	int i, j;

	for (i = 0; i < numMajor; ++i) {
		GLfloat z0 = 0.5 * height - i * majorStep;
		GLfloat z1 = z0 - majorStep;

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
	}
}

// FAROLA
void draw_streetlight() {
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
	glutSolidOctahedron();
	glPopMatrix();
}
//==========================================================================//


/*
GLfloat decrementarAngulo(GLfloat angulo) {
	if (angulo > 360) {
		angulo -= 360;
	}
	return angulo;
}
*/

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

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
	//Si volem camera free view
	if (freeview)
	{
		y += deltaMove * ly * 0.1f;
	}
	else
	{
		y = 1.5;
	}

}

// Impresió objectes en l'escena
void render_items() {

	// Terra
	glColor3f(0.0f, 0.6f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Farola
	draw_streetlight();
}



// Display func
void renderScene() {
	// check for keyboard movement
	if (!forapitjar)
	{
		if (deltaMove) {
			computePos(deltaMove);
			glutPostRedisplay();
		}
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0, 1, 0);

	// Cridam la funció que imprimeix tots els objectes
	render_items();

	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();

	glPopMatrix();

	restorePerspectiveProjection();

	glutSwapBuffers();
}



// -----------------------------------
//             KEYBOARD
// -----------------------------------
void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27) // si apretes ESC te tanca sa finestra
	{
		exit(0);
	}

	if (key == ' ') {
		//allibera eix y
		freeview = !freeview;
	}
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
		//case GLUT_KEY_RIGHT: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
	glutPostRedisplay();
}


void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN: deltaMove = 0; break;
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
		lx = sin(angle + deltaAngle) * sin(beta + betaAngle);
		lz = -cos(angle + deltaAngle) * sin(beta + betaAngle);
		ly = cos(beta + betaAngle);

		glutPostRedisplay();
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (!forapitjar) {
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
}



// -----------------------------------
//             MAIN and INIT
// -----------------------------------

void init() {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// register callbacks
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
}

int main(int argc, char** argv) {
	// init GLUT and create main window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Etapa6");

	// callbacks for main window
	glutDisplayFunc(render_items);
	glutReshapeFunc(changeSize);

	// Removing the idle function to save CPU and GPU
	glutIdleFunc(renderScene);

	init();

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}