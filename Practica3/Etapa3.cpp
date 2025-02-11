/*Etapa 3*/

#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 

const int W_WIDTH = 500; // Tama�o incial de la viewport
const int W_HEIGHT = 500;
const int wMon = 2;
const int hMon = 2;

const float MAX_TOR_SIZE = 0.3f;
const float MIN_TOR_SIZE = 0.1f;
GLfloat fAnguloFig1; // Variable que indica el �ngulo de rotaci�n de los ejes. 
GLfloat escaladoToroide;
bool aumentarToroide = true;
GLfloat fAnguloFig2;
GLfloat fAnguloFig3;
GLfloat fAnguloFig4;
int num = 0;

void reshape(int w, int h) {

	if (h == 0) { //per no fer divisions per 0
		h = 1;
	}

	float aspecRatioW = (float)wMon / (float)hMon; //aspect ratio del Window
	float aspectRatioV = (float)w / (float)h;	//aspect ratio del viewport 

	if (aspectRatioV > aspecRatioW)
		//ViewPort major que aspect (aWin) de la regi�  
	{
		//Amplada nova = Amplada anterior * (aViewPort / aWindow)
		//0 -+ i /2 para centrarlo
		glLoadIdentity();
		glOrtho((GLdouble)0 - (wMon * (aspectRatioV / aspecRatioW)) / 2, (GLdouble)0 + (wMon * (aspectRatioV / aspecRatioW)) / 2, (GLdouble)-hMon / 2, (GLdouble)hMon / 2, (GLdouble)-1.0, (GLdouble)1.0f);
	}
	else
	{

		//Altura nova = Amplada Anterior * (aViewPort / aWindow)
		//Posam 0 -+ perque estigui centrat
		glLoadIdentity();
		glOrtho((GLdouble)-wMon / 2, wMon / 2, (GLdouble)0 - hMon * (aspecRatioW / aspectRatioV) / 2, (GLdouble)0 + hMon * (aspecRatioW / aspectRatioV) / 2, (GLdouble)-1.0, (GLdouble)1.0f);
	}
	glViewport(0, 0, w, h); //Pintam segons es canvi des viewport
}

