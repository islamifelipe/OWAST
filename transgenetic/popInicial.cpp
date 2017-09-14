#ifndef POP_INICIAL
#define POP_INICIAL

#include "param.h"
#include "SolucaoEdgeSet.cpp"

#include <iostream>
using namespace std;

extern double w[NUMOBJETIVOS];  

void alocaPopulacao(SolucaoEdgeSet *populacao[TAMANHOPOPULACAO], TRandomMersenne &rg){
	for (int i=0; i<TAMANHOPOPULACAO; i++){
		populacao[i] = new SolucaoEdgeSet(NUMEROVERTICES-1, rg);
	}
}

// TODO: descartar?
void gerarPopulacao1(SolucaoEdgeSet *populacao[TAMANHOPOPULACAO], TRandomMersenne &rg){
	cout<<"================== Populaçao gerada com doRandomWalk ================== "<<endl;
	int i, cont;
	for (i=0, cont = 0; cont<(int)PORCENT_RANDOM*TAMANHOPOPULACAO/100 && i<TAMANHOPOPULACAO; i++, cont++){
		populacao[i]->doRandomWalk();
		populacao[i]->calculaOwa(w);
	}
	cout<<"================== rmcPrim com k-centrum ================== "<<endl;
	for (cont = 0; cont<(int)PORCENT_KCENTRUM*TAMANHOPOPULACAO/100 && i<TAMANHOPOPULACAO; i++, cont++){
		int k = rg.IRandom(1,NUMOBJETIVOS);
		double lambda[NUMOBJETIVOS];
		for (int ll=0; ll<k; ll++)lambda[ll] = 1.0/k;
		for (int ll=k; ll<NUMOBJETIVOS; ll++) lambda[ll] = 0;
		rmcPrim(*populacao[i], lambda, rg);
		populacao[i]->calculaOwa(w);
	}

	cout<<"================== rmcPrim com k-trimmed ================== "<<endl;
	int lim = (int) NUMOBJETIVOS/2-1;
	if (lim==0) lim = 1;
	for (cont = 0; cont<(int)PORCENT_KTRIMENT*TAMANHOPOPULACAO/100 && i<TAMANHOPOPULACAO; i++, cont++){
		int k = rg.IRandom(1,lim);
		double lambda[NUMOBJETIVOS];
		for (int i=0; i<k; i++) lambda[i] = 0;
		for (int i=k; i<NUMOBJETIVOS-k; i++) lambda[i] = 1.0/(NUMOBJETIVOS-(2.0*k));
		for (int i=NUMOBJETIVOS-k; i<NUMOBJETIVOS; i++)lambda[i] = 0;
		rmcPrim(*populacao[i], lambda, rg);
		populacao[i]->calculaOwa(w);
	}

	cout<<"================== rmcPrim com Hurwicz ================== "<<endl;
	double alfa[6] = {0.2, 0.3, 0.4, 0.6, 0.7, 0.8};
	for (cont = 0; cont<(int)PORCENT_HURWICZ*TAMANHOPOPULACAO/100 && i<TAMANHOPOPULACAO; i++, cont++){
		int index = rg.IRandom(0,5);
		double lambda[NUMOBJETIVOS];
		lambda[0] = alfa[index];
		lambda[NUMOBJETIVOS-1] = 1.0 - alfa[index];
		for (int ll=1; ll<NUMOBJETIVOS-1; ll++)lambda[ll] = 0;
		rmcPrim(*populacao[i], lambda, rg);
		populacao[i]->calculaOwa(w);
	}
}
void gerarPopulacao2(SolucaoEdgeSet *populacao[TAMANHOPOPULACAO], TRandomMersenne &rg, double vetoresDirecoes[NUMDIRECOES][NUMOBJETIVOS]){
	cout<<"================== Populaçao gerada pelos vetores direcionais do SPEA/R ================== "<<endl;
	for (int cont = 0; cont<TAMANHOPOPULACAO; cont++){
		double lambda[NUMOBJETIVOS];
		for (int ll=0; ll<NUMOBJETIVOS; ll++){
			lambda[ll] =  vetoresDirecoes[cont][ll];
			cout<<lambda[ll]<<" ";
		} 
		cout<<endl;
		rmcPrim(*populacao[cont], lambda, rg);
		populacao[cont]->calculaOwa(w);
		populacao[cont]->printSolucao();
		cout<<endl;
		cout<<endl;
	}

}


#endif