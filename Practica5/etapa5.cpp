/*******CONTROLES********/
/* 
-: Disminuir luz ambiente. 
+: Aumentar luz ambiente.
*/


#include "iostream"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h> 

const int W_WIDTH = 500; // Tamaño incial de la viewport
const int W_HEIGHT = 500;
const int wMon = 2;
const int hMon = 2;

GLfloat fAnguloFig4;
GLfloat fAnguloFig2;


GLfloat ambientLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat especularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat difuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };

GLfloat lightPosition0[] = { 0.8f, 0.0f, 0.0f };

bool shade = false;
bool light1 = false;

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

void printAxis() {
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
}

void printSolidSphere() {
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(-1.2, 1.2, 0);
	glColor3f(0.7f, 0.0f, 0.25f);
	glutSolidSphere(0.5f, 20, 20);
}

// Función que visualiza la escena OpenGL
void Display(void)
{
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(lightPosition0[0], lightPosition0[1], lightPosition0[2]);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, especularLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difuseLight);
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidSphere(0.08f, 20, 20);
	glPopMatrix();
	
	/*glPushMatrix();
	//printAxis();
	printSolidSphere();
	glPopMatrix();*/

	glPushMatrix();
	glScalef(0.5, 0.5, 0.5);
	glTranslated(cos(fAnguloFig4), 0, sin(fAnguloFig4));
	glRotated(70, 0, 0.5, 0.5);
	glRotatef(fAnguloFig2, 0.3f, 1.0f, 0.5f);
	glColor3f(0.0f, 0.33f, 0.25f);
	glutSolidCube(0.2f);
	glPopMatrix();

	glPushMatrix();
	glScalef(0.7, 0.7, 0.7);
	glRotated(70, 0, 0.5, 0.5);
	glRotatef(fAnguloFig2, 0.3f, 1.0f, 0.5f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireTeapot(0.5);
	glPopMatrix();

	glPushMatrix();
	printSolidSphere();
	glPopMatrix();

	//Cambio entre el backbuffer y el frontbuffer.
	glutSwapBuffers();
}

// Función que se ejecuta cuando el sistema no esta ocupado
void Idle(void) {
	fAnguloFig2 += 0.2f;
	fAnguloFig4 += 0.01f;

	// Indicamos que es necesario repintar la pantalla
	glutPostRedisplay();
}


void controlTeclado(unsigned char key, int x, int y) {

	switch (key) {
	
	//Controles de luz ambiente.
	case '1':
		ambientLight[0] -= 0.05f;
		ambientLight[1] -= 0.05f;
		ambientLight[2] -= 0.05f;
		break; 

	case '2':
		ambientLight[0] += 0.05f;
		ambientLight[1] += 0.05f;
		ambientLight[2] += 0.05f;
		break;

	case '3':
		especularLight[0] -= 0.5f;
		especularLight[1] -= 0.5f;
		especularLight[2] -= 0.5f;
		break;

	case '4':
		especularLight[0] += 0.5f;
		especularLight[1] += 0.5f;
		especularLight[2] += 0.5f;
		break;

	case '5':
		difuseLight[0] -= 0.2f;
		difuseLight[1] -= 0.2f;
		difuseLight[2] -= 0.2f;
		break;

	case '6':
		difuseLight[0] += 0.2f;
		difuseLight[1] += 0.2f;
		difuseLight[2] += 0.2f;
		break;

	case 'a':
		lightPosition0[0] += 0.1;
		break;
	case 'z':
		lightPosition0[0] -= 0.1;
		break;
	case 's':
		lightPosition0[1] += 0.1;
		break;
	case 'x':
		lightPosition0[1] -= 0.1;
		break;
	case 'd':
		lightPosition0[2] += 0.1;
		break;
	case 'c':
		lightPosition0[2] -= 0.1;
		break;
	case ' ': 
		shade = !shade; 

		if (shade) {
			glShadeModel(GL_FLAT);
		} else {
			glShadeModel(GLU_SMOOTH);
		}

		break;
	}

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
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Creamos la nueva ventana
	glutCreateWindow("Etapa 5");

	// Indicamos cuales son las funciones de redibujado e idle
	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutKeyboardFunc(controlTeclado);
	glutReshapeFunc(reshape);

	// El color de fondo será el negro (RGBA, RGB + Alpha channel)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	//Renderización de luz
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	//Hibilitar primera luz
	glEnable(GL_LIGHT0);

	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);

	// Comienza la ejecución del core de GLUT
	glutMainLoop();
	return 0;
}