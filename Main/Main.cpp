// Etapa5.cpp
// Fichero principal 
////////////////////////////////////////////////////
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

const int W_WIDTH = 500; // Tama�o incial de la ventana
const int W_HEIGHT = 500;

GLenum shadingMode;

bool isFirstLight;
GLfloat firstLightPos[] = { -0.2f, 0.0f, 1.0f };
GLfloat secondLigthPos[] = { -0.2f, 0.0f, -0.03f };

GLfloat lightDifuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat lightEspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

GLfloat materialAmbient0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialEspecular0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDifuse0[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat materialAmbient1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat materialEspecular1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDifuse1[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat materialAmbient2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialEspecular2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDifuse2[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat materialAmbient3[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat materialEspecular3[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat materialDifuse3[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat materialAmbient4[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat materialEspecular4[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat materialDifuse4[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat materialAmbient5[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat materialEspecular5[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat materialDifuse5[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat materialAmbient6[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialEspecular6[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDifuse6[] = { 0.5f, 0.5f, 0.5f, 1.0f };

GLfloat materialAmbient7[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialEspecular7[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDifuse7[] = { 1.0f, 1.0f, 1.0f, 1.0f };

GLfloat materialAmbient8[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialEspecular8[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialDifuse8[] = { 1.0f, 1.0f, 1.0f, 1.0f };

float angleTeapot;

void ReshapeWindow(int width, int height) {

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20, width / height, 1, 20);
	glMatrixMode(GL_MODELVIEW);

}

void DisplayPlano(void) {

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1.0, -1, 0);
	glEnd();
	glPopMatrix();
}

void DrawCoordinates() {
	glPushMatrix();
	glBegin(GL_LINES);

	// ROSA
	glColor3f(0.803f, 0.125f, 1.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// ROJO
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	// AMARILLO
	glColor3f(1.0f, 0.803f, 0.125f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// VERDE
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	// LILA
	glColor3f(0.229f, 0.167f, 0.392f);
	glVertex3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	// AZUL
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();

	glPopMatrix();
}

void DrawSphere(GLfloat x, GLfloat y, GLfloat z, int colorMaterialIndex) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(1.0f, 0.0f, 0.0f);

	switch (colorMaterialIndex) {
	case 0:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular0);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDifuse0);
		break;
	case 1:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDifuse1);
		break;
	case 2:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDifuse2);
		break;
	case 3:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient3);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular3);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDifuse3);
		break;
	case 4:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient4);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular4);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDifuse4);
		break;
	case 5:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient5);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular5);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDifuse5);
		break;
	case 6:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient6);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular6);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDifuse6);
		break;
	case 7:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient7);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular7);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDifuse7);
		break;
	case 8:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient8);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialEspecular8);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDifuse8);
		break;
	}

	glutSolidSphere(0.1, 100, 100);
	glPopMatrix();
}

void DrawSphere(GLfloat x, GLfloat y, GLfloat z) {
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(0.1, 100, 100);
	glPopMatrix();
}

// Funcion que visualiza la escena OpenGL
void DisplayMainScene(void)
{
	GLfloat* lightPosition;
	if (isFirstLight) {
		lightPosition = firstLightPos;
	}
	else {
		lightPosition = secondLigthPos;
	}
	// Borramos la escena
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	DrawCoordinates();

	glPushMatrix();
	glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightEspecular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifuse);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.1, 100, 100);
	glPopMatrix();

	DrawSphere(-0.5f, 0.5f, 0.0f, 0);
	DrawSphere(0.0f, 0.5f, 0.0f, 1);
	DrawSphere(0.5f, 0.5f, 0.0f, 2);

	DrawSphere(-0.5f, 0.0f, 0.0f, 3);
	DrawSphere(0.0f, 0.0f, 0.0f, 4);
	DrawSphere(0.5f, 0.0f, 0.0f, 5);

	DrawSphere(-0.5f, -0.5f, 0.0f, 6);
	DrawSphere(0.0f, -0.5f, 0.0f, 7);
	DrawSphere(+0.5f, -0.5f, 0.0f, 8);

	glFlush();

	glutSwapBuffers();
}


