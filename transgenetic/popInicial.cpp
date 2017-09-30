#ifndef POP_INICIAL
#define POP_INICIAL

#include "param.h"
#include "SolucaoEdgeSet.cpp"

#include <iostream>
using namespace std;

extern double w[NUMOBJETIVOS];  

// TODO: melhorar a hibridizaçao entre os vetores do KCENTRUM e cia com os do SPEA/R

void alocaPopulacao(SolucaoEdgeSet *populacao[TAMANHOPOPULACAO], TRandomMersenne &rg){
	for (int i=0; i<TAMANHOPOPULACAO; i++){
		populacao[i] = new SolucaoEdgeSet(NUMEROVERTICES-1, rg);
	}
}

void renovaKCentrum(SolucaoEdgeSet *individuo){
	int k = individuo->rg->IRandom(1,NUMOBJETIVOS);
	double lambda[NUMOBJETIVOS];
	for (int ll=0; ll<k; ll++)lambda[ll] = 1.0/k;
	for (int ll=k; ll<NUMOBJETIVOS; ll++) lambda[ll] = 0;
	rmcPrim(*individuo, lambda, *individuo->rg);
	individuo->calculaOwa(w);
}

void renovaKTrimmed(SolucaoEdgeSet *individuo){
	int lim = (int) NUMOBJETIVOS/2-1;
	if (lim==0) lim = 1;
	int k = individuo->rg->IRandom(1,lim);
	double lambda[NUMOBJETIVOS];
	for (int i=0; i<k; i++) lambda[i] = 0;
	for (int i=k; i<NUMOBJETIVOS-k; i++) lambda[i] = 1.0/(NUMOBJETIVOS-(2.0*k));
	for (int i=NUMOBJETIVOS-k; i<NUMOBJETIVOS; i++)lambda[i] = 0;
	rmcPrim(*individuo, lambda, *individuo->rg);
	individuo->calculaOwa(w);
	
}

void renovaHurwicz(SolucaoEdgeSet *individuo){
	double alfa[6] = {0.2, 0.3, 0.4, 0.6, 0.7, 0.8};
	int index = individuo->rg->IRandom(0,5);
	double lambda[NUMOBJETIVOS];
	lambda[0] = alfa[index];
	lambda[NUMOBJETIVOS-1] = 1.0 - alfa[index];
	for (int ll=1; ll<NUMOBJETIVOS-1; ll++)lambda[ll] = 0;
	rmcPrim(*individuo, lambda, *individuo->rg);
	individuo->calculaOwa(w);
	
}


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
			//cout<<lambda[ll]<<" ";
		} 
		//cout<<endl;
		rmcPrim(*populacao[cont], lambda, rg);
		populacao[cont]->calculaOwa(w);
		// populacao[cont]->printSolucao();
		// cout<<endl;
		//cout<<endl;
	}

}


void gerarPopulacao3(SolucaoEdgeSet *populacao[TAMANHOPOPULACAO], TRandomMersenne &rg, double vetoresDirecoes[NUMDIRECOES][NUMOBJETIVOS]){
	//cout<<"================== Populaçao gerada pelos vetores direcionais do SPEA/R, doRandomWalk, k-centrum, k-trimmed, Hurwicz ================== "<<endl;
	SolucaoEdgeSet *aux = new SolucaoEdgeSet(NUMEROVERTICES-1, rg);
	int contRandom = 0, speaR = 0, trimed = 0, centrum=0, hur=0;
	int op = 0;
	for (int cont = 0; cont<TAMANHOPOPULACAO; cont++){
		double lambda[NUMOBJETIVOS];
		int indfgf = rg.IRandom(0, NUMDIRECOES-1);
		for (int ll=0; ll<NUMOBJETIVOS; ll++){
			lambda[ll] =  vetoresDirecoes[indfgf][ll];
		} 
		rmcPrim(*populacao[cont], lambda, rg);
		populacao[cont]->calculaOwa(w);
		op = 0;
		aux->doRandomWalk();
		aux->calculaOwa(w);
		if (aux->getOWA()<populacao[cont]->getOWA()){
			*populacao[cont] = *aux;
			op = 1;
			//op = "doRandomWalk";
		}

		renovaHurwicz(aux);
		if (aux->getOWA()<populacao[cont]->getOWA()){
			*populacao[cont] = *aux;
			op = 2;
			// op = "renovaHurwicz";

		}


		renovaKCentrum(aux);
		if (aux->getOWA()<populacao[cont]->getOWA()){
			*populacao[cont] = *aux;
			//op = "renovaKCentrum";
			op = 3;
		}


		renovaKTrimmed(aux);
		if (aux->getOWA()<populacao[cont]->getOWA()){
			*populacao[cont] = *aux;
			op = 4;
			//op = "renovaKTrimmed";
		}

		switch(op){
			case 1:
				contRandom++;
				break;
			case 2:
				hur++;
				break;
			case 3:
				centrum++;
				break;
			case 4:
				trimed++;
				break;
			default:
				speaR++;
				break;
		}
	}
	cout<<"Informacoes sobre a populacao : "<<endl;
	cout<<"\tSPEA/R = "<<100.0*speaR/TAMANHOPOPULACAO<<endl;
	cout<<"\tdoRandomWalk = "<<100.0*contRandom/TAMANHOPOPULACAO<<endl;
	cout<<"\tk-centrum = "<<100.0*centrum/TAMANHOPOPULACAO<<endl;
	cout<<"\tk-trimmed = "<<100.0*trimed/TAMANHOPOPULACAO<<endl;
	cout<<"\tHurwicz = "<<100.0*hur/TAMANHOPOPULACAO<<endl;

}



#endif