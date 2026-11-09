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
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect3d = ((float)w / (float)h);
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
    glColor3ub(139, 69, 19);
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
        glTranslated(posx,0,0.3);
        glScaled(1.5,0.5,1.5);
        glutSolidSphere(3,50,50);
    glPopMatrix();
}

void pierna(float posx){
    glPushMatrix();
        glTranslated(posx,0,0);
        glRotated(-90,1,0,0);
        gluCylinder(gluNewQuadric(),4,4,6,50,50);
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
        glColor3ub(235, 169, 99);
        glTranslated(0,15.2,0);
        glutSolidSphere(8.2,100,100);
    glPopMatrix();
}

void gorra(){
    // Esfera
    glPushMatrix();
        glColor3ub(19, 19, 161);
        glTranslated(0,16,0);
        glutSolidSphere(7.8,100,100);
    glPopMatrix();

    // Aro
    glPushMatrix();
        glColor3ub(209, 0, 0);
        glTranslated(0,18.8,0);
        glRotated(-90,1,0,0);
        glutSolidTorus(1,7.2,50,50);
    glPopMatrix();

    // Bola Superior
    glPushMatrix();
        glColor3ub(209, 0, 0);
        glTranslated(0,23,0);
        glutSolidSphere(3,50,50);
    glPopMatrix();
}

void diente(float posx){
    glPushMatrix();
        glTranslated(posx,13.1,8.1);
        glutSolidCube(0.35);
    glPopMatrix();
}

void boca(){
    glPushMatrix();
        glColor3ub(0,0,0);
        glTranslated(0,12,7.35);
        glRotated(30,1,0,0);
        glScaled(1,0.8,0.2);
        glutSolidSphere(2,50,50);
    glPopMatrix();

    glColor3ub(255,255,255);
    diente(0.2);
    diente(-0.2);
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
        glTranslated(posx, 16, 8.3);
        glutSolidSphere(0.7,50,50);
    glPopMatrix();
}

void ceja(float posx, float rot){
    glPushMatrix();
        glColor3ub(0,0,0);
        glTranslated(posx, 17, 8);
        glRotated(-90,0,1,0);
        glRotated(rot,1,0,0);
        glScaled(0.3,1,1);
        gluCylinder(gluNewQuadric(), 0.5,0.1,3,50,50);
    glPopMatrix();
}

void base(){
    glPushMatrix();
        glTranslated(0, 3, 0);
        glRotated(-90,1,0,0);
        gluDisk(gluNewQuadric(),0,8,50,50);
    glPopMatrix();
}

void ovni(){
    // Platillo
    glPushMatrix();
        glScaled(1.0, 0.3, 1.0);
        glColor3ub(192,192,192);
        gluSphere(gluNewQuadric(), 4.0, 30, 30);
    glPopMatrix();

    // Borde o anillo central
    glPushMatrix();
        glRotated(90, 1, 0, 0);
        glColor3ub(0, 0, 0);
        gluCylinder(gluNewQuadric(), 4.1, 4.0, 0.35, 30, 10);
        glutSolidTorus(0.5, 4.1, 30, 30);
    glPopMatrix();

    // Cúpula superior
    glPushMatrix();
        glTranslated(0, 0.4, 0);
        glScaled(1.0, 0.8, 1.0);
        glColor4f(0.2f, 0.8f, 1.0f, 0.6f);
        gluSphere(gluNewQuadric(), 1.8, 20, 20);
    glPopMatrix();

    // Propulsor
    glPushMatrix();
        glTranslated(0, -1.0, 0);
        glRotated(90, 1, 0, 0);
        glColor3ub(0, 255, 0);
        gluCylinder(gluNewQuadric(), 1, 0.2, 0.7, 20, 10);
    glPopMatrix();
}

void ojom(float posx){
    glPushMatrix();
        glColor3ub(0, 0, 0);
        glTranslated(posx, 2.8, 1.2);
        glutSolidSphere(0.3, 10, 10);
    glPopMatrix();
}

