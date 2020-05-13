#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//////////////////////////////////////////////////////////////////
//                               DEFINICIÓ DE VARIABLES         //
#define BASE_HEIGHT  0.25
#define BASE_WIDE    0.05

// angle of rotation for the camera direction
GLdouble angle = 0.0f;
GLfloat fAnguloFig2;

// actual vector representing the camera's direction
GLdouble lx = 0.0f, lz = -1.0f, ly = 0.0f;

// XZ position of the camera
GLdouble x = 0.0f, z = 5.0f, y = 2.5f;

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
//==============================================================//



///////////////////////////////////////////////////////////////////////////////
//							EXPERIMENT COORD ESFÈRIQUES						 //
GLdouble PI = 3.1415926535897932384626433832795;
GLdouble beta = PI / 2;
// Tecles d'estat. Aquestes variables seran 0 quan no s'apretin les tecles
float betaAngle = 0.0f;
int yOrigin = -1;
//===========================================================================//



//////////////////////////////////////////////////////
//                                RESHAPE           //
// Aquesta funció l'usarem pes reshape des viewport //
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
	glutSetWindow(subWindow1);
	// resize and reposition the sub window
	glutPositionWindow(border, border);
	glutReshapeWindow(w - 2 * border, h / 2 - border * 3 / 2);
	setProjection(w - 2 * border, h / 2 - border * 3 / 2);

	// set subwindow 2 as the active window
	glutSetWindow(subWindow2);
	// resize and reposition the sub window
	glutPositionWindow(border, (h + border) / 2);
	glutReshapeWindow(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	setProjection(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);

	// set subwindow 3 as the active window
	glutSetWindow(subWindow3);
	// resize and reposition the sub window
	glutPositionWindow((w + border) / 2, (h + border) / 2);
	glutReshapeWindow(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	setProjection(w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
}
//==================================================//



/////////////////////////////////////////////////////////////////////
// Les següents dues funcions ens serviran per dibuixar les taules //
// Com construim una pota de la taula                              //
void draw_leg(float xt, float yt, float zt)
{
	glPushMatrix();
	glTranslatef(xt, yt, zt);
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
}
//   Construim l'objecte taula a partir de les potes definides     //
void draw_table()
{
	glColor4f(.82, .60, .16, 1);

	glPushMatrix();
	glTranslatef(0, -0.25, 0);
	glScalef(1, 0.1, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	draw_leg(0.45, -0.5, -0.45);
	draw_leg(0.45, -0.5, 0.45);
	draw_leg(-0.45, -0.5, -0.45);
	draw_leg(-0.45, -0.5, 0.45);
}
//=================================================================//



//////////////////////////////////////
// Si volguessim fer ninots de neu: //
void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.6f, 0.1f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);

	glColor3f(1.0f, 1.0f, 1.0f);

}
//==================================//


///////////////////////////
// EL CUB SOBRE LA TAULA //
void pintarObjecte() {

	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glRotated(70, 0, 0.5, 0.5);
	glRotatef(fAnguloFig2, 0.3f, 0.0f, 0.5f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireCube(0.5);
	glPopMatrix();
}
//=======================//



GLfloat decrementarAngulo(GLfloat angulo) {
	if (angulo > 360) {
		angulo -= 360;
	}
	return angulo;
}



/////////////////////////////////////////////////////////////////////////////////
//           Això crec que se usarà per printar es FPS per pantalla            //
void renderBitmapString(float x, float y, float z, void* font, char* string) {
	char* c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}
//=============================================================================//



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
}

// Common Render Items for all subwindows
void renderScene2() {

	// Draw ground

	glColor3f(0.0f, 0.6f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	//drawSnowMan();

	//glTranslatef(0, 2.0, 0.0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			figura++;
			glPushMatrix();
			glTranslatef(i * 10.0f, 2.0f, j * 10.0f);
			draw_table();
			glColor3f(i * 2, 0.0, j * 2);
			pintarObjecte();
			glPopMatrix();
		}
	}

	draw_table();

	// Draw 36 SnowMen
	/*for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++)
		{
			glPushMatrix();
			glTranslatef(i * 10.0f, 0.0f, j * 10.0f);
			drawSnowMan();
			glPopMatrix();
		}*/
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
	/*
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		-(x + lx) * (y + ly), (y + ly) * (z + lz), -(x + lx) * (y + ly)); //permetre que la normal varii sent sempre ortogonal al vector de la visió de la camara
*/
	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0,1,0); //permetre que la normal varii sent sempre ortogonal al vector de la visió de la camara


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
	renderBitmapString(5, 30, 0, GLUT_BITMAP_HELVETICA_12, s); // Això crec que és lo que mostra es FPS
	glPopMatrix();

	restorePerspectiveProjection();

	glutSwapBuffers();
}

// Display func for sub window 2
void renderScenesw2() {

	glutSetWindow(subWindow2);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(x, y + 15, z,
		x, y - 1, z,
		lx, 0, lz);

	// Draw red cone at the location of the main camera
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(x, y, z);
	glRotatef(180 - (angle + deltaAngle) * 180.0 / PI, 0.0, 1.0, 0.0);
	glutSolidCone(0.2, 0.8f, 4, 4);
	glPopMatrix();

	renderScene2();

	glutSwapBuffers();
}

// Display func for sub window 3
void renderScenesw3() {

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
}


// Global render func
void renderSceneAll() {
	fAnguloFig2 += 3.0f;
	fAnguloFig2 = decrementarAngulo(fAnguloFig2);

	// check for keyboard movement
	if (deltaMove) {
		computePos(deltaMove);
		glutSetWindow(mainWindow);
		glutPostRedisplay();
	}

	renderScene();
	renderScenesw1();
	renderScenesw2();
	renderScenesw3();
}

// -----------------------------------
//             KEYBOARD
// -----------------------------------

void processNormalKeys(unsigned char key, int xx, int yy) {

	if (key == 27) // si apretes ESC te tanca sa finestra
	{
		glutDestroyWindow(mainWindow);
		exit(0);
	}
	if (key == 'a')
	{
		y += 0.1;
	}
	if (key == 'z' & y > 2.5) //sa segona condicio es perque no pugui baixar si no ha pujat, que no traspassi es terra.
	{
		y -= 0.1;
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
		lx = sin(angle + deltaAngle) * sin(beta - betaAngle);
		lz = -cos(angle + deltaAngle) * sin(beta - betaAngle);
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
			beta -= betaAngle;
			deltaAngle = 0.0f;
			betaAngle = 0.0f;
			xOrigin = -1;
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
	mainWindow = glutCreateWindow("Etapa4");

	// callbacks for main window
	glutDisplayFunc(renderSceneAll);
	glutReshapeFunc(changeSize);

	// Removing the idle function to save CPU and GPU
	glutIdleFunc(renderSceneAll);
	init();

	// sub windows
	subWindow1 = glutCreateSubWindow(mainWindow, border, border, w - 2 * border, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw1);
	init();

	subWindow2 = glutCreateSubWindow(mainWindow, border, (h + border) / 2, w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw2);
	init();

	subWindow3 = glutCreateSubWindow(mainWindow, (w + border) / 2, (h + border) / 2, w / 2 - border * 3 / 2, h / 2 - border * 3 / 2);
	glutDisplayFunc(renderScenesw3);
	init();

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}