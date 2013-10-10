typedef struct{
    double x;
    double y;
}ponto;

ponto calcularPontoMedio(ponto p1,ponto p2);

double calcularDistancia(ponto p1, ponto p2);

double calcularAnguloInicial(ponto p1, ponto p2);

ponto calcularPonto(double angulo, double raio, ponto centro);