// Funci�n que visualiza la escena OpenGL
void Display(void)
{
	glEnable(GL_DEPTH_TEST);
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Ver como funciona gluLookAt en: https://youtu.be/bmQmme9jKTc?t=315
	gluLookAt(0.1, 0.1, 0.1, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0); // 3 primeres coord: eixos
															// 3 segones coord: sa direcci� on mira
															// 3 terceres coord: es vector normal

	glBegin(GL_LINES);     // pintar los ejes X: vermell
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.95f, 0.01f, 0.0f);
	glVertex3f(0.95f, -0.01f, 0.0f);
	glEnd();

	glBegin(GL_LINES); // pintar los ejes Y: verd
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.01f, 0.95f, -0.01f);
	glVertex3f(-0.01f, 0.95f, 0.01f);
	glEnd();

	glBegin(GL_LINES); // pintar los ejes Z: blau
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();	

	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.01f, 0.95f);
	glVertex3f(0.0f, -0.01f, 0.95f);
	glEnd();

	switch (num) //Control canvi d'objecte desde teclat
	{
	case 0:
		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glRotated(70, 0, 0.5, 0.5);
		glRotatef(fAnguloFig2, 0.3f, 0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 0.25f);
		glutWireCube(0.5);
		glPopMatrix();

		break;
	case 1:
		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glRotated(70, 0, 0.5, 0.5);
		glRotatef(fAnguloFig2, 0.3f, 0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 0.25f);
		glutWireCone(0.5, 1, 25, 25);
		glPopMatrix();
		break;
	case 2:
		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glRotated(70, 0, 0.5, 0.5);
		glRotatef(fAnguloFig2, 0.3f, 0.0f, 0.5f);
		glColor3f(0.0f, 1.0f, 0.25f);
		glutWireTorus(0.5, 1, 25, 25);
		glPopMatrix();
		break;
	case 3:
		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glRotated(70, 0, 0.5, 0.5);
		glRotatef(fAnguloFig2, 0.3f, 0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 0.25f);
		glutWireDodecahedron();
		glPopMatrix();
		break;
	case 4:
		glPushMatrix();
		glScalef(0.3, 0.3, 1);
		glRotated(0, 0, 0.5, 0);
		glRotatef(fAnguloFig2, 0.0f, 3.0f, -0.2f);
		glColor3f(0.0f, 0.0f, 0.25f);
		glutSolidOctahedron();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glRotated(0, 0, 0.5, 0);
		glRotatef(fAnguloFig2, 0.0f, 3.0f, -0.2f);
		glColor3f(0.0f, 0.0f, 0.25f);
		glutWireOctahedron();
		glPopMatrix();
		break;
	case 5:
		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glRotated(70, 0, 0.5, 0.5);
		glRotatef(fAnguloFig2, 0.3f, 0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 0.25f);
		glutWireTetrahedron();
		glPopMatrix();
		break;
	case 6:
		glPushMatrix();
		glTranslatef(0.5, 0, 0);
		glScalef(0.3, 0.3, 0.3);
		glRotated(70, 0, 0.5, 0.5);
		glRotatef(fAnguloFig2, 0.3f, 0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 0.25f);
		glutWireIcosahedron();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glTranslatef(-0.5, 0, 0);
		glRotated(70, 0, 0.5, 0.5);
		glRotatef(fAnguloFig2, 0.3f, 0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 0.25f);
		glutSolidIcosahedron();
		glPopMatrix();
		break;
	case 7:
		glPushMatrix();
		glScalef(0.5, 0.5, 0.5);
		glTranslated(cos(fAnguloFig4), 0, sin(fAnguloFig4));
		glRotated(70, 0, 0.5, 0.5);
		glRotatef(fAnguloFig2, 0.3f, 1.0f, 0.5f);
		glColor3f(0.0f, 0.33f, 0.25f);
		glutSolidTeapot(0.5);
		glPopMatrix();

		glPushMatrix();
		glScalef(0.7, 0.7, 0.7);
		glRotated(70, 0, 0.5, 0.5);
		glRotatef(fAnguloFig2, 0.3f, 1.0f, 0.5f);
		glColor3f(0.0f, 0, 0);
		glutWireTeapot(0.5);
		glPopMatrix();

		break;
	}

	//Cambio entre el backbuffer y el frontbuffer.
	glutSwapBuffers();
}

GLfloat decrementarAngulo(GLfloat angulo) {
	if (angulo > 360) {
		angulo -= 360;
	}
	return angulo;
}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	//canvi d'objecte segueixi un cam� tancat i el darrer torni a ser el primer
	if (num == -1)
	{
		num = 7;
	}
	else if (num == 8)
	{
		num = 0;
	}

	//Escalado toroide
	if (escaladoToroide >= MAX_TOR_SIZE) {
		aumentarToroide = false;
	}

	if (escaladoToroide <= MIN_TOR_SIZE) {
		aumentarToroide = true;
	}

	if (aumentarToroide) {
		escaladoToroide += 0.001f;
	}
	else {
		escaladoToroide -= 0.001f;
	}

	// Incrementamos el �ngulo
	fAnguloFig1 += 1.0f;
	fAnguloFig2 += 3.0f;
	fAnguloFig3 += 0.5f;
	fAnguloFig4 += 0.1f;

	fAnguloFig1 = decrementarAngulo(fAnguloFig1);
	fAnguloFig2 = decrementarAngulo(fAnguloFig2);
	fAnguloFig3 = decrementarAngulo(fAnguloFig3);
	fAnguloFig4 = decrementarAngulo(fAnguloFig4);

	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}


void controlTeclado(unsigned char key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		num = num + 1;
		break;
	}
	glutPostRedisplay();
}
void SpecialInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		num = num - 1;
		break;
	case GLUT_KEY_RIGHT:
		num = num + 1;
		break;
	}

	glutPostRedisplay();
}

// Funci�n principal
int main(int argc, char** argv)
{
	// Inicializamos la librer�a GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);

	//Se habilita el doblebuffer con el comando "GLUT_DOUBLE". 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Etapa 3 - Primitivas3D");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(controlTeclado);
	glutSpecialFunc(SpecialInput);
	//Se indica cual es la funci�n de reshape.
	glutReshapeFunc(reshape);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	//La sintaxi �s glOrtho(x min, x max, y min, y max, z1, z2)

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}