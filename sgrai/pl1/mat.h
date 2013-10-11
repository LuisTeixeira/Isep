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

int main()
{
    int numberOfPoints;
    ponto p1, p2, pontoMedio;
    double dist;

    cout << "Insira o número de pontos: ";
    cin >> numberOfPoints;

    /* Ponto 1*/
    cout << "Insira os dois pontos" << endl << "P1(X): ";
    cin >> p1.x;
    cout << "P1(Y):";
    cin >> p1.y;

    /*Ponto 2*/
    cout << "P2(X): ";
    cin >> p2.x;
    cout << "P2(Y): ";
    cin >> p2.y;

    pontoMedio = calcularPontoMedio(p1,p2);
    cout << "Ponto médio: (" << pontoMedio.x << "," << pontoMedio.y << ")" << endl;

    dist = calcularDistancia(p1,p2);
    cout << "Distancia: " << dist << endl;

    double angulo = calcularAnguloInicial(p1,p2);
    cout << "Angulo Inicial: " << angulo << endl;

    double anguloinc =  2 * M_PI / numberOfPoints;
    double raio = dist / 2;

    for(int i = 0; i < numberOfPoints; i++){
        double anguloPx = angulo + (i * anguloinc);
        ponto pn = calcularPonto(anguloPx, raio, pontoMedio);
        cout << "X: " << pn.x << " Y: " << pn.y << " Angulo: " << GRAUS(anguloPx) << endl;
    }
}