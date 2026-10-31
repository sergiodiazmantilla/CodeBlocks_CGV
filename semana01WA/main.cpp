#include <GL/glut.h>

void dibujar(){
    glLoadIdentity();
    gluOrtho2D(0,10,0,10);
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    //PUNTO
    glPointSize(10); // tamanio del punto
    glBegin(GL_POINTS);
        glColor3ub(255,137,4);
        glVertex2d(2,2);
    glEnd();

    //LINEA
    glLineWidth(5); //ancho de la linea / Afecta a todo
    glBegin(GL_LINES);
        glColor3ub(255,255,0);
        glVertex2d(3,7);
        glVertex2d(6,6);

        //Las lineas que se creen aqui seran gruesas
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
        glColor3ub(0,255,0);
        glVertex2d(3,3);
        glVertex2d(6,4);

        //Las lineas que se creen aqui seran delgadas
    glEnd();

    //LINEAS UNIDAS POR PUNTOS
    glBegin(GL_LINE_STRIP);
        glColor3ub(255,255,0);
        glVertex2d(3,7);
        glVertex2d(6,6);
        glVertex2d(3,3);
        glVertex2d(6,4);
    glEnd();


    //POLIGONO
    glBegin(GL_POLYGON);
        glColor3ub(255,255,0);
        glVertex2d(3,7);
        glColor3ub(0,255,0);
        glVertex2d(6,6);
        glColor3ub(255,0,0);
        glVertex2d(3,3);
    glEnd();

    //Cuadrilatero
    glBegin(GL_QUADS);
        glColor3ub(255,0,0);
        glVertex2d(2,8);
        glVertex2d(4,8);
        glVertex2d(4,6);
        glVertex2d(2,6);

        glVertex2d(6,8);
        glVertex2d(8,8);
        glVertex2d(8,6);
        glVertex2d(6,6);
    glEnd();


    //Cuadrilateros unidos (+2 puntos)
    glBegin(GL_QUAD_STRIP);
    glEnd();
    */

    glFlush();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Computacion Grafica");
    glutDisplayFunc(dibujar);
    glutMainLoop();
    return 0;
}
