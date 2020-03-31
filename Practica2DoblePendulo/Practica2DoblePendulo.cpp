#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <chrono>
#include <thread>

//Constants generals
const int W_WIDTH = 500; 
const int W_HEIGHT = 500;
const int wMon = 2;
const int hMon = 2;
bool traj = false;

//Constants Pendul
constexpr auto PI = 3.1415926535897932384626433832795;
const float g = -0.0001;

//Caracter�stiques p�ndul 1
float longitud_corda = 0.3; //Longitut bra� 1
const float x_corda = 0;	//Iici corda
const float y_corda = 0;
const float radiQ = 0.05;	//Radio quadrat 1
float angle = PI / 4;		//Angle

float xq, yq = NULL;		//Centro quadrat
float aVel = 0.0;			//Velocitat 
float aAcc = 0.0;			//Acceleraci�n
const float m1 = 10;		//masa 1

//Caracter�stiques p�ndul 2
float longitud_corda2 = 0.5; //Longitut bra� 2
float x_corda2;				//Iici corda
float y_corda2;
float angle2 = PI / 4;		//Angle

float xq2, yq2 = NULL;		//Centre quadrat
float aVel2 = 0.0;			//Velocitat
float aAcc2 = 0.0;			//Acceleraci�
const float m2 = 10;

//Constants per c�lcul de traject�ries
const int trajectoryQ1Lenght = 100;
float trajectoryXQ1[trajectoryQ1Lenght];
float trajectoryYQ1[trajectoryQ1Lenght];

const int trajectoryQ2Lenght = 1000;
float trajectoryXQ2[trajectoryQ2Lenght];
float trajectoryYQ2[trajectoryQ2Lenght];

int index = 0;

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

//Funcio per buidar arrays
void buida(float pp[]) {
	for (int i = 0; i < trajectoryQ1Lenght; i++)
	{
		pp[i] = NULL;
	}
}

void pintarPendulos() {

	//Traject�ria quadrat 1
	trajectoryXQ1[index % trajectoryQ1Lenght] = xq;
	trajectoryYQ1[index % trajectoryQ1Lenght] = yq;

	//Nous valors posici� q1
	xq = x_corda + longitud_corda * sin(angle);
	yq = y_corda + longitud_corda * cos(angle);

	//Traject�ria quadrat 2
	trajectoryXQ2[index % trajectoryQ2Lenght] = xq2;
	trajectoryYQ2[index % trajectoryQ2Lenght] = yq2;

	//Nous valors posici� q2
	xq2 = xq + longitud_corda2 * sin(angle2);
	yq2 = yq + longitud_corda2 * cos(angle2);

	//Dibuixar traject�ria quadrat1
	if (traj)
	{
		

		glPushMatrix();
		for (size_t i = 0; i < trajectoryQ1Lenght; i++) {
			if (trajectoryXQ1[i] != NULL) {
				glPointSize(2);
				glBegin(GL_POINTS);
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(trajectoryXQ1[i], trajectoryYQ1[i], 0.0f);
				glEnd();
			}
		}
		glPopMatrix();

		glPushMatrix();
		//Dibuixar traject�ria quadrat2
		for (size_t i = 0; i < trajectoryQ2Lenght; i++) {
			if (trajectoryXQ2[i] != NULL) {
				glBegin(GL_POINTS);
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(trajectoryXQ2[i], trajectoryYQ2[i], 0.0f);
				glEnd();
			}
		}
		glPopMatrix();
	}
	else
	{
		buida(trajectoryXQ1);
		buida(trajectoryYQ1);
	}

	
	
	
	//Pintam quadrat pendulo 1
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(xq + radiQ, yq - radiQ, 0.0);
	glVertex3f(xq + radiQ, yq + radiQ, 0.0);
	glVertex3f(xq - radiQ, yq + radiQ, 0.0);
	glVertex3f(xq - radiQ, yq - radiQ, 0.0);
	glEnd();

	//Pintam corda 1
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(x_corda, y_corda, 0.0f);
	glVertex3f(xq, yq, 0.0f);
	glEnd();

	//Pintam quadrat pendulo 2
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(xq2 + radiQ, yq2 - radiQ, 0.0);
	glVertex3f(xq2 + radiQ, yq2 + radiQ, 0.0);
	glVertex3f(xq2 - radiQ, yq2 + radiQ, 0.0);
	glVertex3f(xq2 - radiQ, yq2 - radiQ, 0.0);
	glEnd();

	//Pintam corda 2
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(xq, yq, 0.0f);
	glVertex3f(xq2, yq2, 0.0f);
	glEnd();
	
}


void controlTeclado(unsigned char key,int x, int y) {
	switch (key)
	{
	case 't':
		traj = !traj;
			break;
	}
	glutPostRedisplay();
}

//Funci� per determinar la acceleraci� de cada quadrat
//El calcul del numerador es fa per separatper simplificar la visualtzaci�.
void calcular() {
	//Acceleraci� 1
	float num1 = -g * (2 * m1 + m2) * sin(angle);
	float num2 = -m2 * g * sin(angle - 2 * angle2);
	float num3 = -2 * sin(angle - angle2) * m2;
	float num4 = aVel2 * aVel2 * longitud_corda2 + aVel * aVel * longitud_corda * cos(angle - angle2);
	float den = longitud_corda * (2 * m1 + m2 - m2 * cos(2 * angle - 2 * angle2));
	aAcc = (num1 + num2 + num3 * num4) / den;

	//Acceleraci� 2
	num1 = 2 * sin(angle - angle2);
	num2 = (aVel * aVel * longitud_corda * (m1 + m2));
	num3 = g * (m1 + m2) * cos(angle);
	num4 = aVel2 * aVel2 * longitud_corda2 * m2 * cos(angle - angle2);
	den = longitud_corda2 * (2 * m1 + m2 - m2 * cos(2 * angle - 2 * angle2));
	aAcc2 = (num1 * (num2 + num3 + num4)) / den;
}
void Display(void)
{
	//Cridam reshape per si la finestra es modifica durant la execui�
 	glutReshapeFunc(reshape);


	//Borram l'escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	//Pintar els dos p�nduls
	pintarPendulos();

	//Funcio que actualitzar� els angles i acceleracions
	glRotatef(angle, 0.0f, 0.0f, 1.0f);


	glPopMatrix();

	glFlush();

	//Cnavi entre el backbuffer y el frontbuffer.
	glutSwapBuffers();
}

//Funci� que s'executa quan el sistema no esta ocupat
void Idle(void)
{
	//Actualitzam valors per moviment
	calcular();

	//Incrementam velocitat amb acceleraci�
	aVel += aAcc;
	aVel2 += aAcc2;

	//Incrementam angle segons velocitat
	angle += aVel;
	angle2 += aVel2;

	//Aplicam el component de fricci� a cada velocitat
	/*
	aVel *= 0.99;
	aVel2 *= 0.99;
	*/

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


// Funci� principal
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

	// Indicamos quienes s�n les funcions de dibuizar i idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	glutKeyboardFunc(controlTeclado);

	// El color de fondo ser� el negre (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}