#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

//Dimensiones pantalla
const int W_WIDTH = 500;
const int W_HEIGHT = 500;

GLfloat fAngTorus; //Angulo rotacion torus

static float directionTorus = 1.0; //Direccion de rotacion torus


								 //Dibuja la rejilla
void draw_grid(int n, int d)
{
	int i;
	glPushMatrix();
	glLineWidth(1); //Cambiamos ancho de la linea
	glColor3f(1, 1, 1); //Color de la linea
	for (i = 0; i <= (n * 2) + 1; i++) {
		glPushMatrix();
		//La mitad se dibujan paralelas al eje x
		if (i <= n) { glTranslatef(0, 0, i * d); }
		//La otra mitad se dibujan paralelas al eje z
		if (i > n) { glTranslatef((i - n - 1) * d, 0, 0); glRotatef(-90, 0, 1, 0); }
		glBegin(GL_LINES);
		glVertex3f(0, -0.1, 0); glVertex3f(n, -0.1, 0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
}

//Dibuja los cubos del fondo
/*
void draw_cubes() {
	//Arriba izquierda
	glPushMatrix();
	glTranslatef(-0.5, 0.5, -1.0);
	glPushMatrix();
	glRotatef(fAngTorus, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, 0.5);
	glColor3ub(155, 222, 237);
	glutWireTorus(0.2, 0.3, 6, 20);
	glPopMatrix();
	glColor3ub(43, 181, 228);
	glutSolidCube(1.0);
	glPopMatrix();

	//Arriba derecha
	glPushMatrix();
	glTranslatef(0.5, 0.5, 0.0);
	glPushMatrix();
	glRotatef(fAngTorus, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, 0.5);
	glColor3ub(185, 77, 155);
	glutWireTorus(0.2, 0.3, 6, 20);
	glPopMatrix();
	glColor3ub(245, 229, 55);
	glutSolidCube(1.0);
	glPopMatrix();

	//Abajo izquierda
	glPushMatrix();
	glTranslatef(-0.5, -0.5, 0.0);
	glPushMatrix();
	glRotatef(fAngTorus, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, 0.5);
	glColor3ub(252, 217, 51);
	glutWireTorus(0.2, 0.3, 6, 20);
	glPopMatrix();
	glColor3ub(233, 38, 137);
	glutSolidCube(1.0);
	glPopMatrix();

	//Abajo derecha
	glPushMatrix();
	glTranslatef(0.5, -0.5, -1.0);
	glPushMatrix();
	glRotatef(fAngTorus, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, 0.5);
	glColor3ub(235, 54, 49);
	glutWireTorus(0.2, 0.3, 6, 20);
	glPopMatrix();
	glColor3ub(196, 219, 115);
	glutSolidCube(1.0);
	glPopMatrix();
}*/



void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//Desplazamos camara
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(-10.0, -1.0, -15.0);
	draw_grid(20, 1);
	glPopMatrix();

	
	glutSwapBuffers();
	glFlush();
}

void Idle(void)
{
	//Incrementamos el angulo de rotacion
	fAngTorus += 0.1 * directionTorus;


	glutPostRedisplay();
}

void Special_Keys(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_RIGHT:  directionTorus = 1.0;  break; //Cambia direccón de rotacion
	case GLUT_KEY_LEFT:  directionTorus = -1.0;  break; //Cambia direccón de rotacion
	default:;
	}

	glutPostRedisplay();
}

void reshape(int w, int h)
{
	if (w < W_HEIGHT || h < W_HEIGHT) { //Caso en que se encoje la ventana
		int wn = w, hn = h;
		if (w < h) //Escogemos la dimensión mas pequea
		{
			hn = W_HEIGHT * w / W_HEIGHT;
		}
		else {
			wn = W_WIDTH * h / W_HEIGHT;
		}
		glViewport(w / 2 - wn / 2, h / 2 - hn / 2, wn, hn);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 30.0);
		glMatrixMode(GL_MODELVIEW);
	}
	else { //Si la ventana no es menor al tamao original
		glViewport(w / 2 - W_WIDTH / 2, h / 2 - W_HEIGHT / 2, W_WIDTH, W_HEIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 30.0);
		glMatrixMode(GL_MODELVIEW);
	}
}


void reshape2(int w, int h) {

	if (h == 0) { //per no fer divisions per 0
		h = 1;
	}
	float wMon = 2;
	float hMon = 2;
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glutCreateWindow("Etapa 3");

	glutDisplayFunc(Display);
	glutIdleFunc(Idle);
	glutSpecialFunc(Special_Keys);
	glutReshapeFunc(reshape);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.1, 0.1, 1.0);

	glutMainLoop();
	return 0;
}