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

void rueda(float posx, float posy, float posz, float tmn) {
    // Interior
    glPushMatrix();
        glColor3ub(69, 85, 108);
        glTranslated(posx, posy, posz);
        glutSolidTorus(2, tmn, 20, 20);
    glPopMatrix();

    // Exterior
    glPushMatrix();
        glColor3ub(106, 114, 130);
        glTranslated(posx, posy, posz);
        glutWireTorus(2,tmn,30,30);
    glPopMatrix();
}

// Funciones auxiliares para construir el letrero con planas (GL_QUADS)
void barraPlana(double x1, double y1, double x2, double y2) {
    glBegin(GL_QUADS);
        glVertex3d(x1, y1, 0.0);
        glVertex3d(x2, y1, 0.0);
        glVertex3d(x2, y2, 0.0);
        glVertex3d(x1, y2, 0.0);
    glEnd();
}
void barraInclinada(double xInfIzq, double xInfDer, double yInf, double xSupIzq, double xSupDer, double ySup) {
    glBegin(GL_QUADS);
        glVertex3d(xInfIzq, yInf, 0.0);
        glVertex3d(xInfDer, yInf, 0.0);
        glVertex3d(xSupDer, ySup, 0.0);
        glVertex3d(xSupIzq, ySup, 0.0);
    glEnd();
}

// Letras
void letraW() {
    glPushMatrix();
        barraInclinada(0.25, 0.45, 0.0, 0.0, 0.2, 1.5);
        barraInclinada(0.25, 0.45, 0.0, 0.55, 0.75, 0.9);
        barraInclinada(0.85, 1.05, 0.0, 0.55, 0.75, 0.9);
        barraInclinada(0.85, 1.05, 0.0, 1.1, 1.3, 1.5);
    glPopMatrix();
}
void letraA() {
    glPushMatrix();
        barraInclinada(0.0, 0.22, 0.0, 0.4, 0.6, 1.5);
        barraInclinada(0.78, 1.0, 0.0, 0.4, 0.6, 1.5);
        barraPlana(0.2, 0.55, 0.8, 0.75);
    glPopMatrix();
}
void letraL() {
    glPushMatrix();
        barraPlana(0.0, 0.0, 0.22, 1.5);
        barraPlana(0.0, 0.0, 0.85, 0.22);
    glPopMatrix();
}
void letraE() {
    glPushMatrix();
        barraPlana(0.0, 0.0, 0.22, 1.5);
        barraPlana(0.0, 1.28, 0.85, 1.5);
        barraPlana(0.0, 0.65, 0.7, 0.85);
        barraPlana(0.0, 0.0, 0.85, 0.22);
    glPopMatrix();
}

void letreroFrontalWallE() {
    glPushMatrix();
        glTranslated(-1.5, 9.2, 5.02);
        glScaled(0.3, 0.3, 0.3);
        glColor3ub(30, 30, 30);

        // W
        glPushMatrix();
            glTranslated(0.0, 0.0, 0.0);
            letraW();
        glPopMatrix();

        // A
        glPushMatrix();
            glTranslated(1.55, 0.0, 0.0);
            letraA();
        glPopMatrix();

        // L
        glPushMatrix();
            glTranslated(2.8, 0.0, 0.0);
            letraL();
        glPopMatrix();

        // L
        glPushMatrix();
            glTranslated(3.85, 0.0, 0.0);
            letraL();
        glPopMatrix();

        // Punto separador (·)
        glPushMatrix();
            glTranslated(4.9, 0.65, 0.0);
            barraPlana(0.0, 0.0, 0.25, 0.25);
        glPopMatrix();

        // Fondo rojo de la E
        glPushMatrix();
            glColor3ub(180, 30, 30);
            glTranslated(5.3, -0.15, -0.01);
            barraPlana(0.0, 0.0, 1.2, 1.8);
        glPopMatrix();

        // E
        glPushMatrix();
            glColor3ub(240, 240, 230);
            glTranslated(5.48, 0.0, 0.0);
            letraE();
        glPopMatrix();
    glPopMatrix();
}

