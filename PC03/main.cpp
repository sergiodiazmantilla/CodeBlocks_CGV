#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

// Observador
float camaraX   = -20;
float camaraY   = 10;
float camaraZ   = 20;

float radio     = 42;
float angulo    = 2.55;
float centroY   = 10;

void iniciarVentana(int w, int h){
    // punto de vista
    glViewport(0,0,w,h);
    // cambiar la forma en la que vemos la profundida
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect3d = ((float)w / (float)h);
    // distancia a la que esta ubicado el enfoque del observador
    gluPerspective(60,aspect3d,1,200);
}

void inicializarLuces(){
    GLfloat luz_ambiente[]  = {0.35, 0.35,0.35};
    GLfloat luz_difusa[]    = {0.5, 0.5,0.5};
    GLfloat luz_especular[]  = {0.3, 0.3,0.3};

    float posicionLuz[] = {0,70,60,1};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_especular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicionLuz);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void piso(){
    glColor3ub(214,214,214);
    glBegin(GL_QUADS);
        glVertex3d(-100,0,-100);
        glVertex3d(100,0,-100);
        glVertex3d(100,0,100);
        glVertex3d(-100,0,100);
    glEnd();
}

void dibujarejes(){
    glLineWidth(2);
    glBegin(GL_LINES);
        glColor3ub(255,0,0);
        glVertex3d(0,0,0);
        glVertex3d(100,0,0);

        glColor3ub(0,255,0);
        glVertex3d(0,0,0);
        glVertex3d(0,100,0);

        glColor3ub(0,0,255);
        glVertex3d(0,0,0);
        glVertex3d(0,0,100);
    glEnd();
}

void tetera(){
    glPushMatrix();
        glColor3ub(153, 161, 175);
        glTranslated(0,20.7,0);
        glutSolidTeapot(3);
    glPopMatrix();
}

void mesa(){
    // Tablero
    glPushMatrix();
        glColor3ub(166, 95, 27);
        glTranslated(0,17,0);
        glScaled(12,1,12);
        glutSolidCube(3);
    glPopMatrix();

    // Patas
    glPushMatrix();
        glColor3ub(137, 75, 10);
        glTranslated(-12,9,-12);
        glScaled(1,6,1);
        glutSolidCube(3);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(137, 75, 10);
        glTranslated(12,9,-12);
        glScaled(1,6,1);
        glutSolidCube(3);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(137, 75, 10);
        glTranslated(-12,9,12);
        glScaled(1,6,1);
        glutSolidCube(3);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(137, 75, 10);
        glTranslated(12,9,12);
        glScaled(1,6,1);
        glutSolidCube(3);
    glPopMatrix();
}

void naranja(){
    // Cuerpo
    glPushMatrix();
        glColor3ub(254, 154, 55);
        glTranslated(5.0, 20.0, 5.0);
        glutSolidSphere(1.5, 20, 20);
    glPopMatrix();

    // Tallo
    glPushMatrix();
        glColor3ub(42, 166, 62);
        glTranslated(5.0, 21.7, 5.0);
        glScaled(1,7,1);
        glutSolidCube(0.1);
    glPopMatrix();

    // Hoja
    glPushMatrix();
        glColor3ub(34, 139, 34);
        glTranslated(4.6, 22.1, 5.0);
        glRotated(45, 0, 0, 1);
        glScaled(0.3, 1.2, 0.7);
        glutSolidSphere(0.5, 5, 15);
    glPopMatrix();
}

void taza(){
    // Cuerpo
    glPushMatrix();
        glColor3ub(245, 245, 245);
        glTranslated(-4.0, 18.5, 4.0);
        glRotated(-90, 1.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 1.0, 1.2, 2.5, 20, 20);
    glPopMatrix();

    // Base
    glPushMatrix();
        glColor3ub(245, 245, 245);
        glTranslated(-4.0, 18.5, 4.0);
        glRotated(90, 1.0, 0.0, 0.0);
        gluDisk(gluNewQuadric(), 0.0, 1.0, 20, 1);
    glPopMatrix();

    // Asa/Mango
    glPushMatrix();
        glColor3ub(245, 245, 245);
        glTranslated(-5.3, 19.7, 4.0);
        glutSolidTorus(0.12, 0.4, 15, 15);
    glPopMatrix();
}

void dibujar(){
    inicializarLuces();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(radio * cos(angulo),camaraY,radio * sin(angulo),0,centroY,0,0,1,0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    piso();
    dibujarejes();
    tetera();
    mesa();
    naranja();
    taza();

    glutSwapBuffers();
}

void timer(int t){
    glutPostRedisplay();
    glutTimerFunc(0,timer,0);
}

void teclado_especial(int tecla, int x, int y){
    //cout<<tecla<<endl;
    switch(tecla){
        case 100:
            angulo += 0.05;
            break;
        case 101:
            camaraY += 0.4;
            break;
        case 102:
            angulo -= 0.05;
            break;
        case 103:
            camaraY -= 0.4;
            break;
    }
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1420, 880);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Computacion Grafica - Practica de Campo 03");
    glutReshapeFunc(iniciarVentana);
    glutDisplayFunc(dibujar);
    glutTimerFunc(0,timer,0);
    glutSpecialFunc(teclado_especial);
    glutMainLoop();
    return 0;
}
