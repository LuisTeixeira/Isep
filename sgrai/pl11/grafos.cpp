#include "grafos.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

#define __GRAFO__FILE__ "../exemplo.grafo"

No nos[_MAX_NOS_GRAFO];
Arco arcos[_MAX_ARCOS_GRAFO];
int numNos=0, numArcos=0;

using namespace std;

void addNo(No no){
	if(numNos<_MAX_NOS_GRAFO){
		nos[numNos]=no;
		numNos++;
	}else{
		cout << "N�mero de n�s chegou ao limite" << endl;
	}
}

void deleteNo(int indNo){
	if(indNo>=0 && indNo<numNos){
		for(int i=indNo; i<numNos; nos[i++]=nos[i+i]);
		numNos--;
	}else{
		cout << "Indíce de nº inválido" << endl;
	}
}

void imprimeNo(No no){
	cout << "X:" << no.x << "Y:" << no.y << "Z:" << no.z <<endl;
}

void listNos(){
	for(int i=0; i<numNos; imprimeNo(nos[i++]));
}

No criaNo(float x, float y, float z){
	No no;
	no.x=x;
	no.y=y;
	no.z=z;
	return no;
}

void addArco(Arco arco){
	if(numArcos<_MAX_ARCOS_GRAFO){
		arcos[numArcos]=arco;
		numArcos++;
	}else{
		cout << "N�mero de arcos chegou ao limite" << endl;
	}
}

void deleteArco(int indArco){
	if(indArco>=0 && indArco<numArcos){
		for(int i=indArco; i<numArcos; arcos[i++]=arcos[i+i]);
		numArcos--;
	}else{
		cout << "Ind�ce de arco inv�lido" << endl;
	}
}

void imprimeArco(Arco arco){
	cout << "No in�cio:" << arco.noi << "N� final:" << arco.nof << "Peso:" << arco.peso << "Largura:" << arco.largura << endl;
}

void listArcos(){
	for(int i=0; i<numArcos; imprimeArco(arcos[i++]));
}

Arco criaArco(int noi, int nof, float peso, float largura){
	Arco arco;
	arco.noi=noi;
	arco.nof=nof;
	arco.peso=peso;
	arco.largura=largura;
	return arco;
}

void gravaGrafo(){
	ofstream myfile;

	myfile.open (__GRAFO__FILE__, ios::out);
	if (!myfile.is_open()) {
		cout << "Erro ao abrir " << __GRAFO__FILE__ << "para escrever" <<endl;
		exit(1);
	}
	myfile << numNos << endl;
	for(int i=0; i<numNos;i++)
		myfile << nos[i].x << " " << nos[i].y << " " << nos[i].z <<endl;
	myfile << numArcos << endl;
	for(int i=0; i<numArcos;i++)
		myfile << arcos[i].noi << " " << arcos[i].nof << " " << arcos[i].peso << " " << arcos[i].largura << endl;
	myfile.close();
}
void leGrafo(){
	ifstream myfile;

	myfile.open (__GRAFO__FILE__, ios::in);
	if (!myfile.is_open()) {
		cout << "Erro ao abrir " << __GRAFO__FILE__ << "para ler" <<endl;
		exit(1);
	}
	myfile >> numNos;
	for(int i=0; i<numNos;i++)
		myfile >> nos[i].x >> nos[i].y >> nos[i].z;
	myfile >> numArcos ;
	for(int i=0; i<numArcos;i++)
		myfile >> arcos[i].noi >> arcos[i].nof >> arcos[i].peso >> arcos[i].largura ;
	myfile.close();
	// calcula a largura de cada no = maior largura dos arcos que divergem/convergem desse/nesse no	
	for(int i=0; i<numNos;i++){
		nos[i].largura=0;
		for(int j=0; j<numArcos; j++)
			if ((arcos[j].noi == i || arcos[j].nof == i) && nos[i].largura < arcos[j].largura)
				nos[i].largura = arcos[j].largura;
	}		
}