void cuerpo(){
    // principal
    glPushMatrix();
        glColor3ub(208, 135, 46);
        glTranslated(0,9.5,0);
        glScaled(1.5,1.1,1);
        glutSolidCube(10);
    glPopMatrix();

    // consola
    glPushMatrix();
        glColor3ub(144, 161, 185);
        glTranslated(-8.0,12.2,0);
        glScaled(0.1,0.7,1.5);
        glutSolidCube(5);
    glPopMatrix();

    // puerta 1
    glPushMatrix();
        glColor3ub(166, 95, 27);
        glTranslated(-8,7.3,0);
        glScaled(0.1,1.1,1.5);
        glutSolidCube(5);
    glPopMatrix();

    // puerta 2
    glPushMatrix();
        glColor3ub(166, 95, 27);
        glTranslated(8,7.3,0);
        glScaled(0.1,1.1,1.5);
        glutSolidCube(5);
    glPopMatrix();

    letreroFrontalWallE();

    glPushMatrix();
        glTranslated(6.8,-11,0.7);
        glRotated(-90,0,1,0);
        glScaled(2,2,3);
        letreroFrontalWallE();
    glPopMatrix();
}

void soporte(){
    // soporte principal
    glPushMatrix();
        glColor3ub(166, 95, 27);
        glTranslated(0,16.9,0);
        glRotated(90,1,0,0);
        glRotated(10,0,1,0);
        //glScaled(2,2,3);
        gluCylinder(gluNewQuadric(), 0.8, 0.8, 2, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glTranslated(0,16.8,0);
        glRotated(90,1,0,0);
        glRotated(10,0,1,0);
        gluDisk(gluNewQuadric(), 0, 0.8, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(202, 213, 226);
        glTranslated(0.3, 15.1, 0);
        glutSolidSphere(0.9,20,20);
    glPopMatrix();

    // pieza 1
    glPushMatrix();
        glColor3ub(253, 199, 69);
        glTranslated(-1.8,18.8,0);
        glRotated(90,1,0,0);
        glRotated(40,0,1,0);;
        gluCylinder(gluNewQuadric(), 0.5, 0.5, 3, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(202, 213, 226);
        glTranslated(-2, 19.3, 0);
        glutSolidSphere(0.8,20,20);
    glPopMatrix();

    //pieza 2
    glPushMatrix();
        glColor3ub(253, 199, 69);
        glTranslated(0.9,21.9,0);
        glRotated(90,1,0,0);
        glRotated(-50,0,1,0);
        gluCylinder(gluNewQuadric(), 0.5, 0.5, 3.5, 50, 50);
    glPopMatrix();
    glPushMatrix();
        glColor3ub(202, 213, 226);
        glTranslated(0.8, 22.0, 0);
        glutSolidSphere(0.8,20,20);
    glPopMatrix();

    // ojos

}

void brazo(float posy, float posz, float rot){
    glPushMatrix();
        glTranslated(-4.0, posy, posz);
        glRotated(rot,0,0,1);
        glScaled(7,1.1,1);
        glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
        glTranslated(-1.0, 13, posz);
        glutSolidSphere(1,20,20);
    glPopMatrix();
}

void visor(float posx, float trx){
    glPushMatrix();
        glColor3ub(144, 161, 185);
        glTranslated(posx, 1, 1.0);
        glRotated(90.0, 1.0, 0.0, 0.0);
        glScaled(1,1,1.5);
        gluCylinder(gluNewQuadric(), 0.9, 0.9, 2.2, 30, 30);
        // front
        glPushMatrix();
            glColor3ub(144, 161, 185);
            glTranslated(0.0, 0.0, 2.21);
            gluDisk(gluNewQuadric(), 0.0, 0.9, 20, 20);
        glPopMatrix();
        // back
        glPushMatrix();
            glColor3ub(144, 161, 185);
            glTranslated(0.0, 0.0, 0);
            gluDisk(gluNewQuadric(), 0.0, 0.9, 20, 20);
        glPopMatrix();
        // punta
        glPushMatrix();
            glColor3ub(144, 161, 185);
            glTranslated(trx, -0.45, 1.1);
            glScaled(1,1,2.4);
            glutSolidCube(0.9);
        glPopMatrix();
        // lente
        glPushMatrix();
            glColor3ub(255, 255, 255);
            glTranslated(0.0, 0.0, 2.21);
            glScaled(1,1,0.2);
            glutSolidSphere(0.8,30,30);
        glPopMatrix();
    glPopMatrix();
}

void cabeza(){
    glPushMatrix();
        // posicion
        glTranslated(0.0, 25, 0.0);
        glRotated(90,1,0,0);
        glRotated(-90,0,0,1);
        glScaled(2,2,2);

        visor(1.2, -0.45);
        visor(-1.2, 0.45);

        // union
        glPushMatrix();
            glColor3ub(140, 120, 40);
            glTranslated(0.0, 0.7, 1.2);
            glScaled(2.4, 0.7, 0.7);
            glutSolidCube(1.0);
        glPopMatrix();

    glPopMatrix();
}
int vista = 0;

// Dibujar una esfera escalada
void esfera(float x, float y, float z,
            float sx, float sy, float sz,
            float r, float g, float b) {

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glColor3f(r, g, b);
    glutSolidSphere(1.0, 32, 32);

    glPopMatrix();
}

// Dibujar un cubo escalado
void cubo(float x, float y, float z,
          float sx, float sy, float sz,
          float r, float g, float b) {

    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);

    glColor3f(r, g, b);
    glutSolidCube(1.0);

    glPopMatrix();
}

// Cilindro orientado horizontalmente

void cilindroHorizontal(float x, float y, float z,
                        float radio, float altura,
                        float r, float g, float b) {

    glPushMatrix();

    glTranslatef(x, y, z);
    glRotatef(90, 0, 1, 0);

    glColor3f(r, g, b);

    GLUquadric* cilindro = gluNewQuadric();

    gluQuadricNormals(cilindro, GLU_SMOOTH);

    gluCylinder(cilindro, radio, radio, altura, 24, 8);

    gluDeleteQuadric(cilindro);

    glPopMatrix();
}


void cuerpoNave() {

    // Estructura principal
    esfera(0, 0, 0, 2.7, 1.05, 0.75,0.78, 0.82, 0.88);

    // Parte inferior oscura
    esfera(-0.1, 0, -0.38, 2.45, 0.92, 0.40,0.30, 0.35, 0.42);

    // Cubierta superior
    esfera(-0.25, 0, 0.48, 2.15, 0.90, 0.30,0.90, 0.93, 0.98);

    // Cabina frontal
    esfera(1.85, 0, 0.52, 0.85, 0.77, 0.38,0.05, 0.30, 0.65);

    // Brillo de la cabina
    esfera(2.05, 0, 0.73, 0.48, 0.56, 0.13,0.15, 0.65, 0.95);

    // Ventanas laterales
    for (int lado = -1; lado <= 1; lado += 2) {

        for (int i = 0; i < 4; i++) {

            esfera(0.4 - i * 0.65,
                   lado * 0.91,
                   0.30,
                   0.22, 0.055, 0.16,
                   0.05, 0.55, 0.90);
        }
    }
}

// ======================================
// ALAS LATERALES
// ======================================

void alas() {

    for (int lado = -1; lado <= 1; lado += 2) {

        // Ala principal
        cubo(-0.5, lado * 1.45, -0.05,
             2.1, 1.0, 0.13,
             0.68, 0.73, 0.82);

        // Punta del ala
        esfera(-0.5, lado * 1.95, -0.05,
               0.65, 0.25, 0.10,
               0.25, 0.38, 0.55);

        // Luces de las alas
        esfera(-0.5, lado * 2.05, 0.08,
               0.13, 0.13, 0.13,
               0.0, 0.85, 1.0);
    }
}

// ======================================
// MOTORES POSTERIORES
// ======================================

void motores() {

    for (int lado = -1; lado <= 1; lado += 2) {

        for (int nivel = 0; nivel < 2; nivel++) {

            float z = (nivel == 0) ? 0.30 : -0.35;
            float y = lado * 0.58;

            // Carcasa del motor
            cilindroHorizontal(-3.1, y, z,
                               0.30, 0.85,
                               0.38, 0.43, 0.52);

            // Salida luminosa
            esfera(-3.98, y, z,
                   0.10, 0.23, 0.23,
                   0.0, 0.65, 1.0);

            // Anillo exterior
            glPushMatrix();

            glTranslatef(-3.12, y, z);
            glRotatef(90, 0, 1, 0);

            glColor3f(0.15, 0.55, 0.95);
            glutSolidTorus(0.055, 0.31, 12, 24);

            glPopMatrix();
        }
    }
}

// ======================================
// SOPORTES DE ATERRIZAJE
// ======================================

void soportes() {

    for (int lado = -1; lado <= 1; lado += 2) {

        // Patas
        cubo(-0.6, lado * 0.65, -0.82,
             0.16, 0.16, 0.75,
             0.30, 0.34, 0.40);

        // Bases
        esfera(-0.6, lado * 0.65, -1.18,
               0.38, 0.30, 0.10,
               0.12, 0.16, 0.22);
    }
}

// ======================================
// DETALLES FUTURISTAS
// ======================================

void detalles() {

    // Antenas superiores
    cilindroHorizontal(0, 0, 0,
                       0.07, 0.01,
                       0.30, 0.35, 0.40);

    esfera(-1.0, 0, 0.85,
           0.12, 0.12, 0.12,
           0.0, 0.85, 1.0);

    // Luces de navegaci n
    esfera(2.2, 0.65, 0.10,
           0.12, 0.12, 0.12,
           0.0, 1.0, 1.0);

    esfera(2.2, -0.65, 0.10,
           0.12, 0.12, 0.12,
           1.0, 0.15, 0.15);

    // Franja decorativa lateral
    for (int lado = -1; lado <= 1; lado += 2) {

        cubo(-0.5, lado * 1.02, -0.10,
             2.0, 0.035, 0.08,
             0.05, 0.55, 0.90);
    }
}

// ======================================
// ESCENARIO
// ======================================

void escenario() {

    // Suelo
    glDisable(GL_LIGHTING);

    glColor3f(0.18, 0.22, 0.30);

    glBegin(GL_LINES);

    for (int i = -12; i <= 12; i++) {

        glVertex3f(i, -12, -1.5);
        glVertex3f(i, 12, -1.5);

        glVertex3f(-12, i, -1.5);
        glVertex3f(12, i, -1.5);
    }

    glEnd();

    glEnable(GL_LIGHTING);
}


void walle(){
    rueda(5.0, 5.1, -7.0, 3.0);
    rueda(-5.0, 4.1, 7.0, 2.0);
    rueda(-5.0, 4.1, -7.0, 2.0);
    rueda(5.0, 5.1, 7.0, 3.0);

    cuerpo();
    brazo(13,5.7,0);
    brazo(12.4,-5.7,15);
    soporte();
    cabeza();
}

void dibujarNave() {

    cuerpoNave();
    alas();
    motores();
    soportes();
    detalles();
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

    walle();

    glPushMatrix();
        glTranslated(30,30,30);
        glScaled(10,10,10);
        glRotated(-90,1,0,0);
        dibujarNave();
    glPopMatrix();


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
