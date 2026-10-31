#include <GL/glut.h>
#include <math.h>

void cielo(){
    glBegin(GL_POLYGON);
        glColor3ub(253,40,6);
        glVertex2d(0,10);
        glVertex2d(15,10);

        glColor3ub(248,202,155);
        glVertex2d(15,3.2);
        glVertex2d(0,3.2);
    glEnd();
}

void mar(){
    glBegin(GL_QUADS);
        glColor3ub(252,41,7);
        glVertex2d(0,3.2);
        glVertex2d(15,3.2);

        glColor3ub(5,171,235);
        glVertex2d(15,0);
        glVertex2d(0,0);
    glEnd();
}

void sol1(){
    float radio = 2;
    float cx, cy;

    glColor3ub(250,218,186);
    glBegin(GL_POLYGON);
        for(double i=0; i< (2 * M_PI); i += 0.001){
            cx = radio * cos(i);
            cy = radio * sin(i);
            glVertex2d(cx+1.5,cy+9);
        }
    glEnd();
}

void sol2(){
    float radio = 2;
    float cx, cy;

    glColor3ub(218,94,84);
    glBegin(GL_POLYGON);
        for(double i=0; i< (2 * M_PI); i += 0.001){
            cx = radio * cos(i);
            cy = radio * sin(i);
            glVertex2d(cx+1.3,cy+9.2);
        }
    glEnd();
}

void base(){
    glBegin(GL_POLYGON);
        glColor3ub(0,0,0);
        glVertex2d(5.9,2.3);
        glVertex2d(10.27,2.3);

        glColor4ub(250,0,0,0);
        glVertex2d(9.99,1.84);
        glVertex2d(6.18,1.84);
    glEnd();
}
void mastil(){
    glBegin(GL_POLYGON);
        glColor3ub(0,0,0);
        glVertex2d(7.25,4.8);
        glVertex2d(7.35,4.8);
        glVertex2d(7.35,2.3);
        glVertex2d(7.25,2.3);
    glEnd();
}
void vela(){
    glBegin(GL_POLYGON);
        glColor3ub(242,156,139);
        glVertex2d(7.32,4.59);
        glVertex2d(8.19,2.79);
        glVertex2d(7.31,2.29);
        glVertex2d(6.63,2.77);
        glVertex2d(7.33,4.21);
    glEnd();
}

void velero(){
    vela();
    base();
    mastil();
}

void estrellas(){
    //Estrellas Pequenias
    glPointSize(3);
    glBegin(GL_POINTS);
        glColor3ub(255,255,0);
        glVertex2d(2.75,5.55);
        glVertex2d(6.8,8.65);
        glVertex2d(12.73,5.14);
        glVertex2d(4.1,5.1);
        glVertex2d(11.4,8.33);
        glVertex2d(10.44,9.77);
    glEnd();

    //Estrellas grandes
    glPointSize(6);
    glBegin(GL_POINTS);
        glColor3ub(255,255,0);
        glVertex2d(9.13,6.02);
        glVertex2d(6.1,7.1);
        glVertex2d(9.1,8.4);
        glVertex2d(13.67,7.41);
    glEnd();

    //Destellos
    glPointSize(3);
    glBegin(GL_LINES);
        glColor3ub(255,255,0);
        glVertex2d(2.75,5.55);
        glVertex2d(3.75,6.55);

        glVertex2d(6.8,8.65);
        glVertex2d(7.8,9.65);

        glVertex2d(4.1,5.1);
        glVertex2d(5.1,6.1);

        glVertex2d(11.4,8.33);
        glVertex2d(12.4,9.33);

        glVertex2d(10.44,9.77);
        glVertex2d(11.44,10.77);

        glVertex2d(9.13,6.02);
        glVertex2d(10.13,7.02);

        glVertex2d(6.1,7.1);
        glVertex2d(7.1,8.1);

        glVertex2d(9.1,8.4);
        glVertex2d(10.1,9.4);

        glVertex2d(13.67,7.41);
        glVertex2d(14.67,8.41);

    glEnd();
}

void meteorito() {
    float radiom = 0.8;
    float radioc1 = 0.25;
    float radioc2 = 0.12;
    float cx, cy;

    // Estela de fuego del meteorito 1
    glBegin(GL_POLYGON);
        glColor3ub(50, 100, 255);
        glVertex2d(8.42, 8.20);
        glVertex2d(9.02, 9.09);
        glVertex2d(8.85, 8.55);
        glVertex2d(9.57, 9.38);
        glVertex2d(9.35, 8.81);
        glVertex2d(10.66, 9.63);
        glVertex2d(9.6, 8.74);
        glVertex2d(10.44, 8.84);
        glVertex2d(9.04, 8.24);
        glVertex2d(10.12, 8.52);
        glVertex2d(8.54, 7.79);
    glEnd();

    // Estela de fuego del meteorito 2
    glBegin(GL_POLYGON);
        glColor3ub(255, 191, 0);
        glVertex2d(8.39, 7.92);
        glVertex2d(8.75, 8.50);
        glVertex2d(8.71, 8.29);
        glVertex2d(9.19, 8.77);
        glVertex2d(9.10, 8.53);
        glVertex2d(9.35, 8.55);
        glVertex2d(8.70, 8.16);
        glVertex2d(8.95, 8.13);
    glEnd();

    // Cuerpo del meteorito
    glBegin(GL_POLYGON);
    for(double i=0; i < (2 * M_PI); i += 0.4){
        cx = radiom * cos(i);
        cy = radiom * sin(i);

        //Difuminar color
        if (cy >= 0) {
            glColor3ub(87, 158, 212);
        } else {
            glColor3ub(35, 99, 148);
        }
        glVertex2d(cx + 8.0, cy + 7.5);
    }
    glEnd();

    //detalle (crater grande)
    glColor3ub(200, 200, 210);
    glBegin(GL_POLYGON);
    for(double i=0; i < (2 * M_PI); i += 0.4){
        cx = radioc1 * cos(i);
        cy = radioc1 * sin(i);
        glVertex2d(cx + 7.8, cy + 7.4);
    }
    glEnd();

    //detalle (crater pequeño 1)
    glColor3ub(200, 200, 210);
    glBegin(GL_POLYGON);
    for(double i=0; i < (2 * M_PI); i += 0.4){
        cx = radioc2 * cos(i);
        cy = radioc2 * sin(i);
        glVertex2d(cx + 7.5, cy + 7.8);
    }
    glEnd();

    //detalle (crater pequeño 2)
    glColor3ub(200, 200, 210);
    glBegin(GL_POLYGON);
    for(double i=0; i < (2 * M_PI); i += 0.4){
        cx = radioc2 * cos(i);
        cy = radioc2 * sin(i);
        glVertex2d(cx + 8.4, cy + 7.2);
    }
    glEnd();
}

