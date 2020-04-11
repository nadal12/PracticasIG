#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

const int W_WIDTH = 500; // Tamaño incial de la viewport
const int W_HEIGHT = 500;
const int wMon = 2;
const int hMon = 2;
GLfloat fAngulo; // Variable que indica el ángulo de rotación de los ejes. 


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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glScalef(0.5, 0.5, 0.0);
	glTranslatef(-0.6, 0, 0);
	glRotated(70, 0, 0.5, 0.5);
	glColor3f(0.0f, 0.0f, 0.25f);
	glutSolidTetrahedron();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.6, 0, 1.0);
	glScalef(0.7, 0.7, 0.0);
	glRotated(70, 0, 0.5, 0.5);
	glColor3f(0.0f, 0, 0);
	glutWireTeapot(0.5);
	glPopMatrix();

	//Cambio entre el backbuffer y el frontbuffer.
	glutSwapBuffers();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	// Incrementamos el ángulo
	fAngulo += 1.0f;
	// Si es mayor que dos pi la decrementamos
	if (fAngulo > 360)
		fAngulo -= 360;
	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {


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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);

	//glutKeyboardFunc(keyboard);
	// Creamos la nueva ventana
	glutCreateWindow("Etapa 4 - Movimiento de cámara");


	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	//Se indica cual es la función de reshape.
	glutReshapeFunc(reshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	//La sintaxi és glOrtho(x min, x max, y min, y max, z1, z2)


	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}