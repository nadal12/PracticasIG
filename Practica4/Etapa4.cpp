#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

//Dimensiones pantalla
const int W_WIDTH = 500;
const int W_HEIGHT = 500;
float	mourex = 0, mourey = 0, mourez = 3;
float 	mirarx = 0, mirary = 0, mirarz = 3;
bool mirar = false;

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
void moure() {
	if (!mirar) {
		
		gluLookAt(mourex, mourey, mourez, mourex, mourey, 0.0, 0.0, 1.0, 0.0);
	}
	else {
		gluLookAt(mourex, mourey, mourez, mirarx, mirary, 0.0, 0.0, 1.0, 0.0);
	}



	

	
}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//Desplazamos camara
	//Ver como funciona gluLookAt en: https://youtu.be/bmQmme9jKTc?t=315
	moure();

	

	glPushMatrix();
	glTranslatef(-10.0, -1.0, -15.0);
	draw_grid(20, 1);
	glPopMatrix();
	glTranslatef(0, 0,-1);
	drawSnowMan();
	glutSwapBuffers();
	glFlush();
}

void Idle(void)
{
	//Incrementamos el angulo de rotacion
	fAngTorus += 0.1 * directionTorus;


	glutPostRedisplay();
}
void controlTeclado(unsigned char key, int x, int y) {
	mirar = false;
	switch (key) {
	case 'w':
		mourez += 0.1;
		break;
	case 'a':
		mourex -= 0.1;
		break;
	case 's':
		mourez -= 0.1;
		break;
	case 'd':
		mourex += 0.1;
		break;
	}
	glutPostRedisplay();
}
void Special_Keys(int key, int x, int y)
{
	mirar = true;
	switch (key) {
		
	case GLUT_KEY_RIGHT:  mirarx += 0.1;   break;
	case GLUT_KEY_LEFT:  mirarx -= 0.1;  break;
	case GLUT_KEY_UP:  mirary += 0.1;  break;
	case GLUT_KEY_DOWN:  mirary -= 0.1;  break;
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
	glutKeyboardFunc(controlTeclado);
	glutReshapeFunc(reshape);

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1, 0.1, 0.1, 1.0);

	glutMainLoop();
	return 0;
}