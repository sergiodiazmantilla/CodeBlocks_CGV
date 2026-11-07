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

void pie(float posx){
    glPushMatrix();
        glTranslated(posx,0,0);
        glScaled(1.5,0.3,1.5);
        glutSolidSphere(3,50,50);
    glPopMatrix();
}

void pierna(float posx){
    glPushMatrix();
        glTranslated(posx,0,0);
        glRotated(-90,1,0,0);
        gluCylinder(gluNewQuadric(),4,4,4,50,50);
    glPopMatrix();
}

void cuerpo(float posy){
    glPushMatrix();
        glTranslated(0,posy,0);
        glRotated(-90,1,0,0);
        gluCylinder(gluNewQuadric(),8,6,7,50,50);
    glPopMatrix();
}

void brazo(float posx, float rot){
    glPushMatrix();
        glTranslated(posx,9,0);
        glRotated(90,0,1,0);
        glRotated(rot,1,0,0);
        gluCylinder(gluNewQuadric(),1.5,1.5,4.8,50,50);
    glPopMatrix();
}

void mano(float posx){
    glPushMatrix();
        glTranslated(posx,5.5,0);
        glScaled(1,0.75,0.65);
        glutSolidSphere(2,50,50);
    glPopMatrix();
}

void lineaCuerpo(){
    glPushMatrix();
        glTranslated(0,6.5,6.6);
        glRotated(-16,1,0,0);
        glScaled(0.5,7,1);
        glutSolidCube(1);
    glPopMatrix();
}

void cuello(){
    glPushMatrix();
        glTranslated(0,10,0);
        glRotated(-90,1,0,0);
        glScaled(0.6,0.6,0.6);
        glutSolidTorus(1,10,50,50);
    glPopMatrix();
}

void cabeza(){
    glPushMatrix();
        glColor3ub(255,204,153);
        glTranslated(0,15.2,0);
        glutSolidSphere(8.2,100,100);
    glPopMatrix();
}

void gorra(){
    // Esfera
    glPushMatrix();
        glColor3ub(76,51,25);
        glTranslated(0,16,0);
        glutSolidSphere(7.8,100,100);
    glPopMatrix();

    // Aro
    glPushMatrix();
        glColor3ub(255,178,0);
        glTranslated(0,18.8,0);
        glRotated(-90,1,0,0);
        glutSolidTorus(1,7.2,50,50);
    glPopMatrix();

    // Bola Superior
    glPushMatrix();
        glTranslated(0,23,0);
        glutSolidSphere(3,50,50);
    glPopMatrix();
}

void diente(float posx){
    glPushMatrix();
        glTranslated(posx,12.3,7.7);
        glutSolidCube(0.35);
    glPopMatrix();
}

void boca(){
    glPushMatrix();
        glColor3ub(0,0,0);
        glTranslated(0,12.5,7.35);
        glScaled(1,0.8,0.2);
        glutSolidSphere(2,50,50);
    glPopMatrix();

    glColor3ub(255,255,255);
    diente (0.2);
    diente (-0.2);
}

void ojo(float posx, float rot){
    glPushMatrix();
        glColor3ub(255,255,255);
        glTranslated(posx,15,6.9);
        glRotated(rot,0,0,1);
        glScaled(0.9,0.7,0.7);
        glutSolidSphere(2.8,50,50);
    glPopMatrix();
}

void pupila(float posx){
    glPushMatrix();
        glColor3ub(0,0,0);
        glTranslated(posx, 15, 8.5);
        glutSolidSphere(0.7,50,50);
    glPopMatrix();
}

void ceja(float posx, float rot){
    glPushMatrix();
        glColor3ub(0,0,0);
        glTranslated(posx, 19, 8);
        glRotated(-90,0,1,0);
        glRotated(rot,1,0,0);
        glScaled(0.3,1,1);
        gluCylinder(gluNewQuadric(), 0.5,0.1,3,50,50);
    glPopMatrix();
}

void dibujar(){
    inicializarLuces();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(camaraX, CamaraY, CamaraZ, 0,0,0,0,1,0);
    gluLookAt(radio * cos(angulo),camaraY,radio * sin(angulo),0,centroY,0,0,1,0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(66/255.0, 211/255.0, 242/255.0,1);

    piso();
    dibujarejes();

    ceja(3,45);
    ceja(-3,135);
    pupila(1.7);
    pupila(-1.7);
    ojo(1.7,-45);
    ojo(-1.7,45);
    boca();
    gorra();
    cabeza();

    glColor3ub(0,0,0);
    cuello();
    lineaCuerpo();

    glColor3ub(0,0,0);
    pie(-3);
    pie(3);

    glColor3ub(146,82,0);
    mano(7.5);
    mano(-7.5);

    glColor3ub(255,127,0);
    pierna(-3);
    pierna(3);
    cuerpo(3);
    brazo(5,50);
    brazo(-5,130);

    glutSwapBuffers();
}

void timer(int t){
    glutPostRedisplay();
    glutTimerFunc(0,timer,0);
}

void teclado(unsigned char key, int x, int y){
    switch(key){
        case 'n':
            radio -= 0.5;
            break;
        case 'm':
            radio += 0.5;
            break;
        case 'j':
            centroY -= 0.5;
            break;
        case 'k':
            centroY += 0.5;
            break;
    }
}

void teclado_especial(int tecla, int x, int y){
    //cout<<tecla<<endl;
    switch(tecla){
        case 100:
            angulo += 0.3;
            break;
        case 101:
            camaraY += 0.5;
            break;
        case 102:
            angulo -= 0.3;
            break;
        case 103:
            camaraY -= 0.5;
            break;
    }
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1420, 880);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Computacion Grafica 3D - Personaje Terminado + ZOOM");
    glutReshapeFunc(iniciarVentana);
    glutDisplayFunc(dibujar);
    glutTimerFunc(0,timer,0);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclado_especial);
    glutMainLoop();
    return 0;
}
