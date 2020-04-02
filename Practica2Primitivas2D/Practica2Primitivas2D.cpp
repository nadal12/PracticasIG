#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 

const int W_WIDTH = 500; // Tamaño incial de la viewport
const int W_HEIGHT = 500;
const int wMon = 2;
const int hMon = 2;

const float MAX_TOR_SIZE = 0.3f; 
const float MIN_TOR_SIZE = 0.1f;
GLfloat fAnguloFig1; // Variable que indica el ángulo de rotación de los ejes. 
GLfloat escaladoToroide;
bool aumentarToroide = true; 
GLfloat fAnguloFig2;
GLfloat fAnguloFig3;
GLfloat fAnguloFig4;

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

// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	//Dibujar plano cartesiano. 
	glPushMatrix();

	glBegin(GL_LINES); // pintar los ejes Y
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glBegin(GL_LINES); // pintar los ejes X
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();

	glPopMatrix();

	//Primera figura (Triangulo).
	glPushMatrix();
	
	glTranslatef(-0.5, 0.5, 0);
	glRotatef(fAnguloFig1, 0.0f, 0.5f, 0.0f);
	glScalef(0.5, 0.5, 0.0);

	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.2f, 0.4f);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glPopMatrix();

	//Segunda figura (Cono). 
	glPushMatrix();

	//Configuración inicial.
	glTranslatef(0.5, 0.5, 0);
	glScalef(0.5, 0.5, 0.0);
	glRotated(70, 0, 0.5, 0.5);
	glRotatef(fAnguloFig2, 0.3f, 0.0f, 0.5f);
	glColor3f(0.0f, 0.0f, 0.25f);

	//Dibujado de la figura. 
	glutWireCone(0.5, 1, 25, 25);
	glPopMatrix();

	//Tercera figura (toroide)
	glPushMatrix();

	//Configuración inicial.
	glTranslatef(-0.5, -0.5, 0);
	glScalef(escaladoToroide, escaladoToroide, 0.0);
	glRotated(40, 0.5, 0.7, 0.0);
	glRotatef(fAnguloFig3, 0.8f, 0.0f, 0.5f);
	glColor3f(0.0f, 0.30f, 0.30f);

	//Dibujado de la figura. 
	glutWireTorus(0.5, 1, 25, 25);
	glPopMatrix();

	//Cuarta figura figura
	glPushMatrix();

	//Configuración inicial.
	glTranslatef(0.5, -0.5, 0);
	glScalef(0.5, 0.5, 0.5);
	glRotated(5, 0.0, 0.7, 0.5);
	glRotatef(fAnguloFig4, 0.2f, 0.0f, 0.1f);
	glColor3f(0.0f, 0.30f, 0.30f);

	//Dibujado de la figura. 
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.5f, 0.4f);
	glVertex2f(0.5, 0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glVertex2f(-0.5, 0.5);
	glEnd();

	glPopMatrix();

	//Cambio entre el backbuffer y el frontbuffer.
	glutSwapBuffers();
}

GLfloat decrementarAngulo(GLfloat angulo) {
	if (angulo > 360) {
		angulo -= 360;
	}
	return angulo;
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{	
	//Escalado toroide

	if (escaladoToroide >= MAX_TOR_SIZE) {
		aumentarToroide = false; 
	}

	if (escaladoToroide <= MIN_TOR_SIZE) {
		aumentarToroide = true; 
	}

	if (aumentarToroide) {
		escaladoToroide += 0.001f; 
	} else {
		escaladoToroide -= 0.001f; 
	}

	// Incrementamos el ángulo
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
	glutCreateWindow("Etapa 2 - Primitivas2D");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	//Se indica cual es la función de reshape.
	glutReshapeFunc(reshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	//La sintaxi és glOrtho(x min, x max, y min, y max, z1, z2)


	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}