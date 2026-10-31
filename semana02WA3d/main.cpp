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
        glColor3ub(255,0,0);
        glTranslated(15,0,0);
        glutSolidCube(4);
    glPopMatrix();

    //Cubo Wire
    glPushMatrix();
        glTranslated(10,0,0);
        glutWireCube(4);
    glPopMatrix();

    //Cono Solido
    glPushMatrix();
        glColor3ub(255,255,0);
        glTranslated(0,0,-20);
        glRotated(-90,1,0,0);
        glutSolidCone(5,6,50,50);
    glPopMatrix();

    //Cono Wire
    glPushMatrix();
        glTranslated(0,0,-10);
        glRotated(-90,1,0,0);
        glutWireCone(5,6,50,50); //base, altura, cantidad de lineas verticales, horizontales
    glPopMatrix();

    //Esfera Solida
    glPushMatrix();
        glColor3ub(0,255,0);
        glTranslated(-20,0,0);
        glutSolidSphere(4,50,50);
    glPopMatrix();

    //Esfera Wire
    glPushMatrix();
        glColor3ub(0,255,0);
        glTranslated(-15,0,0);
        glutWireSphere(4,50,50);
    glPopMatrix();

    //Tetera solida
    glPushMatrix();
        glColor3ub(228,0,247);
        glTranslated(0,10,5);
        glutSolidTeapot(3);
    glPopMatrix();

    //Tetera Wire
    glPushMatrix();
        glTranslated(0,10,0);
        glutWireTeapot(3);
    glPopMatrix();

    //Torus solido
    glPushMatrix();
        glColor3ub(250,180,0);
        glTranslated(0,-15,0);
        glutSolidTorus(2,4,50,50);
    glPopMatrix();

    //Torus Wile
    glPushMatrix();
        glTranslated(0,-15,-5);
        glutWireTorus(2,4,50,50);
    glPopMatrix();

    //Cilindro
    glPushMatrix();
        glColor3ub(0,200,200);
        glTranslated(0,0,15);
        gluCylinder(gluNewQuadric(),3,3,5,50,50);
    glPopMatrix();

    //disco
    glPushMatrix();
        glColor3ub(0,200,200);
        //glTranslated(0,0,15);
        gluDisk(gluNewQuadric(),1,4,50,50);
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
