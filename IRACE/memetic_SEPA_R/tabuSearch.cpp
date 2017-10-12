#ifndef TABUSEARCH 
#define TABUSEARCH

#include "param.h"
#include "SolucaoEdgeSet.cpp"

#include <iostream>
using namespace std;

/*Nao utilizado no momento !!!!!*/

// Baseado no trabalho de Rocha et al (2006)
/*a busca tabu edita a solucao 'sol' que foi passada como argumento*/
void buscaTabu(SolucaoEdgeSet &sol,TRandomMersenne &rg){
	int tabu[NUMEROVERTICES][NUMEROVERTICES]; 
	for (int i=0; i<NUMEROVERTICES; i++){
		for (int j=0; j<NUMEROVERTICES; j++) tabu[i][j] = 0;
	}
	bool s_was_modified = false;
	int contIteracoes = 0;
	SolucaoEdgeSet aux(NUMEROVERTICES-1, rg);
	do{ // repita até contIteracoes==max_tabu or s nao seja modificado
		s_was_modified = false;
		int r = 0;
		int a1, a2;

		do{
			r++;
			a1 = rg.IRandom(0,NUMEROVERTICES-1-1);
			while ((a2 = rg.IRandom(0,NUMEROVERTICES-1-1)) == a1);
			aux.trocaArestas(a1,a2,aux.calcularTrocaArestas(a1,a2,sol),sol);
			aux.calculaOwa(w);
			// cout<<sol.edges[a1][0]<<","<<sol.edges[a1][1]<<" --> "<<aux.edges[a1][0]<<","<<aux.edges[a1][1]<<endl;
			// cout<<sol.edges[a2][0]<<","<<sol.edges[a2][1]<<" --> "<<aux.edges[a2][0]<<","<<aux.edges[a2][1]<<endl;
			//cout<<"aux.OWA = " << aux.getOWA()<<endl;
			if (aux.getOWA()<sol.getOWA()){
				s_was_modified = true;
				sol = aux;
			} 
			// else if (tabu[aux.edges[a1][0]][aux.edges[a1][1]]==0 && tabu[aux.edges[a2][0]][aux.edges[a2][1]]==0){
			// 	s_was_modified = true;
			// 	sol = aux;
			// }
		} while (r<MAX_VIZINHOS && s_was_modified == false);
		if (s_was_modified == true){
			for (int i=0; i<NUMEROVERTICES; i++){
				for (int j=0; j<NUMEROVERTICES; j++) {
					if (tabu[i][j]>0) tabu[i][j]--;
				}
			}
			tabu[aux.edges[a1][0]][aux.edges[a1][1]] = TABUTENURE;
			tabu[aux.edges[a2][0]][aux.edges[a2][1]] = TABUTENURE;
		}
		contIteracoes++;
		cout<<"contIteracoes = "<<contIteracoes<<endl;
	}while (contIteracoes<MAX_ITERATIONS);
}

#endif
