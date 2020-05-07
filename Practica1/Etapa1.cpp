/*#include <gl/glut.h>
float alpha, beta;
int x0, y0;
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f);
    glRotatef(alpha, 1.0f, 0.0f, 0.0f);
    glRotatef(beta, 0.0f, 1.0f, 0.0f);
    glutWireTeapot(0.5);
    glFlush();
    glutSwapBuffers();
}
void onMouse(int button, int state, int x, int y) {
   
        if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN)) {
                    x0 = x; y0 = y;
                }
}
void onMotion(int x, int y) {
                
                    alpha = (alpha + (y - y0));
                    beta = (beta +  (x - x0));
                    x0 = x; y0 = y; 
                    glutPostRedisplay();
}
void main(void) {
                    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
                    glutInitWindowSize(400, 400);
                    glutInitWindowPosition(100, 100);
                    glutCreateWindow("Ejemplo de menus");
                    glutDisplayFunc(display);
                    glutMouseFunc(onMouse);
                    glutMotionFunc(onMotion); 
                    glutMainLoop();
                }*/


/*
#include <gl/glut.h>
int iFondo = 0;
int iDibujo = 3;
typedef enum { FONDO1, FONDO2, FONDO3, FONDO4, DIBUJO1, DIBUJO2, DIBUJO3, DIBUJO4 }
opcionesMenu;
void onMenu(int opcion) {
    switch (opcion) {
    case FONDO1:
        iFondo = 0;
        break;
    case FONDO2:
        iFondo = 1;
        break;
    case FONDO3:
        iFondo = 2;
        break;
    case DIBUJO1:
        iDibujo = 3;
        break;
    case DIBUJO2:
        iDibujo = 4;
        break;
    case DIBUJO3:
        iDibujo = 5;
        break;
        
    }
    glutPostRedisplay(); 
}
void creacionMenu(void) {
    int menuFondo, menuDibujo, menuPrincipal;

    menuFondo = glutCreateMenu(onMenu);
    glutAddMenuEntry("Negro", FONDO1);
    glutAddMenuEntry("Verde oscuro", FONDO2);
    glutAddMenuEntry("Azul oscuro", FONDO3);
    menuDibujo = glutCreateMenu(onMenu);
    glutAddMenuEntry("Blanco", DIBUJO1);
    glutAddMenuEntry("Verde claro", DIBUJO2);
    glutAddMenuEntry("Azul claro", DIBUJO3);
    menuPrincipal = glutCreateMenu(onMenu);
    glutAddSubMenu("Color de fondo", menuFondo );
    glutAddSubMenu("Color de dibujo", menuDibujo);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void display(void) {
    float colores[6][3] = {
    { 0.00f, 0.00f, 0.00f}, // 0 - negro
    { 0.06f, 0.25f, 0.13f}, // 1 - verde oscuro
    { 0.10f, 0.07f, 0.33f}, // 2 - azul oscuro
    { 1.00f, 1.00f, 1.00f}, // 3 - blanco
    { 0.12f, 0.50f, 0.26f}, // 4 - verde claro
    { 0.20f, 0.14f, 0.66f}, // 5 - azul claro
    };
    glClearColor(colores[iFondo][0], colores[iFondo][1], colores[iFondo][2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(colores[iDibujo][0], colores[iDibujo][1], colores[iDibujo][2]);
    glutWireTeapot(0.5);
    glFlush();
    glutSwapBuffers();
}
void main(void) {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Ejemplo de menus");
    glutDisplayFunc(display);
    creacionMenu(); 
    glutMainLoop();
}
*/

// Etapa1.cpp
// Fichero principal 
////////////////////////////////////////////////////

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
const int W_WIDTH = 500; // Tama?o incial de la ventana
const int W_HEIGHT = 500;
GLfloat fAngulo; // Variable que indica el ?ngulo de rotaci?n de los ejes. 

// Funci?n que visualiza la escena OpenGL
void Display(void)
{
    // Borramos la escena
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    // Rotamos las proximas primitivas
    glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
    // Creamos a continuaci?n dibujamos los tres poligonos
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
    glPopMatrix();

    glFlush();
}

// Funci?n que se ejecuta cuando el sistema no esta ocupado
void Idle(void)
{
    // Incrementamos el ?ngulo
    fAngulo += 0.3f;
    // Si es mayor que dos pi la decrementamos
    if (fAngulo > 360)
        fAngulo -= 360;
    // Indicamos que es necesario repintar la pantalla
    glutPostRedisplay();
}

// Funci?n principal
int main(int argc, char** argv)
{
    // Inicializamos la librer?a GLUT
    glutInit(&argc, argv);

    // Indicamos como ha de ser la nueva ventana
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    // Creamos la nueva ventana
    glutCreateWindow("Mi primera Ventana - Etapa 1");

    // Indicamos cuales son las funciones de redibujado e idle
    glutDisplayFunc(Display);
    glutIdleFunc(Idle);

    // El color de fondo ser? el negro (RGBA, RGB + Alpha channel)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

    // Comienza la ejecuci?n del core de GLUT
    glutMainLoop();
    return 0;
}