#include <iostream>
#include <math.h>

#define GRAUS(x) (180 * (x) / M_PI)

typedef struct{
    double x;
    double y;
}ponto;

using namespace std;

ponto calcularPontoMedio(ponto p1,ponto p2);

double calcularDistancia(ponto p1, ponto p2);

double calcularAnguloInicial(ponto p1, ponto p2);

ponto calcularPonto(double angulo, double raio, ponto centro);