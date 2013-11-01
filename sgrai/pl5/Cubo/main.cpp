#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

#define DEBUG 1
#define LADO_MAXIMO     2
#define LADO_MINIMO     0.3
#define DELTA_LADO      0.1


/* VARIAVEIS GLOBAIS */

typedef struct {
  GLboolean   doubleBuffer;
  GLint       delayMovimento;
  GLboolean   debug;
  GLboolean    movimentoTranslacao;      // se os cubinhos se movem
  GLboolean   movimentoRotacao;         // se o cubo grande roda;
}Estado;


typedef struct {
  GLfloat   theta[3];     // 0-RotaÃ§Ã£o em X; 1-RotaÃ§Ã£o em Y; 2-RotaÃ§Ã£o em Z
  
  GLint     eixoRodar;    // eixo que estÃ¡ a rodar (mudar com o rato)
  GLfloat   ladoCubo;     // comprimento do lado do cubo
  GLfloat   deltaRotacao; // incremento a fazer ao angulo quando roda
  GLboolean  sentidoTranslacao; //sentido da translaÃ§Ã£o dos cubos pequenos
  GLfloat    translacaoCubo; //
  GLfloat   deltaTranslacao; // incremento a fazer na translacao
  GLboolean sentidoRotacao;  //sentido da rotaÃ§Ã£o dos cubos pequenos
  GLfloat   thetaCubo;     // RotaÃ§Ã£o dos cubinhos
}Modelo;

Estado estado;
Modelo modelo;


/* InicializaÃ§Ã£o do ambiente OPENGL */
void inicia_modelo()
{
  estado.delayMovimento=50;
  estado.movimentoTranslacao=GL_FALSE;
  estado.movimentoRotacao=GL_FALSE;

  modelo.theta[0]=0;
  modelo.theta[1]=0;
  modelo.theta[2]=0;
  modelo.eixoRodar=-1;  // eixo de X;
  modelo.ladoCubo=1;
  modelo.translacaoCubo = 4;
  modelo.sentidoTranslacao = false;
}

void Init(void)
{
  inicia_modelo();
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
  glPolygonMode(GL_BACK,GL_LINE);
  glEnable(GL_DEPTH_TEST);

}

/**************************************
***  callbacks de janela/desenho    ***
**************************************/

/* CALLBACK PARA REDIMENSIONAR JANELA */
void Reshape(int width, int height)
{
  glViewport(0, 0, (GLint) width, (GLint) height);  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (width < height)
     glOrtho(-5, 5, -5*(GLdouble)height/width, 5*(GLdouble)height/width,-10,10);
  else
     glOrtho(-5*(GLdouble)width/height, 5*(GLdouble)width/height,-5, 5, -10,10);

   
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}


/* ... definicao das rotinas auxiliares de desenho ... */

void desenhaPoligono(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[])
{

  /* draw a polygon via list of vertices */

  glBegin(GL_POLYGON);
    glColor3fv(cor);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glVertex3fv(d);
  glEnd();
}


void cubo()
{
 GLfloat vertices[][3] = {{-0.5,-0.5,-0.5}, 
                          {0.5,-0.5,-0.5}, 
                          {0.5,0.5,-0.5}, 
                          {-0.5,0.5,-0.5},
                          {-0.5,-0.5,0.5}, 
                          {0.5,-0.5,0.5}, 
                          {0.5,0.5,0.5}, 
                          {-0.5,0.5,0.5}};

  GLfloat cores[][3] = {{0.0,1.0,1.0},
                        {1.0,0.0,0.0},
                        {1.0,1.0,0.0}, 
                        {0.0,1.0,0.0}, 
                        {1.0,0.0,1.0}, 
                        {0.0,0.0,1.0}, 
                        {1.0,1.0,1.0}};

  desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[0]);
  desenhaPoligono(vertices[4],vertices[5],vertices[6],vertices[7],cores[1]);
  desenhaPoligono(vertices[1],vertices[2],vertices[6],vertices[5],cores[2]);
  desenhaPoligono(vertices[2],vertices[3],vertices[7],vertices[6],cores[3]);
  desenhaPoligono(vertices[4],vertices[0],vertices[1],vertices[5],cores[4]);
  desenhaPoligono(vertices[7],vertices[3],vertices[0],vertices[4],cores[5]);
}

void cubo1(){
    GLfloat vertices[][3] = {{-0.5,-0.5,-0.5}, 
                          {0.5,-0.5,-0.5}, 
                          {0.5,0.5,-0.5}, 
                          {-0.5,0.5,-0.5}};

  GLfloat cores[][3] = {{0.0,1.0,1.0},
                        {1.0,0.0,0.0},
                        {1.0,1.0,0.0}, 
                        {0.0,1.0,0.0}, 
                        {1.0,0.0,1.0}, 
                        {0.0,0.0,1.0}, 
                        {1.0,1.0,1.0}};
  
  desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[0]);
  for(int i = 0; i < 3; i++){
      glRotatef(90.0,0,1,0);
      desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[0]);
  }
  glRotatef(90.0,1,0,0);
  desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[0]);
  glRotatef(180.0,1,0,0);
  desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[0]);
}

