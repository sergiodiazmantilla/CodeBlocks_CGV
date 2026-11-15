#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

const float PI = 3.14159265f;
float anguloVista = 35.0f, elevacionVista = 51.0f, distanciaVista = 77.0f;
bool arrastrando = false;
int ultimoMouseX = 0, ultimoMouseY = 0;
GLuint escena;

float azar(unsigned int &s) {
    s = s * 1664525u + 1013904223u;
    return (s & 0x00FFFFFFu) / 16777215.0f;
}

void caja(float x, float y, float z, float sx, float sy, float sz,
          float r, float g, float b) {
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y + sy * 0.5f, z);
    glScalef(sx, sy, sz);
    glutSolidCube(1);
    glPopMatrix();
}

void colorBasura(unsigned int &s, float &r, float &g, float &b) {
    float t = azar(s), luz = 0.65f + azar(s) * 0.40f;
    if (t < 0.25f) { r = 0.48f; g = 0.35f; b = 0.23f; }
    else if (t < 0.50f) { r = 0.55f; g = 0.29f; b = 0.14f; }
    else if (t < 0.75f) { r = 0.57f; g = 0.49f; b = 0.32f; }
    else if (t < 0.88f) { r = 0.32f; g = 0.33f; b = 0.29f; }
    else { r = 0.68f; g = 0.61f; b = 0.45f; }
    r *= luz; g *= luz; b *= luz;
}

float centroCamino(float x) {
    const float px[] = {-30, -24, -18, -12, -7, -2, 4, 10, 16, 22, 30};
    const float pz[] = {-12, -12.9f, -12.5f, -10, -7.2f, -6.7f,
                        -8, -10.4f, -12.7f, -12, -10};
    for (int i = 0; i < 10; ++i) {
        if (x <= px[i + 1]) {
            float t = (x - px[i]) / (px[i + 1] - px[i]);
            return pz[i] + t * (pz[i + 1] - pz[i]);
        }
    }
    return pz[10];
}

void suelo() {
    unsigned int s = 12u;
    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
    for (int x = -30; x < 30; ++x)
        for (int z = -30; z < 30; ++z) {
            float v = azar(s) * 0.025f;
            if (std::fabs(z + 0.5f - centroCamino(x + 0.5f)) < 1.4f)
                glColor3f(0.46f + v, 0.35f + v, 0.22f + v);
            else
                glColor3f(0.57f + v, 0.44f + v, 0.28f + v);
            glVertex3f(x, 0, z);
            glVertex3f(x, 0, z + 1);
            glVertex3f(x + 1, 0, z + 1);
            glVertex3f(x + 1, 0, z);
        }
    glEnd();
}

void monticulo(float cx, float cz, float radio, float alto, unsigned int s) {
    const float paso = 1.2f;
    int limite = static_cast<int>(std::ceil(radio / paso));
    for (int ix = -limite; ix <= limite; ++ix)
        for (int iz = -limite; iz <= limite; ++iz) {
            float localX = ix * paso;
            float localZ = iz * paso;
            float x = cx + localX;
            float z = cz + localZ;
            float d = std::sqrt(localX * localX + localZ * localZ);
            if (d > radio) continue;
            float perfil = std::pow(1.0f - d / radio, 0.75f);
            float h = alto * perfil + 0.12f + (azar(s) - 0.5f) * 0.25f;
            if (h < 0.18f) h = 0.18f;
            float r, g, b;
            colorBasura(s, r, g, b);
            caja(x, 0, z, paso, h, paso, r, g, b);
            if (azar(s) < 0.45f) {
                float tam = 0.80f + azar(s) * 0.45f;
                colorBasura(s, r, g, b);
                caja(x, h - 0.04f, z, tam, 0.25f + azar(s) * 0.40f,
                     tam, r, g, b);
            }
        }
}

void torre(float cx, float cz, int pisos, float ancho, unsigned int s) {
    float lado = ancho / 6.0f;
    for (int nivel = 0; nivel < pisos; ++nivel)
        for (int ix = 0; ix < 6; ++ix)
            for (int iz = 0; iz < 6; ++iz) {
                float x = cx + (ix - 2.5f) * lado;
                float z = cz + (iz - 2.5f) * lado;
                float y = nivel * 0.83f;
                float r, g, b;
                colorBasura(s, r, g, b);
                caja(x, y, z, lado, 0.83f, lado, r, g, b);
            }
    for (int i = 0; i < 20; ++i) {
        float x = cx + (azar(s) - 0.5f) * ancho;
        float z = cz + (azar(s) - 0.5f) * ancho;
        float r, g, b;
        colorBasura(s, r, g, b);
        caja(x, pisos * 0.83f, z, 0.45f + azar(s) * 0.4f,
             0.20f + azar(s) * 0.45f, 0.45f + azar(s) * 0.4f, r, g, b);
    }
}

