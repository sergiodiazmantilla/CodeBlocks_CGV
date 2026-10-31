#include <GL/glut.h>

void dibujar(){
    glLoadIdentity();
    gluOrtho2D(0,11,0,11);
    glClear(GL_COLOR_BUFFER_BIT);

    //Poligono Principal - Base
    glBegin(GL_POLYGON);
        glColor3ub(245, 235, 210);
        glVertex2d(2,6);
        glVertex2d(2,2);
        glVertex2d(6,2);
        glVertex2d(6,6);
    glEnd();

    //Poligono Chimenea
    glBegin(GL_POLYGON);
        glColor3ub(203, 65, 84);
        glVertex2d(2.5,8);
        glVertex2d(3.5,8);
        glVertex2d(3.5,6);
        glVertex2d(2.5,6);
    glEnd();

    //Poligono Superior - Techo
    glBegin(GL_POLYGON);
        glColor3ub(178, 34, 34);
        glVertex2d(2,6);
        glVertex2d(4,8);
        glVertex2d(6,6);
    glEnd();

    //Recta que separa la base de techo
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3ub(125, 68, 10);
        glVertex2d(2,6);
        glVertex2d(6,6);
    glEnd();

    //Poligono Puerta
    glBegin(GL_POLYGON);
        glColor3ub(180, 115, 60);
        glVertex2d(3,2);
        glVertex2d(3,4);
        glVertex2d(4,4);
        glVertex2d(4,2);
    glEnd();

    //Ventana
    glBegin(GL_POLYGON);
        glColor3ub(130, 150, 230);
        glVertex2d(4.3,5.7);
        glVertex2d(5.7,5.7);
        glVertex2d(5.7,4.3);
        glVertex2d(4.3,4.3);
    glEnd();

    //Rectas que separan la ventana
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3ub(125, 68, 10);
        glVertex2d(5,5.7);
        glVertex2d(5,4.3);
    glEnd();

    //Poligonos Humos
    glBegin(GL_QUADS);
        //Humo nivel 2
        glColor3ub(149, 166, 164);
        glVertex2d(2.2,8.9);
        glVertex2d(2.8,8.9);
        glVertex2d(2.8,8.5);
        glVertex2d(2.2,8.5);
        //Humo nivel 3
        glColor3ub(170, 180, 180);
        glVertex2d(1,9.9);
        glVertex2d(2.3,9.9);
        glVertex2d(2.3,9.2);
        glVertex2d(1,9.2);
    glEnd();

    //Poligonos Arbol
    glBegin(GL_QUADS);
        //Tronco
        glColor3ub(125, 68, 10);
        glVertex2d(8,4);
        glVertex2d(9,4);
        glVertex2d(9,2);
        glVertex2d(8,2);
        //Copa nivel 1
        glColor3ub(60, 222, 64);
        glVertex2d(7,5);
        glVertex2d(10,5);
        glVertex2d(10,4);
        glVertex2d(7,4);
        //Copa nivel 2
        glColor3ub(74, 232, 78);
        glVertex2d(7.5,6);
        glVertex2d(9.5,6);
        glVertex2d(9.5,5);
        glVertex2d(7.5,5);
        //Copa nivel 3
        glColor3ub(89, 240, 93);
        glVertex2d(8,7);
        glVertex2d(9,7);
        glVertex2d(9,6);
        glVertex2d(8,6);
    glEnd();

    //Punto Pequenio
    glPointSize(5);
    glBegin(GL_POINTS);
        //Manijas para la ventana
        glColor3ub(125, 68, 10);
        glVertex2d(4.8,5);
        glVertex2d(5.2,5);
        //Frutos
        glColor3ub(255,0,0);
        glVertex2d(7.66,4.46);
        glVertex2d(9,5.62);
    glEnd();

    //Punto Grande
    glPointSize(12);
    glBegin(GL_POINTS);
        //Manija para la Puerta
        glColor3ub(125, 68, 10);
        glVertex2d(3.8,3);
        //Primer Humo
        glColor3ub(126, 148, 146);
        glVertex2d(3,8.2);
        //Frutos
        glColor3ub(255,0,0);
        glVertex2d(9.69,4.76);
        glVertex2d(7.97,5.8);
        glVertex2d(8.39,6.79);
        glVertex2d(8.8,4.91);
    glEnd();

    //Poligono Suelo/Pasto
    glBegin(GL_POLYGON);
        glColor3ub(76, 175, 80);
        glVertex2d(0,2);
        glVertex2d(11,2);
        glVertex2d(11,0);
        glVertex2d(0,0);
    glEnd();

    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Computacion Grafica - Practica de Campo 01");
    glutDisplayFunc(dibujar);
    glutMainLoop();
    return 0;
}