void faro() {
    // Techo del faro
    float radio2 = 1.76;
    float cxx, cyy;

    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    for(double i=0; i < (2 * M_PI); i += 0.01){
        cxx = radio2 * cos(i);
        cyy = radio2 * sin(i);
        glVertex2d(cxx + 14.34, cyy + 6.31);
    }
    glEnd();

    // Luz
    glBegin(GL_POLYGON);
        glColor3ub(255, 255, 0);
        glVertex2d(12.55, 6.52);

        glColor4ub(255, 255, 0, 0);
        glVertex2d(4.32,4.59);
        glVertex2d(7.19,2.79);
    glEnd();

    //Cuerpo del Faro
    glShadeModel(GL_FLAT);
    glBegin(GL_QUAD_STRIP);
        glColor3ub(255, 255, 255); // Bloque 1 blanco
        glVertex2d(16.11, 1.11);
        glVertex2d(12.58, 1.11);
        glVertex2d(16.11, 2.41);
        glVertex2d(12.58, 2.41);

        glColor3ub(255, 0, 0);      // Bloque 2 rojo
        glVertex2d(16.11, 3.71);
        glVertex2d(12.58, 3.71);

        glColor3ub(255, 255, 255); // Bloque 3 blanco
        glVertex2d(16.11, 5.01);
        glVertex2d(12.58, 5.01);

        glColor3ub(255, 0, 0);     // Bloque 4 rojo
        glVertex2d(16.11, 6.31);
        glVertex2d(12.58, 6.31);
    glEnd();

    // Base o suelo del faro
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
        glVertex2d(16, 1.2);
        glVertex2d(12.5, 1.2);
        glVertex2d(12.0, 0);
        glVertex2d(16, 0);
    glEnd();

    //detalle (Esquina redondeada)
    float radio1 = 0.1;
    float cx, cy;

    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    for(double i=0; i < (2 * M_PI); i += 0.01){
        cx = radio1 * cos(i);
        cy = radio1 * sin(i);
        glVertex2d(cx + 12.56, cy + 1.11);
    }
    glEnd();

    // Foco
    glColor3ub(255, 255, 0);
    glBegin(GL_POLYGON);
        glVertex2d(12.59, 6.32);
        glVertex2d(12.66, 6.32);
        glVertex2d(12.66, 6.72);
        glVertex2d(12.59, 6.72);
    glEnd();
}

void criatura_marina(){
    //Cola
    glColor3ub(19, 22, 133);
    glBegin(GL_POLYGON);
        glVertex2d(7.85, 3.20);
        glVertex2d(6.37, 3.67);
        glVertex2d(7.65, 3.53);
        glVertex2d(7.48, 4.02);
        glVertex2d(8.01, 3.3);
        glVertex2d(8.49, 3.20);
    glEnd();

    //Cuerpo
    float radiox = 1.8;
    float radioy = 0.95;
    float cx, cy;

    glColor3ub(19, 22, 133);
    glBegin(GL_POLYGON);
    for(double i=0; i < (2 * M_PI); i += 0.01){
        cx = radiox * cos(i);
        cy = radioy * sin(i);
        glVertex2d(cx + 10.69, cy + 2.7);
    }
    glEnd();

    //Agua disparada
    glColor3ub(53, 209, 240);
    glBegin(GL_POLYGON);
        glVertex2d(10.41,3.70);
        glVertex2d(9.95, 4.86);
        glVertex2d(10.32, 4.18);
        glVertex2d(10.16, 5.28);
        glVertex2d(10.47, 4.07);
        glVertex2d(10.60, 4.72);
        glVertex2d(10.45, 3.82);
    glEnd();
}

void dibujar(){
    glLoadIdentity();
    gluOrtho2D(0,15,0,10);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    cielo();
    criatura_marina();
    mar();
    sol1();
    sol2();
    estrellas();

    glPushMatrix();
        glTranslated(-2.8,1.8,0);
        glScaled(0.5, 0.5, 0.5);
        velero();
    glPopMatrix();

    glPushMatrix();
        glTranslated(-3,0,0);
        velero();
    glPopMatrix();

    glPushMatrix();
        glTranslated(-7.5,-1.5,0);
        glScaled(1.3, 1.3, 1.3);
        velero();
    glPopMatrix();

    meteorito();
    faro();

    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1100,779);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Computacion Grafica - Practica de Campo 02");
    glutDisplayFunc(dibujar);
    glutMainLoop();
    return 0;
}
