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
void SA(SolucaoEdgeSet &sol){
	//cout<<"Inicio do SA = "<<sol.getOWA()<<endl;
	quantSAinvocado++;
	double temperature = TEMPERATURA;
	double iteracaoK = ITERACAO_K/1.0;
	int quantIteracaoK = (int) iteracaoK;
	int a1, a2;
	double probabilidade;
	double deltaC;
	SolucaoEdgeSet aux(NUMEROVERTICES-1);
	SolucaoEdgeSet xk(NUMEROVERTICES-1);
	xk = sol;
	do {
		for (int i=0; i<quantIteracaoK; i++){
			//gera nova soluçao
			a1 = IRandom(NUMEROVERTICES/3,NUMEROVERTICES/2);
			// a1 = IRandom(0,NUMEROVERTICES-1-1);
			 //while ((a2 = IRandom(0,NUMEROVERTICES-1-1)) == a1);
			a2 = IRandom(NUMEROVERTICES/2+1,2*NUMEROVERTICES/3);
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
				double pp = genrand64_real3();
				if (pp<probabilidade){
					xk = aux;
				}
			}
		}
		temperature/=FATORDECAIMENTO;
		iteracaoK*=FATORDECAIMENTOITERACAO;
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
