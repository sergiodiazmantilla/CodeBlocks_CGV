#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

//Observador
float camaraX   = -20;
float camaraY   = 10;
float camaraZ   = 20;

float radio     = 42;
float angulo    = 2.55;
float centroY   = 10;

void iniciarVentana(int w, int h){
    glViewport(0,0,w,h); //punto de vista
    glMatrixMode(GL_PROJECTION); // cambiar la forma en la que vemos la profundida
    glLoadIdentity();
    float aspect3d = ((float)w / (float)h);
    gluPerspective(60,aspect3d,1,200); // distancia a la que esta ubicado el enfoque del observador
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
        glColor3ub(228,0,247);
        glTranslated(0,2,0);
        glutSolidTeapot(3);
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
            angulo += 0.5;
            break;
        case 101:
            camaraY += 0.2;
            break;
        case 102:
            angulo -= 0.5;
            break;
        case 103:
            camaraY -= 0.2;
            break;
    }
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1420, 880);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Computacion Grafica 3D - Movimiento");
    glutReshapeFunc(iniciarVentana);
    glutDisplayFunc(dibujar);
    glutTimerFunc(0,timer,0);
    glutSpecialFunc(teclado_especial);
    glutMainLoop();
    return 0;
}
