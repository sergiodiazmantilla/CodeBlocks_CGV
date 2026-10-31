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

    //glPointSize(5);
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

    //glPointSize(5);
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
        glVertex2d(5.5,7.4);
        glVertex2d(9.1,8.4);
        glVertex2d(13.67,7.41);
    glEnd();

    //Destello

}

// NUEVA FUNCIÓN: Puntas o tentáculos saliendo del agua
void picos(){
    // Tentáculo izquierdo (forma de triángulo inclinado hacia arriba)
    glBegin(GL_POLYGON);
        glColor3ub(20, 170, 130); // Mismo color del cuerpo del monstruo
        glVertex2d(2.1, 3.2); // Base izquierda en el agua
        glVertex2d(2.6, 3.2); // Base derecha en el agua
        glVertex2d(2.3, 5.2); // Punta superior saliendo al cielo
    glEnd();

    // Tentáculo derecho
    glBegin(GL_POLYGON);
        glColor3ub(20, 170, 130);
        glVertex2d(4.6, 3.2);
        glVertex2d(5.1, 3.2);
        glVertex2d(5.0, 4.9);
    glEnd();
}

// 1. Tentáculo con forma de onda / gancho fluido
void tentaculo_onda() {
    glBegin(GL_QUAD_STRIP);
    for(double t = 0; t <= 3.2; t += 0.03) {
        // Se hace más delgado conforme sube (llega a la punta)
        float ancho = 0.3 * (1.0 - t / 3.5);
        if (ancho < 0.04) ancho = 0.04;

        // Curva suave usando seno para simular la ondulación
        float cx = sin(t * 1.8) * 0.5;
        float cy = t * 1.3; // Altura que va creciendo desde la base

        // Exterior
        glColor3ub(20, 170, 130);
        glVertex2d(cx - ancho, cy + 3.2); // Ubicado justo sobre la línea del agua (3.2)
        // Interior (sombra)
        glColor3ub(10, 70, 94);
        glVertex2d(cx + ancho, cy + 3.2);
    }
    glEnd();
}

// 2. Tentáculo con rulo / espiral (como el de tu dibujo de la derecha)
void tentaculo_espiral() {
    glBegin(GL_QUAD_STRIP);
    for(double t = 0; t <= 5.0; t += 0.03) {
        float ancho = 0.35 * (1.0 - t / 5.5);
        if (ancho < 0.03) ancho = 0.03;

        // Combinación de seno y coseno para dar la vuelta del rulo
        float cx = cos(t) * (5.0 - t) * 0.22;
        float cy = sin(t) * (5.0 - t) * 0.22 + (t * 0.7);

        // Exterior
        glColor3ub(20, 170, 130);
        glVertex2d(cx, cy + 3.2);
        // Interior
        glColor3ub(10, 70, 94);
        glVertex2d(cx + ancho, cy + 3.2);
    }
    glEnd();
}

void monstruo(){
    float r1 = 0.1, r2= 0.2;
    float radio_externo = 2.0;
    float radio_interno = 0.7;
    float cx, cy;

    //Lineas de sumersión en el agua
    glLineWidth(5);
    glBegin(GL_LINES);
        glColor3ub(252,41,7);
        glVertex2d(1.51,2.48);
        glVertex2d(3.00,2.48);
        glVertex2d(5.71,2.48);
        glVertex2d(4.15,2.48);
    glEnd();

    picos();

    //Cuerpo de la criatura - Base
    glBegin(GL_QUAD_STRIP);
        for(double i = 0; i <= M_PI; i += 0.01){
            // Exterior
            glColor3ub(20, 170, 130);
            cx = radio_externo * cos(i);
            cy = radio_externo * sin(i);
            glVertex2d(cx + 3.61, cy + 2.48);
            //Interior
            glColor3ub(10, 70, 94);
            cx = radio_interno * cos(i);
            cy = radio_interno * sin(i);
            glVertex2d(cx + 3.61, cy + 2.48);
        }
    glEnd();

    //Ventosas
    glColor3ub(10, 70, 94);
    glBegin(GL_POLYGON);
        for(double i=0; i< (2 * M_PI); i += 0.001){
            cx = r1 * cos(i);
            cy = r1 * sin(i);
            glVertex2d(cx+2.35,cy+2.65);
        }
    glEnd();
    glColor3ub(10, 70, 94);
    glBegin(GL_POLYGON);
        for(double i=0; i< (2 * M_PI); i += 0.001){
            cx = r2 * cos(i);
            cy = r2 * sin(i);
            glVertex2d(cx+2.3,cy+3.9);
        }
    glEnd();
    glColor3ub(10, 70, 94);
    glBegin(GL_POLYGON);
        for(double i=0; i< (2 * M_PI); i += 0.001){
            cx = r1 * cos(i);
            cy = r1 * sin(i);
            glVertex2d(cx+3.91,cy+3.71);
        }
    glEnd();
    glColor3ub(10, 70, 94);
    glBegin(GL_POLYGON);
        for(double i=0; i< (2 * M_PI); i += 0.001){
            cx = r2 * cos(i);
            cy = r2 * sin(i);
            glVertex2d(cx+5,cy+3);
        }
    glEnd();
}

void dibujar(){
    glLoadIdentity();
    gluOrtho2D(0,15,0,10);
    glClear(GL_COLOR_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    cielo();
    mar();
    sol1();
    sol2();
    estrellas();

    glPushMatrix();
        glTranslated(-1,0,0);
        velero();
    glPopMatrix();

    glPushMatrix();
        monstruo();
    glPopMatrix();

    glPushMatrix();
        glTranslated(7,0,0);
        glScaled(1.2,1.1,1);
        monstruo();
    glPopMatrix();

    glPushMatrix();
        glTranslated(4,-2.9,0);
        glScaled(1.2,1.1,1);
        monstruo();
    glPopMatrix();


    // --- TENTÁCULOS CURVOS (Basados en tus dibujos) ---
    // 1. Tentáculo en onda a la izquierda
    glPushMatrix();
        glTranslated(1.8, 0, 0);
        tentaculo_onda();
    glPopMatrix();

    // 2. Tentáculo con espiral a la derecha
    glPushMatrix();
        glTranslated(12.5, 0, 0);
        tentaculo_espiral();
    glPopMatrix();

    // 3. Tentáculo en onda inferior (saliendo del agua al frente)
    glPushMatrix();
        glTranslated(3.2, -0.5, 0);
        glScaled(0.8, 0.8, 1);
        tentaculo_onda();
    glPopMatrix();

    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1100,779);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Computacion Grafica");
    glutDisplayFunc(dibujar);
    glutMainLoop();
    return 0;
}
