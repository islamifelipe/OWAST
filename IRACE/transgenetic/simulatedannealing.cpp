#ifndef SIMULATEDANNEALING  
#define SIMULATEDANNEALING

#include "param.h"
#include "SolucaoEdgeSet.cpp"
#include <math.h>       /* exp */

#include <iostream>
using namespace std;

extern int quantSAinvocado; // quantidade de vezes em que o SA (trans2) foi invocado

// baseado no modelo classico de SA (notas de aula de Profa. Silvia e Beth)
// a soluçao sol será modificada no final
void SA(SolucaoEdgeSet &sol,TRandomMersenne &rg){
	//cout<<"Inicio do SA = "<<sol.getOWA()<<endl;
	quantSAinvocado++;
	double temperature = temperatura;
	double iteracaoK = iteracao/1.0;
	int quantIteracaoK = (int) iteracaoK;
	int a1, a2;
	double probabilidade;
	double deltaC;
	SolucaoEdgeSet aux(numerovertices-1, rg);
	SolucaoEdgeSet xk(numerovertices-1, rg);
	xk = sol;
	do {
		for (int i=0; i<quantIteracaoK; i++){
			//gera nova soluçao
			a1 = rg.IRandom(0,numerovertices-1-1);
			while ((a2 = rg.IRandom(0,numerovertices-1-1)) == a1);
			aux.trocaArestas(a1,a2,aux.calcularTrocaArestas(a1,a2,xk),xk);
			aux.calculaOwa(w);
			deltaC = aux.getOWA() - xk.getOWA();
			if (deltaC<=0){ // aceita soluçao
				xk = aux;
				if (xk.getOWA()<sol.getOWA()){ //descida
					sol = xk;
				}
			} else{ // aplica probabilidade da temperatura
				probabilidade = exp((-1)*deltaC/temperature);
				double pp = rg.Random ();
				if (pp<probabilidade){
					xk = aux;
				}
			}
		}
		temperature/=taxadecaimento;
		iteracaoK*=taxadecaimentoIteracao;
		// cout<<"temperature = "<<temperature<<endl;
		// cout<<"iteracaoK = "<<iteracaoK<<endl;
		quantIteracaoK = (int) iteracaoK;
		if (xk.getOWA()<sol.getOWA()){ //descida
			sol = xk;
		}
	} while ((temperature-1.0)>EPS);
	//cout<<"FIM do SA = "<<sol.getOWA()<<endl;

}

#endif
