#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#include "pl2.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define rtd(x)   (180*(x)/M_PI)
#define dtr(x)   (M_PI*(x)/180)

#define DEBUG 1

/* VARIÁVEIS GLOBAIS */

typedef struct {
    GLboolean doubleBuffer;
    GLint delay;
} Estado;

typedef struct {
    GLint hor, min, seg;
} Horas;

typedef struct {
    GLint numLados;
    GLfloat raio;
    GLfloat tamLado;
    Horas hora;
} Modelo;


Estado estado;
Modelo modelo;

void poligono(GLint n, GLdouble x0, GLdouble y0, GLdouble r);
void mostrador(GLdouble x0, GLdouble y0, GLdouble r);
void ponteiros(GLdouble x0, GLdouble y0, GLdouble r, GLint h, GLint m, GLint s);

/* Inicialização do ambiente OPENGL */
void Init(void) {

    struct tm *current_time;
    time_t timer = time(0);

    //delay para o timer
    estado.delay = 1000;

    modelo.tamLado = 1;
    modelo.numLados = 5;
    modelo.raio = 0.75;


    // Lê hora do Sistema
    current_time = localtime(&timer);
    modelo.hora.hor = current_time->tm_hour;
    modelo.hora.min = current_time->tm_min;
    modelo.hora.seg = current_time->tm_sec;

    glClearColor(0.3, 0.3, 0.3, 0.0);
    //
    //    glEnable(GL_POINT_SMOOTH);
    //    glEnable(GL_LINE_SMOOTH);
    //    glEnable(GL_POLYGON_SMOOTH);

}

/**************************************
 ***  callbacks de janela/desenho    ***
 **************************************/

// CALLBACK PARA REDIMENSIONAR JANELA

