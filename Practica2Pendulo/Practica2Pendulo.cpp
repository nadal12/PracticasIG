#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//Constants generals
const int W_WIDTH = 500; // Tamaño incial de la viewport
const int W_HEIGHT = 500;
const int wMon = 2;
const int hMon = 2;

//Constants Pendul
constexpr auto PI = 3.1415926535897932384626433832795;

//Característiques 
float longitud_corda = 0.5; //longitud braç
const float x_corda = 0;	//Iici corda
const float y_corda = 0;
const float radiQ = 0.05;	//Radio quadrat 1
float angle = PI / 4;		//Angle


float xq, yq = NULL;		//Centro quadrat
float aVel = 0.0;			//Velocitat 
float aAcc = 0.0;			//Acceleración


//Constants per càlcul de trajectòria
const int trajectoryQ1Lenght = 100;
float trajectoryXQ1[trajectoryQ1Lenght];
float trajectoryYQ1[trajectoryQ1Lenght];
int index = 0;



void reshape(int w, int h) {

	if (h == 0) { //per no fer divisions per 0
		h = 1;
	}

	float aspecRatioW = (float)wMon / (float)hMon; //aspect ratio del Window
	float aspectRatioV = (float)w / (float)h;	//aspect ratio del viewport 

	if (aspectRatioV > aspecRatioW)
		//ViewPort major que aspect (aWin) de la regió  
	{
		//Amplada nova = Amplada anterior * (aViewPort / aWindow)
		//0 -+ i /2 para centrarlo
		glLoadIdentity();
		glOrtho(0 - (wMon * (aspectRatioV / aspecRatioW)) / 2, 0 + (wMon * (aspectRatioV / aspecRatioW)) / 2, -hMon / 2, hMon / 2, -1.0, 1.0f);
	}
	else
	{

		//Altura nova = Amplada Anterior * (aViewPort / aWindow)
		//Posam 0 -+ perque estigui centrat
		glLoadIdentity();
		glOrtho(-wMon / 2, wMon / 2, 0 - hMon * (aspecRatioW / aspectRatioV) / 2, 0 + hMon * (aspecRatioW / aspectRatioV) / 2, -1.0, 1.0f);
	}
	glViewport(0, 0, w, h); //Pintam segons es canvi des viewport
}

void pintarQuadrat() {


	//Trajectòria quadrat
	trajectoryXQ1[index % trajectoryQ1Lenght] = xq;
	trajectoryYQ1[index % trajectoryQ1Lenght] = yq;

	//actualitzam els punts del quadrat
	xq = x_corda + longitud_corda * sin(angle);
	yq = y_corda + longitud_corda * cos(angle);

	//Dibuixar trajectòria quadrat1
	glPushMatrix();
	for (size_t i = 0; i < trajectoryQ1Lenght; i++) {
		if (trajectoryXQ1[i] != NULL) {
			glBegin(GL_POINTS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(trajectoryXQ1[i], trajectoryYQ1[i], 0.0f);
			glEnd();
		}
	}
	glPopMatrix();


	//Pintam quadrat 
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(xq + radiQ, yq - radiQ, 0.0);
	glVertex3f(xq + radiQ, yq + radiQ, 0.0);
	glVertex3f(xq - radiQ, yq + radiQ, 0.0);
	glVertex3f(xq - radiQ, yq - radiQ, 0.0);
	glEnd();

	//Pintam corda 
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(x_corda, y_corda, 0.0f);
	glVertex3f(xq, yq, 0.0f);
	glEnd();
}

void Display(void)
{
	//Cridam reshape per si la finestra es modifica durant la execuió
	glutReshapeFunc(reshape);

	//Borram l'escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	//Pintam pèndul
	pintarQuadrat();

	glEnd();

	//Funcio que actualitzarà l'angle
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glPopMatrix();

	glFlush();

	//Canvi entre el backbuffer y el frontbuffer.
	glutSwapBuffers();
}

//Funció que s'executa quan el sistema no esta ocupat
void Idle(void)
{

	//Incrementam velocitat amb acceleració, angle i velocitats
	aAcc = 0.01 * sin(angle);
	angle += aVel;
	aVel += aAcc;

	// Aplicam el component de fricció
	aVel *= 0.99;
	
	//Perque index no s'incrementi fins a nombres molt grans
	if (index == trajectoryQ1Lenght) {
		index = 1;
	}
	else {
		index++;
	}

	//Indicam que es necessari repintar la pantalla
	glutPostRedisplay();
}



// Funció principal
int main(int argc, char** argv)
{
	// Inicialtzam  la llibreria GLUT
	glutInit(&argc, argv);

	// Definim finestra
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);

	//	Habilitam doble buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Cream nova finestra
	glutCreateWindow("Etapa 2 - Doble Pendulo");

	// Indicamos quienes són les funcions de dibuizar i idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	// El color de fondo serà el negre (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}