
/* 
 * File:   main.cpp
 * Author: qsp
 *
 * Created on 27 September 2013, 21:34
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <math.h>

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

typedef struct {
    double x, y;
} point;

using namespace std;

point pMedio(point a, point b) {
    point medio;

    medio.x = (b.x + a.x) / 2;
    medio.y = (b.y + a.y) / 2;

    return medio;
}

double pDistancia(point a, point b) {
    double distancia;

    distancia = sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));

    return distancia;
}

point pPontoCirc(point centro, double raio, double angulo) {
    point ponto;
    
    ponto.x = centro.x + raio * cos(angulo);
    ponto.y = centro.y + raio * sin(angulo);
    
    return ponto;
}


//int main(int argc, char** argv) {
//    int n;
//    point p0, p1;
//
//    cout << "Número de pontos: ";
//    cin >> n;
//    cout << endl;
//    
//    cout << "P0 x: ";
//    cin >> p0.x;
//
//    cout << "P0 y: ";
//    cin >> p0.y;
//    cout << endl;
//
//    cout << "P1 x: ";
//    cin >> p1.x;
//
//    cout << "P1 y: ";
//    cin >> p1.y;
//    cout << endl;
//
//    point medio = pMedio(p0, p1);
//    double distancia = pDistancia(p0, p1);
//    double raio = distancia / 2;
//    
//    cout << "Entre P0 e P1:" << endl;
//    cout << "\tPonto médio: (" << medio.x << "," << medio.y << ")" << endl;
//    cout << "\tDistância: " << distancia << endl;
//
//    cout << endl << "Cálculo dos pontos da circunferência:" << endl;
//
//    double nRad = (2 * M_PI) / n;
//    cout << "Ângulo entre pontos: " << GRAUS(nRad) << " graus." << endl << endl;
//
//    cout << "Partindo de 0 graus:" << endl;
//    cout << setw(10) << "Ponto" << setw(15) << "Coord X"
//            << setw(15) << "Coord Y" << setw(10) << "angulo" << endl;
//    
//    for (int i = 0; i < n; ++i) {
//        double angulo = nRad * i;
//        point p = pPontoCirc(medio, raio, angulo);
//        cout << setw(10) << i << setw(15) << p.x
//                << setw(15) << p.y << setw(10) << GRAUS(angulo) <<endl;
//    }
//    
//    
//    double dy = p1.y - medio.y;
//    double dx = p1.x - medio.x;
//    double anguloInicial = atan2(dy, dx);
//    
//    cout << endl;
//    cout << "Partindo de " << GRAUS(anguloInicial) << " graus:" << endl;
//    cout << setw(10) << "Ponto" << setw(15) << "Coord X"
//            << setw(15) << "Coord Y" << setw(10) << "angulo" << endl;
//    
//    for (int i = 0; i < n; ++i) {
//        double angulo = anguloInicial + nRad * i;
//        point p = pPontoCirc(medio, raio, angulo);
//        cout << setw(10) << i << setw(15) << p.x
//                << setw(15) << p.y << setw(10) << GRAUS(angulo) <<endl;
//    }
//    
//    return 0;
//}

