﻿#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

constexpr auto PI = 3.1415926535897932384626433832795;
const int W_WIDTH = 500; // Tamaño incial de la viewport
const int W_HEIGHT = 500;
const int wMon = 2;
const int hMon = 2;
float longitud_corda = 0.5; //longitud corda
const float x_corda = 0;
const float y_corda = 0;
const float radiQ = 0.05; //radiquadrat
float angle = PI / 4;
float xq, yq = NULL;
float aVel = 0.0;
float aAcc = 0.0;

int draw_endpoint = 0;
int n_points = 500;

const int trajectoryQ1Lenght = 100;
float trajectoryXQ1[trajectoryQ1Lenght];
float trajectoryYQ1[trajectoryQ1Lenght];
int index = 0;


void reshape(int w, int h) {

	if (h == 0) { //per no fer divisions per 0
		h = 1;
	}

	float aspecRatioW = (float)wMon / (float)hMon; //aspect ratio de Window (es 1)
	float aspectRatioV = (float)w / (float)h;	//aspect ratio des viewport 

	if (aspectRatioV > aspecRatioW) //viewPort major que aspect (aWin) de sa regio  
	{	//hem de tocar amplada (w) de window. Deixam altura igual i tocam amplada.
		//Amplada nova = Amplada Anterior * (aViewPort / aWindow)
		//Posam 0 -+ i /2 perque estigui centrat
		glLoadIdentity();
		glOrtho(0 - (wMon * (aspectRatioV / aspecRatioW)) / 2, 0 + (wMon * (aspectRatioV / aspecRatioW)) / 2, -hMon / 2, hMon / 2, -1.0, 1.0f);
	}
	else
	{
		//hem de tocar altura (h) de window. Deixam amplada igual i tocam altura.
		//Altura nova = Amplada Anterior * (aViewPort / aWindow)
		//Posam 0 -+ perque estigui centrat
		glLoadIdentity();
		glOrtho(-wMon / 2, wMon / 2, 0 - hMon * (aspecRatioW / aspectRatioV) / 2, 0 + hMon * (aspecRatioW / aspectRatioV) / 2, -1.0, 1.0f);
	}
	glViewport(0, 0, w, h); //pintam segons es canvi des viewport
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
	//glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xq + radiQ, yq + radiQ, 0.0);
	//glColor3f(1.0, 1.0, 0.0);
	glVertex3f(xq - radiQ, yq + radiQ, 0.0);
	//glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xq - radiQ, yq - radiQ, 0.0);
	glEnd();
}
// Función que visualiza la escena OpenGL
void Display(void)
{
	//Se llama a la función que tiene que mantener la relación de aspecto pasando por parámetro el tamaño de la ventana. 
	glutReshapeFunc(reshape);


	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	//Se hace un escalado reduciendo el tamaño un 70% para el dibujado del cuadrado. 
	//glScalef(0.2f, 0.2f, 0.2f);

	/*glBegin(GL_LINES); // pintar sostre
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glEnd();*/



	pintarQuadrat();

	glBegin(GL_LINES); // pintar corda
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(x_corda, y_corda, 0.0f);
	glVertex3f(xq, yq, 0.0f);

	glEnd();

	glRotatef(angle, 0.0f, 0.0f, 1.0f);




	glPopMatrix();

	glFlush();

	//Cambio entre el backbuffer y el frontbuffer.
	glutSwapBuffers();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{

	//per pintar punts
	draw_endpoint = (draw_endpoint + 1) % n_points;

	//glutPostRedisplay();

	// Incrementamos el ángulo
	aAcc = 0.01 * sin(angle);
	angle += aVel;
	aVel += aAcc;
	aVel *= 0.99;
	// Si es mayor que dos pi la decrementamos

	if (index == trajectoryQ1Lenght) {
		index = 1;
	}
	else {
		index++;
	}

	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}


// Función principal
int main(int argc, char** argv)
{
	// Inicializamos la librería GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);

	//Se habilita el doblebuffer con el comando "GLUT_DOUBLE". 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	// Creamos la nueva ventana
	glutCreateWindow("Etapa 2 - Péndulo");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	//La sintaxi és glOrtho(x min, x max, y min, y max, z1, z2)


	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}