void marciano(){
    // Cuerpo
    glPushMatrix();
        glColor3ub(0, 255, 0);
        glRotated(-90, 1, 0, 0);
        gluCylinder(gluNewQuadric(), 1.0, 0.5, 3.0, 20, 20);
    glPopMatrix();

    // Cabeza
    glPushMatrix();
            glTranslated(0, 3.5, 0);
            glColor3ub(0, 255, 0);
            glutSolidSphere(1.5, 30, 30);
    glPopMatrix();

    ojom(0.5);
    ojom(-0.5);
}

void luz_abd(){
    glPushMatrix();
        glColor4ub(200, 150, 50, 130);
        glRotated(-90,1,0,0);
        gluCylinder(gluNewQuadric(),20,5,60,80,80);
    glPopMatrix();
}

void caja(float posx, float posy, float posz, float rot){
    glPushMatrix();
        glTranslated(posx, posy, posz);
        glRotated(rot, 0, 1, 0);
        glRotated(15, 1, 0, 1);
        glColor3ub(139, 69, 19);
        glutSolidCube(3.5);
    glPopMatrix();
}

void arbol(float posx, float posy, float posz, float rot){
    glPushMatrix();
        glTranslated(posx, posy, posz);
        glRotated(rot, 0, 1, 1);

        // Tronco
        glPushMatrix();
            glColor3ub(100, 50, 0);
            glRotated(-90, 1, 0, 0);
            gluCylinder(gluNewQuadric(), 1.0, 1.0, 6.0, 20, 20);
        glPopMatrix();

        // Copa del árbol
        glPushMatrix();
            glTranslated(0, 6.5, 0);
            glColor3ub(34, 139, 34);
            glutSolidSphere(3.5, 30, 30);
        glPopMatrix();

    glPopMatrix();
}

void cajas(){
    caja(8.0, 3, 5.0, 25.0);
    caja(-9.0, 7.0, -6.0, -30.0);
    caja(6.0, 15.0, -8.0, 45.0);
}

void arboles(){
    arbol(-15.0, 2.0, 10.0, 5.0);
    arbol(14.0, 9.0, -12.0, -5.0);
    arbol(-4.0, 22.0, -5.0, 25.0);
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

    // Humano
    glPushMatrix();
        glTranslated(0,2,0);
        glScaled(0.5, 0.5, 0.5);

        glPushMatrix();
            glTranslated(0,3,0);
            glRotated(-20,1,0,0);
            ceja(3.5,-20);
            ceja(-3.5,-160);
            pupila(1.7);
            pupila(-1.7);
            ojo(1.7,-45);
            ojo(-1.7,45);
            boca();
            gorra();
            cabeza();

            glColor3ub(209, 0, 0);
            cuello();

            glColor3ub(0, 0, 0);
            lineaCuerpo();

            glColor3ub(166, 60, 25);
            cuerpo(3);
            base();
        glPopMatrix();

        glPushMatrix();
            glTranslated(0,2,-2.5);
            glColor3ub(209, 0, 0);
            mano(7.5);
            mano(-7.5);

            glColor3ub(166, 60, 25);
            brazo(5,50);
            brazo(-5,130);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0,3,-1);
            glRotated(5,1,0,0);
            glColor3ub(19, 19, 161);
            pierna(-3);
            pierna(3);
        glPopMatrix();

        glPushMatrix();
            glTranslated(0,2.6,-1);
            glRotated(16.2,1,0,0);
            glColor3ub(0,0,0);
            pie(-3);
            pie(3);
        glPopMatrix();
    glPopMatrix();

    // Marciano
    glPushMatrix();
        glTranslated(0,70.5,5);
        glRotated(20,1,0,0);
        glScaled(0.8,0.8,0.8);
        marciano();
    glPopMatrix();

    // Ovni
    glPushMatrix();
        glTranslated(0,60,0);
        glScaled(9,9,9);
        ovni();
    glPopMatrix();

    // Detalles Escenario
    cajas();
    arboles();
    luz_abd();
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
    glutCreateWindow("Computacion Grafica - Practica de Campo 04");
    glutReshapeFunc(iniciarVentana);
    glutDisplayFunc(dibujar);
    glutTimerFunc(0,timer,0);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclado_especial);
    glutMainLoop();
    return 0;
}