void eixos(){
     GLfloat cores[][3] = {{0.0,1.0,1.0},
                        {1.0,0.0,0.0},
                        {1.0,1.0,0.0}};
     
     //Desenha eixo dos Xs
     glBegin(GL_LINES);
        glColor3fv(cores[0]);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(4.0,0.0,0.0);
     glEnd();
     
     //Desenha eixo dos Ys
     glBegin(GL_LINES);
        glColor3fv(cores[1]);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,4.0,0.0);
     glEnd();
     
     //Desenha eixo dos Zs
     glBegin(GL_LINES);
        glColor3fv(cores[2]);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,4.0);
     glEnd();
}


/* Callback de desenho */
void Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/* ... chamada das rotinas auxiliares de desenho ... */

  glPushMatrix();
    glRotatef(modelo.theta[0],1,0,0);
    glRotatef(modelo.theta[1],0,1,0);
    glRotatef(modelo.theta[2],0,0,1);
    glScalef(modelo.ladoCubo,modelo.ladoCubo,modelo.ladoCubo);
    cubo1();
    eixos();
    glPushMatrix();
        glTranslatef(modelo.translacaoCubo,0.0,0.0);
        glScalef(0.2,0.2,0.2);
        glRotatef(modelo.deltaRotacao,1,0,0);
        cubo();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,modelo.translacaoCubo,0.0);
        glScalef(0.2,0.2,0.2);
        glRotatef(modelo.deltaRotacao,0,1,0);
        cubo();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,0.0,modelo.translacaoCubo);
        glScalef(0.2,0.2,0.2);
        glRotatef(modelo.deltaRotacao,0,0,1);
        cubo();
    glPopMatrix();
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(-4.0,-4.0,0);
    glRotatef(modelo.theta[0],1,0,0);
    glRotatef(modelo.theta[1],0,1,0);
    glRotatef(modelo.theta[2],0,0,1);
    glScalef(0.2,0.2,0.2);
    eixos();
  glPopMatrix();        


  if (estado.doubleBuffer)
    glutSwapBuffers();
  else
    glFlush();
  
}

/*******************************
***   callbacks timer   ***
*******************************/
/* Callback de temporizador */
void Timer(int value)
{

  glutTimerFunc(estado.delayMovimento, Timer, 0);
  /* ... accoes do temporizador nÃ£o colocar aqui transformaÃ§Ãµes, alterar
     somente os valores das variÃ¡veis ... */
  
  // alterar o modelo.theta[] usando a variÃ¡vel modelo.eixoRodar como indice
  if(modelo.eixoRodar >= 0){
        modelo.theta[modelo.eixoRodar]++;
  }
  
  if(modelo.sentidoTranslacao){
      if(modelo.translacaoCubo >= 4){
          modelo.sentidoTranslacao = false;
          modelo.sentidoRotacao = false;
      }else{
          modelo.translacaoCubo += 0.1;
      }
  }else{
      if(modelo.translacaoCubo <= 0.7){
          modelo.sentidoTranslacao = true;
          modelo.sentidoRotacao = true;
      }else{
          modelo.translacaoCubo -= 0.1;
          modelo.deltaRotacao += 10;
      }
  }
  
  /* redesenhar o ecrÃ£ */
  glutPostRedisplay();
}


/*******************************
***  callbacks de teclado    ***
*******************************/

void imprime_ajuda(void)
{
  printf("\n\nDesenho de um quadrado\n");
  printf("h,H - Ajuda \n");
  printf("F1  - Reiniciar \n");
  printf("F2  - Poligono Fill \n");
  printf("F3  - Poligono Line \n");
  printf("F4  - Poligono Point \n");
  printf("+   - Aumentar tamanho dos Cubos\n");
  printf("-   - Diminuir tamanho dos Cubos\n");
  printf("i,I - Reiniciar VariÃ¡veis\n");
  printf("p,p - Iniciar/Parar movimento dos cubinhos\n");
  printf("ESC - Sair\n");
  printf("teclas do rato para iniciar/parar rotaÃ§Ã£o e alternar eixos\n");

}


