// Etapa2.cpp
// Fichero principal 
////////////////////////////////////////////////////

#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes. 

//Funci�n que detecta el cambio de ventana. 
void glutReshapeFunc(int width, int height) {
	
	int aWindow = width / height;

}

// Funci�n que visualiza la escena OpenGL
void Display(void)
{
	//Se llama a la funci�n que tiene que mantener la relaci�n de aspecto pasando por par�metro el tama�o de la ventana. 
	glutReshapeFunc(GLUT_SCREEN_WIDTH, GLUT_SCREEN_HEIGHT);

	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	// Rotamos las proximas primitivas
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);

	// Creamos a continuaci�n dibujamos los tres poligonos
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.866f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.866f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-0.5f, 0.866f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.866f, 0.0f);
	glEnd();

	//Se hace un escalado reduciendo el tama�o un 70% para el dibujado del cuadrado. 
	glScalef(0.3f, 0.3f, 0.3f);

	//Cuadrado. 
	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);     
	glVertex3f(0.5, -0.5, -0.5);      
	glColor3f(0.0, 1.0, 0.0);     
	glVertex3f(0.5, 0.5, -0.5);      
	glColor3f(0.0, 0.0, 1.0);     
	glVertex3f(-0.5, 0.5, -0.5);     
	glColor3f(1.0, 0.0, 1.0);     
	glVertex3f(-0.5, -0.5, -0.5);


	glEnd();
	
	glPopMatrix();

	glFlush();

	//Cambio entre el backbuffer y el frontbuffer.
	glutSwapBuffers();
}

// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	// Incrementamos el �ngulo
	fAngulo += 0.3f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360)
		fAngulo -= 360;
	// Indicamos que es necesario repintar la pantalla
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
	glutCreateWindow("Mi primera Ventana - Etapa 2");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}