void restos() {
    unsigned int s = 319u;
    for (int i = 0; i < 120; ++i) {
        float x = (azar(s) - 0.5f) * 58.0f;
        float z = (azar(s) - 0.5f) * 58.0f;
        if (std::fabs(z - centroCamino(x)) < 1.6f) continue;
        float r, g, b, tam = 0.40f + azar(s) * 0.35f;
        colorBasura(s, r, g, b);
        caja(x, 0.01f, z, tam, tam * 0.45f, tam * 0.8f, r, g, b);
    }
}

void crearEscena() {
    escena = glGenLists(1);
    glNewList(escena, GL_COMPILE);
    suelo();
    restos();
    monticulo(-23, 18, 7, 2.8f, 11u);
    monticulo(-19, -4, 8, 3.8f, 21u);
    monticulo(-5, 6, 10, 4.2f, 31u);
    monticulo(10, 16, 7, 2.8f, 11u);
    monticulo(17, -3, 9, 4.6f, 51u);
    monticulo(2, -22, 7, 2.8f, 11u);
    torre(-20, -17, 10, 6.5f, 101u);
    torre(-5, -13, 17, 8.0f, 201u);
    torre(11, -15, 12, 7.0f, 301u);
    torre(-25, 4, 7, 5.4f, 401u);
    torre(21, 15, 9, 6.5f, 501u);
    glEndList();
}

void redimensionar(int ancho, int alto) {
    if (alto < 1) alto = 1;
    glViewport(0, 0, ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(58.0, static_cast<double>(ancho) / alto, 1.0, 180.0);
    glMatrixMode(GL_MODELVIEW);
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

        // Punto separador ( )
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

void dibujar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    float a = anguloVista * PI / 180.0f;
    float e = elevacionVista * PI / 180.0f;
    float horizontal = std::cos(e) * distanciaVista;
    gluLookAt(std::sin(a) * horizontal, 1.5f + std::sin(e) * distanciaVista,
              std::cos(a) * horizontal, 0, 1.5, 0, 0, 1, 0);
    GLfloat luz[] = {-0.6f, 1.0f, 0.4f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, luz);
    glCallList(escena);

    glPushMatrix();
        glTranslated(5,0,7);
        glScaled(0.3,0.3,0.3);
        walle();
    glPopMatrix();

    glPushMatrix();
        glTranslated(20,20,-20);
        glScaled(8,8,8);
        glRotated(-90,1,0,0);
        glRotated(-90,0,0,1);
        dibujarNave();
    glPopMatrix();


    glutSwapBuffers();
}

void flechas(int tecla, int, int) {
    if (tecla == GLUT_KEY_LEFT) anguloVista -= 5.0f;
    if (tecla == GLUT_KEY_RIGHT) anguloVista += 5.0f;
    if (tecla == GLUT_KEY_UP && elevacionVista < 85.0f) elevacionVista += 3.0f;
    if (tecla == GLUT_KEY_DOWN && elevacionVista > 8.0f) elevacionVista -= 3.0f;
    glutPostRedisplay();
}

void raton(int boton, int estado, int x, int y) {
    if (boton == GLUT_LEFT_BUTTON) {
        arrastrando = estado == GLUT_DOWN;
        ultimoMouseX = x;
        ultimoMouseY = y;
    }
    if (estado == GLUT_DOWN && boton == 3 && distanciaVista > 30.0f)
        distanciaVista -= 4.0f;
    if (estado == GLUT_DOWN && boton == 4 && distanciaVista < 120.0f)
        distanciaVista += 4.0f;
    glutPostRedisplay();
}

void moverRaton(int x, int y) {
    if (!arrastrando) return;
    anguloVista += (x - ultimoMouseX) * 0.4f;
    elevacionVista += (ultimoMouseY - y) * 0.4f;
    if (elevacionVista < 8.0f) elevacionVista = 8.0f;
    if (elevacionVista > 85.0f) elevacionVista = 85.0f;
    ultimoMouseX = x;
    ultimoMouseY = y;
    glutPostRedisplay();
}

void teclado(unsigned char tecla, int, int) {
    if (tecla == 27 || tecla == 'q' || tecla == 'Q') std::exit(0);
    if ((tecla == '+' || tecla == '=') && distanciaVista > 30.0f) distanciaVista -= 3.0f;
    if (tecla == '-' && distanciaVista < 120.0f) distanciaVista += 3.0f;
    if (tecla == 'r' || tecla == 'R') {
        anguloVista = 35.0f;
        elevacionVista = 51.0f;
        distanciaVista = 77.0f;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1100, 720);
    glutCreateWindow("T1 - Basurero inspirado en WALL-E");
    glClearColor(0.69f, 0.56f, 0.38f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    GLfloat ambiente[] = {0.54f, 0.46f, 0.34f, 1.0f};
    GLfloat difusa[] = {0.88f, 0.76f, 0.57f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
    crearEscena();
    glutDisplayFunc(dibujar);
    glutReshapeFunc(redimensionar);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(flechas);
    glutMouseFunc(raton);
    glutMotionFunc(moverRaton);
    glutMainLoop();
    return 0;
}


