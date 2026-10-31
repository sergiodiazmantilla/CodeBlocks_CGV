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
        glTranslated(-3,0,0);
        velero();
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
