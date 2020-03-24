// Etapa2.cpp
// Fichero principal 
//Viewport: sa part de s'ordenador
//Finestra : sa part des "mon real" que se representa a sa pantalla
////////////////////////////////////////////////////

#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;
const int wMon = 2;
const int hMon = 2;
GLfloat fAngulo; // Variable que indica el �ngulo de rotaci�n de los ejes. 

//Funci�n que detecta el cambio de ventana. 
void reshape(int w, int h) {	
	/*"There are two cases to consider: the aspect of the viewport is 
	greater than the aspect of your region, so it is wider. In that case,
	you should map the full height and increase the horitonal range by a 
	factor of (aspect_viewport/aspect_region). Otherwise, the aspect of the
	window is lower than aspect of your region, so you should use the full 
	width and scale up the vertical range by (aspect_region/aspect_viewport). 
	Note that in both cases, the factor is >= 1."
	Com que est�s en 2d, assegura't que z1 < z2, si no, no funcionar� i no te dir� el perqu�.
	*/
	if (h == 0) {
		h = 1;
	}
	
	float aspecRatioW = (float)wMon / (float)hMon;
	float aspectRatioV= (float) w / (float) h;	//aspect des viewport
	//float aWin = wFin / hFin;	//aspect de sa finestra/mon
	//awin es 1 per 2/2
	if (aspectRatioV/aspecRatioW < 1)
	{
		printf("Divios a's menor a 1");
	}
	
	if (aspectRatioV > 1) //viewPort major que aspect (aWin) de sa regio  //aspectratio es ATRI
	{
		// map the full height and increase the horitonal range by a 
		//factor of(aspect_viewport / aspect_region)
		glLoadIdentity();
		glOrtho(0 - (aspectRatioV * wMon) / 2, 0 + aspectRatioV *  wMon / 2, -hMon / 2, hMon / 2, -1.0, 1.0f);
		printf(" ARatio > 1 ");
		//glOrtho(-(aspectRatio),+(aspectRatio), -hMon/2, hMon/2, -1.0, 1.0f);
		//glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	}
	else
	{	
		//so you should use the full
		//width and scale up the vertical range by(aspect_region / aspect_viewport)
		glLoadIdentity();
		glOrtho(-wMon/2, wMon/2, 0 - (hMon/2)* aspecRatioW /aspectRatioV, 0+ hMon/2 * aspecRatioW / aspectRatioV, -1.0, 1.0f);
		printf(" ARatio < 1 ");
		//glOrtho(-wMon / 2, wMon / 2, -(aspectRatio), +(aspectRatio), -1.0, 1.0f);
		//glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	}
	
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
	glutCreateWindow("ViewPort - Etapa 2");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glLoadIdentity();
	glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);
	//La sintaxi �s glOrtho(x min, x max, y min, y max, z1, z2)
	//glOrtho(left, right, bottom, top, near, far)
	//osea amplada i altura = 2

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}