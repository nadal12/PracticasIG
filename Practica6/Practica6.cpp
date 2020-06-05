#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// angle of rotation for the camera direction
float angle = 0.0f;

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f, ly = 0.0f;

// XZ position of the camera
float x = 0.0f, z = 5.0f, y = 1.75f;
bool freeview = false;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
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

	glPushMatrix();
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
	glPopMatrix();
}

void drawCircularTree(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);

	glPushMatrix();
	glColor3f(0.6, 0.3, 0.1);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	drawCylinder(6, 16, 12.0, 0.3);

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

	glPopMatrix();
	glPopMatrix();
}

void drawTriangularTree(float x, float y, float z) {
	glPushMatrix();
	glTranslatef(x, y, z);

	glPushMatrix();
	glColor3f(0.6, 0.3, 0.1);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	drawCylinder(6, 16, 10.0, 0.3);

	glColor3f(0.0, 0.3, 0.0);
	glTranslatef(0.0, 0.0, -6.0);
	//glutSolid(2.0, 20, 20);
	glPopMatrix();

	glPopMatrix();
}
//==========================================================================//


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
// Common Render Items for all subwindows
void renderScene2() {

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

	drawCircularTree(2.5f, 0.0f, 0.0f);
	drawCircularTree(9.5f, 0.0f, 0.0f);
	drawCircularTree(15.5f, 0.0f, 0.0f);
	drawCircularTree(25.5f, 0.0f, 0.0f);
	drawCircularTree(35.5f, 0.0f, 0.0f);
}

// Display func for main window
void renderScene() {
	glutSetWindow(mainWindow);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

// Display func for sub window 1
void renderScenesw1() {

	glutSetWindow(subWindow1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, 1.0f, 0.0f);

	renderScene2();

	// display fps in the top window
	frame++;

	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf_s(s, "Lighthouse3D - FPS:%4.2f",
			frame * 1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}

	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	renderBitmapString(5, 30, 0, GLUT_BITMAP_HELVETICA_12, s);
	glPopMatrix();

	restorePerspectiveProjection();

	glutSwapBuffers();
}

// Display func for sub window 2
void renderScenesw2() {

	glutSetWindow(subWindow2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x, y + 30, z,
		x, y - 1, z,
		lx, 0, lz);

	// Draw red cone at the location of the main camera
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(x, y, z);
	glRotatef(180 - (angle + deltaAngle) * 180.0 / 3.14, 0.0, 1.0, 0.0);
	glutSolidCone(0.2, 0.8f, 4, 4);
	glPopMatrix();

	renderScene2();

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

// Global render func
void renderSceneAll() {

	// check for keyboard movement
	if (deltaMove) {
		computePos(deltaMove);
		glutSetWindow(mainWindow);
		glutPostRedisplay();
	}

	renderScene();
	renderScenesw1();
	renderScenesw2();
	//renderScenesw3();
}

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
}

void pressKey(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_UP: deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
	glutSetWindow(mainWindow);
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
	mainWindow = glutCreateWindow("Etapa 6 Informática Gráfica");

	// callbacks for main window
	glutDisplayFunc(renderSceneAll);
	glutReshapeFunc(changeSize);

	// Removing the idle function to save CPU and GPU
	//glutIdleFunc(renderSceneAll);
	init();

	subWindow2 = glutCreateSubWindow(mainWindow, (w + border) * 0.75, border, w / 4 - border * 3 / 2, h / 4 - border * 3 / 2);
	glutDisplayFunc(renderScenesw2);
	init();

	// sub windows
	subWindow1 = glutCreateSubWindow(mainWindow, border, border, w - 2 * border, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw1);
	init();



	/*subWindow3 = glutCreateSubWindow(mainWindow, (w + border) / 2, (h + border) / 2, w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw3);
	init();
	*/
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}