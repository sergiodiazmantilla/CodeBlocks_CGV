#include <GL/glut.h>
#include <math.h>

//CIRCULO VACIO
void dibujar(){
    glLoadIdentity();
    gluOrtho2D(0, 20, 0, 20);
    glClear(GL_COLOR_BUFFER_BIT);

    float radio = 5;
    float cx, cy;

    glColor3ub(255,0,0);
    glBegin(GL_POINTS);
        for(double i = 0; i < 360; i += 0.001){
            cx = 10+(radio * cos(i));
            cy = 10+(radio * sin(i));
            glVertex2f(cx, cy);
        }
    glEnd();

    glFlush();
}

//CIRCULO RELLENO
void dibujar2(){
    glLoadIdentity();
    gluOrtho2D(0, 20, 0, 20);
    glClear(GL_COLOR_BUFFER_BIT);

    float radio = 5;
    float cx, cy;

    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
        for(double i = 0; i < 360; i += 0.001){
            cx = 10+(radio * cos(i));
            cy = 10+(radio * sin(i));
            glVertex2f(cx, cy);
        }
    glEnd();

    glFlush();
}

//MAIN
int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Ventana Prueba");
    glutDisplayFunc(dibujar2);
    glutMainLoop();
    return 0;
}
