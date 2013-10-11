#include <iostream>
#include <math.h>
#include "mat.h"

#define GRAUS(x) (180 * (x) / M_PI)

using namespace std;

ponto calcularPontoMedio(ponto p1,ponto p2){
    ponto pM;
    
    pM.x = (p2.x + p1.x) / 2;
    pM.y = (p2.y + p1.y) / 2;

    return pM;
}

double calcularDistancia(ponto p1, ponto p2){

    double dist;
    dist = sqrt(pow((p2.x - p1.x),2) + pow((p2.y - p1.y),2));
    return dist;
}

double calcularAnguloInicial(ponto p1, ponto p2){
    double angulo;
    double dx;
    double dy;

    dx = p2.x - p1.y;
    dy = p2.y - p1.y;

    angulo = atan2(dy,dx);
    return angulo;
}

ponto calcularPonto(double angulo, double raio, ponto centro){
    ponto pn;
    pn.x = centro.x + (raio * cos(angulo));
    pn.y = centro.y + (raio * sin(angulo));
    return pn;
}