/* Callback para interaccao via teclado (carregar na tecla) */
void Key(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(1);
    /* ... accoes sobre outras teclas ... */

    case 'h' :
    case 'H' :
                imprime_ajuda();
            break;
    case '+':
            if(modelo.ladoCubo<LADO_MAXIMO)
            {
              modelo.ladoCubo+=DELTA_LADO;
              glutPostRedisplay();
            }
          break;

    case '-':
            if(modelo.ladoCubo>LADO_MINIMO)
            {
              modelo.ladoCubo-=DELTA_LADO;
              glutPostRedisplay();
            }
          break;

    case 'i' :
    case 'I' :
            inicia_modelo();
            glutPostRedisplay();
          break;
    case 'p' :
    case 'P' :
            estado.movimentoTranslacao=!estado.movimentoTranslacao;
          break;

  }

  if(DEBUG)
    printf("Carregou na tecla %c\n",key);

}

/* Callback para interaccao via teclado (largar a tecla) */
void KeyUp(unsigned char key, int x, int y)
{

  if(DEBUG)
    printf("Largou a tecla %c\n",key);
}

/* Callback para interaccao via teclas especiais  (carregar na tecla) */
void SpecialKey(int key, int x, int y)
{
  /* ... accoes sobre outras teclas especiais ... 
     GLUT_KEY_F1 ... GLUT_KEY_F12
     GLUT_KEY_UP
     GLUT_KEY_DOWN
     GLUT_KEY_LEFT
     GLUT_KEY_RIGHT
     GLUT_KEY_PAGE_UP
     GLUT_KEY_PAGE_DOWN
     GLUT_KEY_HOME
     GLUT_KEY_END
     GLUT_KEY_INSERT 
  */

  switch (key) {

  /* redesenhar o ecra */
  //glutPostRedisplay();
      case GLUT_KEY_F1 :
            inicia_modelo();
            glutPostRedisplay();
        break;

  }


  if(DEBUG)
    printf("Carregou na tecla especial %d\n",key);
}

/* Callback para interaccao via teclas especiais (largar na tecla) */
void SpecialKeyUp(int key, int x, int y)
{

  if(DEBUG)
    printf("Largou a tecla especial %d\n",key);

}

/*******************************
***  callbacks do rato       ***
*******************************/

void MouseMotion(int x, int y)
{
    /* x,y    => coordenadas do ponteiro quando se move no rato
                 a carregar em teclas
    */

  if(DEBUG)
    printf("Mouse Motion %d %d\n",x,y);

}

void MousePassiveMotion(int x, int y)
{
    /* x,y    => coordenadas do ponteiro quando se move no rato
                 sem estar a carregar em teclas
    */

  if(DEBUG)
    printf("Mouse Passive Motion %d %d\n",x,y);

}

void Mouse(int button, int state, int x, int y)
{
  /* button => GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
     state  => GLUT_UP, GLUT_DOWN
     x,y    => coordenadas do ponteiro quando se carrega numa tecla do rato
  */

  // alterar o eixo que roda (variÃ¡vel modelo.eixoRodar)

  switch(button){
    case GLUT_LEFT_BUTTON :      
      if(state == GLUT_DOWN)
      {
          if(modelo.eixoRodar == 0){
              modelo.eixoRodar = -1;
          }else{
              modelo.eixoRodar = 0;
          }
      }
     break;
    case GLUT_MIDDLE_BUTTON :      
      if(state == GLUT_DOWN)
      {       
          if(modelo.eixoRodar == 1){
              modelo.eixoRodar = -1;
          }else{
          modelo.eixoRodar = 1;
          }
      }
      break;
    case GLUT_RIGHT_BUTTON :
      if(state == GLUT_DOWN)
      {
          if(modelo.eixoRodar == 2){
              modelo.eixoRodar = -1;
          }else{
                modelo.eixoRodar = 2;
          }
      }
      break;
  }
  if(DEBUG)
    printf("Mouse button:%d state:%d coord:%d %d\n",button,state,x,y);
}
int main(int argc, char **argv)
{
  char str[]=" makefile MAKEFILE Makefile ";

  estado.doubleBuffer=1;
  glutInit(&argc, argv);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(400, 400);
  glutInitDisplayMode(((estado.doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE) | GLUT_RGB | GLUT_DEPTH);
  if (glutCreateWindow("Exemplo") == GL_FALSE)
    exit(1);

  Init();
  imprime_ajuda();
/* Registar callbacks do GLUT */
  
  /* callbacks de janelas/desenho */
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);

  /* Callbacks de teclado */
  glutKeyboardFunc(Key);
  //glutKeyboardUpFunc(KeyUp);
  glutSpecialFunc(SpecialKey);
  //glutSpecialUpFunc(SpecialKeyUp);

  /* callbacks rato */
  //glutPassiveMotionFunc(MousePassiveMotion);
  //glutMotionFunc(MouseMotion);
  glutMouseFunc(Mouse);

  /* callbacks timer/idle */
  glutTimerFunc(estado.delayMovimento, Timer, 0);
  //glutIdleFunc(Idle);

  
  /* COMECAR... */
  glutMainLoop();
  return 0;
}
