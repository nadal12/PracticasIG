// Etapa2.cpp
// Fichero principal 
////////////////////////////////////////////////////

#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

const int W_WIDTH = 500; // Tama�o incial de la viewport
const int W_HEIGHT = 500;
const int wMon = 2;
const int hMon = 2;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes. 


void reshape(int w, int h) {	
	
	if (h == 0) { //per no fer divisions per 0
		h = 1;
	}
	
	float aspecRatioW = (float)wMon / (float)hMon; //aspect ratio de Window (es 1)
	float aspectRatioV= (float) w / (float) h;	//aspect ratio des viewport 

	if (aspectRatioV > aspecRatioW) //viewPort major que aspect (aWin) de sa regio  
	{	//hem de tocar amplada (w) de window. Deixam altura igual i tocam amplada.
		//Amplada nova = Amplada Anterior * (aViewPort / aWindow)
		//Posam 0 -+ i /2 perque estigui centrat
		glLoadIdentity();
		glOrtho(0 - (wMon* (aspectRatioV/aspecRatioW)  ) / 2, 0 + (wMon * (aspectRatioV / aspecRatioW)) / 2, -hMon / 2, hMon / 2, -1.0, 1.0f);
	}
	else
	{	
		//hem de tocar altura (h) de window. Deixam amplada igual i tocam altura.
		//Altura nova = Amplada Anterior * (aViewPort / aWindow)
		//Posam 0 -+ perque estigui centrat
		glLoadIdentity();
		glOrtho(-wMon/2, wMon/2, 0 - hMon* (aspecRatioW /aspectRatioV) / 2, 0+ hMon * (aspecRatioW / aspectRatioV) / 2, -1.0, 1.0f);
	}
	glViewport(0, 0, w, h); //pintam segons es canvi des viewport
}

// Funci�n que visualiza la escena OpenGL
void Display(void)
{
	//Se llama a la funci�n que tiene que mantener la relaci�n de aspecto pasando por par�metro el tama�o de la ventana. 
	glutReshapeFunc(reshape);

	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	// Rotamos las proximas primitivas
	glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);

	// Creamos a continuaci�n dibujamos los tres poligonos
	glBegin(GL_POLYGON);				
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
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
	glVertex3f(0.5, -0.5, 0.0);
	glColor3f(0.0, 1.0, 0.0);     
	glVertex3f(0.5, 0.5, 0.0);
	glColor3f(0.0, 0.0, 1.0);     
	glVertex3f(-0.5, 0.5, 0.0);
	glColor3f(1.0, 0.0, 1.0);     
	glVertex3f(-0.5, -0.5, 0.0);


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
	fAngulo += 1.0f;
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
	glutCreateWindow("ViewPort - Etapa 2");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	//La sintaxi �s glOrtho(x min, x max, y min, y max, z1, z2)


	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}