// Funci�n que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
	if (angleTeapot > 360) {
		angleTeapot = 0.0f;
	}
	angleTeapot += 0.05f;

	glutPostRedisplay();
}

void KeyboardController(unsigned char key, int x, int y) {

	GLfloat* lightPosition;
	if (isFirstLight) {
		lightPosition = firstLightPos;
	}
	else {
		lightPosition = secondLigthPos;
	}

	switch (key) {
	case ' ':
		shadingMode = (shadingMode == GL_FLAT) ? GL_SMOOTH : GL_FLAT;
		glShadeModel(shadingMode);
		break;
	case 'l':
		isFirstLight = !isFirstLight;
		break;

	case 'y':
		//GLfloat lightDifuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
		//GLfloat lightEspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		//GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		lightAmbient[0] += 0.1f;
		lightAmbient[1] += 0.1f;
		lightAmbient[2] += 0.1f;
		break;
	case 'h':
		lightAmbient[0] -= 0.1f;
		lightAmbient[1] -= 0.1f;
		lightAmbient[2] -= 0.1f;
		break;
	case 'u':
		lightEspecular[0] += 0.1f;
		lightEspecular[1] += 0.1f;
		lightEspecular[2] += 0.1f;
		break;
	case 'j':
		lightEspecular[0] -= 0.1f;
		lightEspecular[1] -= 0.1f;
		lightEspecular[2] -= 0.1f;
		break;
	case 'i':
		lightDifuse[0] += 0.1f;
		lightDifuse[1] += 0.1f;
		lightDifuse[2] += 0.1f;
		break;
	case 'k':
		lightDifuse[0] -= 0.1f;
		lightDifuse[1] -= 0.1f;
		lightDifuse[2] -= 0.1f;
		break;
	case 'a': //X derecha
		lightPosition[0] += 0.01;
		break;
	case 'z': //X izquierda
		lightPosition[0] -= 0.01;
		break;
	case 's': //Y arriba
		lightPosition[1] += 0.01;
		break;
	case 'x': //Y abajo
		lightPosition[1] -= 0.01;
		break;
	case 'd': //Z mas profundidad
		lightPosition[2] += 0.01;
		break;
	case 'c': //Z menos profundidad
		lightPosition[2] -= 0.01;
		break;

	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "X: " << lightPosition[0] << ", Y: " << lightPosition[1] << ", Z: " << lightPosition[2] << endl;
	cout << "AMBIENT: " << lightAmbient[0] << ", " << lightAmbient[1] << ", " << lightAmbient[2] << endl;
	cout << "ESPECULAR: " << lightEspecular[0] << ", " << lightEspecular[1] << ", " << lightEspecular[2] << endl;
	cout << "DIFUSE: " << lightDifuse[0] << ", " << lightDifuse[1] << ", " << lightDifuse[2] << endl;

}

void initializeComponents() {
	angleTeapot = 0.0f;
	isFirstLight = true;
	shadingMode = GL_FLAT;
	glShadeModel(shadingMode);
}

// Funcion principal
int main(int argc, char** argv)
{

	// Inicializamos la librer�a GLUT
	glutInit(&argc, argv);

	// Indicamos como ha de ser la nueva ventana
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(W_WIDTH, W_HEIGHT);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// Creamos la nueva ventana
	glutCreateWindow("Ventana etapa 5");

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	//First light for scene
	glEnable(GL_LIGHT0);

	initializeComponents();

	// Indicamos cuales son las funciones de redibujado e idle
	glutReshapeFunc(ReshapeWindow);
	glutDisplayFunc(DisplayMainScene);
	glutKeyboardFunc(KeyboardController);
	glutIdleFunc(Idle);

	// El color de fondo ser� el negro (RGBA, RGB + Alpha channel)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Comienza la ejecuci�n del core de GLUT
	glutMainLoop();
	return 0;
}