void Reshape(int width, int height) {
    GLint size;
    GLfloat ratio = (GLfloat) width / height;
    GLfloat ratio1 = (GLfloat) height / width;

    if (width < height)
        size = width;
    else
        size = height;

    // glViewport(botom, left, width, height)
    // define parte da janela a ser utilizada pelo OpenGL

    //glViewport(0, 0, (GLint) size, (GLint) size);
    glViewport(0, 0, width, height);


    // Matriz Projecção
    // Matriz onde se define como o mundo e apresentado na janela
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // gluOrtho2D(left,right,bottom,top); 
    // projeccao ortogonal 2D, com profundidade (Z) entre -1 e 1
    if (width < height)
        gluOrtho2D(-1, 1, -1 * ratio1, 1 * ratio1);
    else
        gluOrtho2D(-1 * ratio, 1 * ratio, -1, 1);

    // Matriz Modelview
    // Matriz onde são realizadas as tranformações dos modelos desenhados
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// ... definição das rotinas auxiliares de desenho ...

// Callback de desenho

void Draw(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    // ... chamada das rotinas auxiliares de desenho ...

    //    glBegin(GL_POLYGON);
    //    glColor3f(1.0f, 0.0f, 0.0f);
    //    glVertex2f(modelo.tamLado / 2, modelo.tamLado / 2);
    //    glColor3f(0.0f, 0.0f, 1.0f);
    //    glVertex2f(-modelo.tamLado / 2, modelo.tamLado / 2);
    //    glColor3f(0.0f, 1.0f, 0.0f);
    //    glVertex2f(-modelo.tamLado / 2, -modelo.tamLado / 2);
    //    glColor3f(1.0f, 0.0f, 1.0f);
    //    glVertex2f(modelo.tamLado / 2, -modelo.tamLado / 2);
    //    glEnd();
    //
    //    glBegin(GL_LINE_LOOP);
    //    glColor3f(1.0, 1.0, 1.0);
    //    glVertex2f(-1.0, -1.0);
    //    glVertex2f(1.0, -1.0);
    //    glVertex2f(1.0, 1.0);
    //    glVertex2f(-1.0, 1.0);
    //    glEnd();

    poligono(modelo.numLados, 0.0, 0.0, modelo.raio);
    mostrador(0.0, 0.0, modelo.raio);
    ponteiros(0.0, 0.0, modelo.raio, modelo.hora.hor, modelo.hora.min, modelo.hora.seg);

    glFlush();
    if (estado.doubleBuffer)
        glutSwapBuffers();
}

/*******************************
 ***   callbacks timer/idle   ***
 *******************************/

// Callback Idle

void Idle(void) {

    // accoes a tomar quando o glut estÃ¡ idle 

    // redesenhar o ecra 
    // glutPostRedisplay();
}

// Callback de temporizador (não colocar instruções de desenho aqui...)

void Timer(int value) {
    glutTimerFunc(estado.delay, Timer, 0);
    // ... acções do temporizador ...     
    // Lê hora do Sistema
    struct tm *current_time;
    time_t timer = time(0);
    current_time = localtime(&timer);
    modelo.hora.hor = current_time->tm_hour;
    modelo.hora.min = current_time->tm_min;
    modelo.hora.seg = current_time->tm_sec;
    // redesenhar o ecrã (invoca o callback de desenho)
    glutPostRedisplay();
}

void imprime_ajuda(void) {
    printf("\n\nDesenho de um quadrado\n");
    printf("h,H - Ajuda \n");
    printf("+   - Aumentar tamanho do Lado\n");
    printf("-   - Diminuir tamanho do Lado\n");
    printf("ESC - Sair\n");
}

/*******************************
 ***  callbacks de teclado    ***
 *******************************/

// Callback para interacção via teclado (carregar na tecla)

void Key(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // Tecla Escape
            exit(1);
            // ... acções sobre outras teclas ... 

        case 'h':
        case 'H':
            imprime_ajuda();
            break;
        case '+':
            if (modelo.raio < 1.8) {
                modelo.raio += 0.05;
                glutPostRedisplay(); // redesenhar o ecrã
            }
            break;
        case '-':
            if (modelo.raio > 0.2) {
                modelo.raio -= 0.05;
                glutPostRedisplay(); // redesenhar o ecrã
            }
            break;
        case '*':
            modelo.numLados++;
            glutPostRedisplay(); // redesenhar o ecrã
            break;
        case '_':
            if (modelo.numLados > 4) {
                modelo.numLados--;
                glutPostRedisplay(); // redesenhar o ecrã
            }
            break;

    }

    if (DEBUG)
        printf("Carregou na tecla %c\n", key);

}

// Callback para interacção via teclado (largar a tecla)

void KeyUp(unsigned char key, int x, int y) {

    if (DEBUG)
        printf("Largou a tecla %c\n", key);
}

// Callback para interacção via teclas especiais  (carregar na tecla)

void SpecialKey(int key, int x, int y) {
    // ... accoes sobre outras teclas especiais ... 
    //    GLUT_KEY_F1 ... GLUT_KEY_F12
    //    GLUT_KEY_UP
    //    GLUT_KEY_DOWN
    //    GLUT_KEY_LEFT
    //    GLUT_KEY_RIGHT
    //    GLUT_KEY_PAGE_UP
    //    GLUT_KEY_PAGE_DOWN
    //    GLUT_KEY_HOME
    //    GLUT_KEY_END
    //    GLUT_KEY_INSERT 

    switch (key) {

            // redesenhar o ecra 
            //glutPostRedisplay();
    }


    if (DEBUG)
        printf("Carregou na tecla especial %d\n", key);
}

// Callback para interacção via teclas especiais (largar a tecla)

void SpecialKeyUp(int key, int x, int y) {

    if (DEBUG)
        printf("Largou a tecla especial %d\n", key);

}

