/* 
 * File:   pl2.h
 * Author: qsp
 *
 * Created on 04 October 2013, 21:11
 */

#ifndef PL2_H
#define	PL2_H

typedef struct {
    double x, y;
} point;

int pMedio(point a, point b) ;

double pDistancia(point a, point b);

point pPontoCirc(point centro, double raio, double angulo);


#endif	/* PL2_H */