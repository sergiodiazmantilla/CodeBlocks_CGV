#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include "RgbImage/RgbImage.h"

using namespace std;

GLuint arregloTexturas[10];

//Observador
float camaraX   = -20;
float camaraY   = 10;
float camaraZ   = 20;

float radio     = 42;
float angulo    = 2.55;
float centroY   = 10;

GLUquadric* quad;

void loadTextureFromFile(const char* filename, int index){
    RgbImage theTextMap(filename);
    glGenTextures(1, &arregloTexturas[index]);
    glBindTexture(GL_TEXTURE_2D, arregloTexturas[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, theTextMap.GetNumCols(), theTextMap.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, theTextMap.ImageData());
}

void cargarImagenes(){
    loadTextureFromFile("texturas/cuadros.bmp",0);
    loadTextureFromFile("texturas/goku.bmp",1);
    loadTextureFromFile("texturas/pared.bmp",2);
    loadTextureFromFile("texturas/tierra_cmp.bmp",3);
}

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
    glColor3ub(255,255,255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, arregloTexturas[0]);
    glBegin(GL_QUADS);
        glTexCoord2d(0,1); glVertex3d(-100,0,-100);
        glTexCoord2d(1,1); glVertex3d(100,0,-100);
        glTexCoord2d(1,0); glVertex3d(100,0,100);
        glTexCoord2d(0,0); glVertex3d(-100,0,100);
    glEnd();
    glDisable(GL_TEXTURE_2D);
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

void carroceria(float posX){
    glPushMatrix();
        glColor3ub(210,43,81);
        glTranslated(posX,0.8,0);
        glScaled(0.5,2,18);
        glutSolidCube(0.5);
    glPopMatrix();
}

void carroceria1(float posZ){
    glPushMatrix();
        glColor3ub(210,43,81);
        glTranslated(0,0.8,posZ);
        glScaled(10,2,0.5);
        glutSolidCube(0.5);
    glPopMatrix();
}

void cabina(){
    glPushMatrix();
        glColor3ub(233,187,139);
        glTranslated(0,2.8,0);
        glScaled(2.3,1.5,1.3);
        glutSolidCube(2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,0.85,3);
        glScaled(4.6,1,3);
        glutSolidCube(1);
    glPopMatrix();
}


void cabina1(){
    glPushMatrix();
        glColor3ub(255,255,255);
        glBegin(GL_QUADS);
            glVertex3d(-2.3,1.3,2.5);
            glVertex3d(2.3,1.3,2.5);
            glVertex3d(2.3,4.3,1.3);
            glVertex3d(-2.3,4.3,1.3);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(81,216,255);
        glBegin(GL_QUADS);
            glVertex3d(-2.1,1.5,2.51);
            glVertex3d(2.1,1.5,2.51);
            glVertex3d(2.1,4.1,1.4);
            glVertex3d(-2.1,4.1,1.4);
        glEnd();
    glPopMatrix();
}



void cabina2(float posX1, float posX2 ){
    glPushMatrix();
        glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
            glVertex3d(posX1,1.3,2.5);
            glVertex3d(posX1,4.3,1.3);
            glVertex3d(posX1,1.3,1.3);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(81,216,255);
        glBegin(GL_POLYGON);
            glVertex3d(posX2,1.5,2.4);
            glVertex3d(posX2,3.7,1.4);
            glVertex3d(posX2,1.5,1.4);
        glEnd();
    glPopMatrix();
}

void cabina3(float posX1, float posX2 ){
    glPushMatrix();
        glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
            glVertex3d(posX1,4.3,1.31);
            glVertex3d(posX1,1.3,1.31);
            glVertex3d(posX1,1.3,-1.3);
            glVertex3d(posX1,4.3,-1.3);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(81,216,255);
        glBegin(GL_POLYGON);
            glVertex3d(posX2,4.1,1.25);
            glVertex3d(posX2,1.5,1.25);
            glVertex3d(posX2,1.5,-1.1);
            glVertex3d(posX2,4.1,-1.1);
        glEnd();
    glPopMatrix();
}

void llanta1(float posZ){
    glPushMatrix();
        glTranslated(0,0,posZ);
        glPushMatrix();
            glColor3ub(50,50,50);
            glTranslated(-2.3,-0.5,0);
            glRotated(-90,0,1,0);
            gluCylinder(gluNewQuadric(),1,1,0.5,50,50);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-2.8,-0.5,0);
            glRotated(-90,0,1,0);
            gluDisk(gluNewQuadric(),0,1,50,50);
        glPopMatrix();
    glPopMatrix();
}

void llanta2(float posZ){
    glPushMatrix();
        glTranslated(0,0,posZ);
        glRotated(180,0,1,0);

        glPushMatrix();
            glColor3ub(50,50,50);
            glTranslated(-2.3,-0.5,0);
            glRotated(-90,0,1,0);
            gluCylinder(gluNewQuadric(),1,1,0.5,50,50);
        glPopMatrix();

        glPushMatrix();
            glTranslated(-2.8,-0.5,0);
            glRotated(-90,0,1,0);
            gluDisk(gluNewQuadric(),0,1,50,50);
        glPopMatrix();
    glPopMatrix();
}

void camioneta(){
    glPushMatrix();
        glTranslated(0,2,15);
        carroceria(-2.4);
        carroceria(2.4);
        carroceria1(-4.4);
        carroceria1(4.4);
        cabina();
        cabina1();
        cabina2(-2.3,-2.31);
        cabina2(2.3,2.31);
        cabina3(-2.31,-2.32);
        cabina3(2.31,2.32);
        llanta1(2.5);
        llanta1(-2.5);
        llanta2(2.5);
        llanta2(-2.5);
    glPopMatrix();
}

void cubo(){
    glColor3ub(245, 221, 39);
    glPushMatrix();
        glTranslated(0,5,0);
        glutSolidCube(10);
    glPopMatrix();
}

void ladoCubo(){
    glColor3ub(255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, arregloTexturas[1]);
    glPushMatrix();
        glTranslated(-5,0,5.001);
        glBegin(GL_QUADS);
            glTexCoord2d(0,1); glVertex3d(0,10,0);
            glTexCoord2d(1,1); glVertex3d(10,10,0);
            glTexCoord2d(1,0); glVertex3d(10,0,0);
            glTexCoord2d(0,0); glVertex3d(0,0,0);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void pared(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, arregloTexturas[2]);
    glPushMatrix();
        glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
            glTexCoord2d(0,0.25); glVertex3d(-50,10,-50);
            glTexCoord2d(1.6,0.25); glVertex3d(50,10,-50);
            glTexCoord2d(1.6,0); glVertex3d(50,0,-50);
            glTexCoord2d(0,0); glVertex3d(-50,0,-50);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void tierra(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, arregloTexturas[3]);
    glPushMatrix();
        glColor3ub(255,255,255);
        glTranslated(0,16,0);
        glRotated(-90,1,0,0);
        quad = gluNewQuadric();
        gluQuadricTexture(quad,1);
        gluSphere(quad,4,50,50);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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

    cubo();
    ladoCubo();
    pared();
    tierra();

    camioneta();

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
    glutCreateWindow("Computacion Grafica");
    cargarImagenes();
    glutReshapeFunc(iniciarVentana);
    glutDisplayFunc(dibujar);
    glutTimerFunc(0,timer,0);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(teclado_especial);
    glutMainLoop();
    return 0;
}