int main(int argc, char **argv) {
    estado.doubleBuffer = GL_TRUE; // colocar a GL_TRUE para ligar o Double Buffer

    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(300, 300);
    glutInitDisplayMode(((estado.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB);
    if (glutCreateWindow("Exemplo") == GL_FALSE)
        exit(1);

    Init();

    imprime_ajuda();

    // Registar callbacks do GLUT

    // callbacks de janelas/desenho
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);

    // Callbacks de teclado
    glutKeyboardFunc(Key);
    //glutKeyboardUpFunc(KeyUp);
    //glutSpecialFunc(SpecialKey);
    //glutSpecialUpFunc(SpecialKeyUp);

    // callbacks timer/idle
    glutTimerFunc(estado.delay, Timer, 0);
    //glutIdleFunc(Idle);


    // COMEÇAR...
    glutMainLoop();
    return 0;
}

void poligono(GLint n, GLdouble x0, GLdouble y0, GLdouble r) {
    double difangulo = (2 * M_PI) / n;
    double angulo = M_PI / 2;

    point centro;
    centro.x = x0;
    centro.y = y0;

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 1.0f);

    for (int i = 0; i < n; ++i) {
        point ponto = pPontoCirc(centro, r, angulo);
        glVertex2d(ponto.x, ponto.y);
        angulo += difangulo;
    }

    glEnd();
}

void mostrador(GLdouble x0, GLdouble y0, GLdouble r) {
    int numMinutos = 60;

    double difAnguloMinutos = (2 * M_PI) / 60;
    double angulo;

    point centro;
    centro.x = x0;
    centro.y = y0;

    glBegin(GL_LINES);

    //raios do ponteiro minutos:
    double rmmin = r - r * 0.10;
    double rmmax = r - r * 0.05;
    //raios do ponteiro minutos:
    double rhmin = r - r * 0.20;
    double rhmax = r - r * 0.05;

    angulo = M_PI / 2;
    for (int i = 0; i < numMinutos; ++i) {

        //Marcas de Horas:
        if (i % 5 == 0 && i % 15 != 0) {
            point pmin = pPontoCirc(centro, rhmin, angulo);
            point pmax = pPontoCirc(centro, rhmax, angulo);
            glColor3f(0.0f, 0.5f, 0.5f);

            glVertex2d(pmin.x, pmin.y);
            glVertex2d(pmax.x, pmax.y);
        }//Marcas de Horas 3, 6, 9, 12
        else if (i % 15 == 0) {
            point pmin = pPontoCirc(centro, rhmin, angulo);
            point pmax = pPontoCirc(centro, rhmax, angulo);
            glColor3f(0.0f, 0.5f, 1.0f);

            glVertex2d(pmin.x, pmin.y);
            glVertex2d(pmax.x, pmax.y);
        }//Marcas de minutos
        else {
            point pmin = pPontoCirc(centro, rmmin, angulo);
            point pmax = pPontoCirc(centro, rmmax, angulo);
            glColor3f(1.0f, 0.0f, 0.0f);

            glVertex2d(pmin.x, pmin.y);
            glVertex2d(pmax.x, pmax.y);
        }
        angulo += difAnguloMinutos;
    }
    glEnd();

}

void ponteiros(GLdouble x0, GLdouble y0, GLdouble r, GLint h, GLint m, GLint s) {
    double angHora = (-(2 * M_PI) / 12) * (h + (m / 60.0) + (s / 3600) ) + (M_PI/2);
    double angMinuto = (-(2 * M_PI) / 60) * (m + (s / 60.0)) + (M_PI/2);
    double angSegundo = (-(2 * M_PI) / 60) * s + (M_PI/2);

    point centro;
    centro.x = x0;
    centro.y = y0;

    glBegin(GL_LINES);

    //raios dos ponteiros
    double rh = r - r * 0.40;
    double rm = r - r * 0.25;
    double rs = r - r * 0.10;

    point pmax = pPontoCirc(centro, rh, angHora);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2d(centro.x, centro.y);
    glVertex2d(pmax.x, pmax.y);

    pmax = pPontoCirc(centro, rm, angMinuto);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2d(centro.x, centro.y);
    glVertex2d(pmax.x, pmax.y);

    pmax = pPontoCirc(centro, rs, angSegundo);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2d(centro.x, centro.y);
    glVertex2d(pmax.x, pmax.y);


    glEnd();
}

