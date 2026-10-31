#include <GL/glut.h>

//Observador
float camaraX = -20;
float camaraY = 10;
float camaraZ = 20;

void iniciarVentana(int w, int h){
    glViewport(0,0,w,h); //punto de vista
    glMatrixMode(GL_PROJECTION); // cambiar la forma en la que vemos la profundida
    glLoadIdentity();
    float aspect3d = ((float)w / (float)h);
    gluPerspective(60,aspect3d,1,2000); // distancia a la que esta ubicado el enfoque del observador
}

void inicializarLuces(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
}

void dibujar(){
    inicializarLuces();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camaraX, camaraY, camaraZ, 0,0,0,0,1,0);

    //Cubo Solido
    glPushMatrix();
        glutSolidCube(4);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1420, 880);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Computacion Grafica 3D");
    glutReshapeFunc(iniciarVentana);
    glutDisplayFunc(dibujar);
    glutMainLoop();
    return 0;
}
