#ifndef RMC_PRIM
#define RMC_PRIM

#include "param.h"
#include "SolucaoEdgeSet.cpp"

#include <iostream>
using namespace std;

/*This code file was kindly provided by Monteiro */


#define INF 1e9
#define PER_ACCEPTED 0.03 // ????
#define for(i,n) for (int i=0;i<n;i++)

void rmcPrim (SolucaoEdgeSet &s, double lambda[10], TRandomMersenne &rg) {
	//cout<<"============== rm1 ============== "<<endl;
	bool arvore[1000]; // elementos ja colocados na arvore
	double mindist[1000]; // menor distancia ate cada no
	int cont = 0; // numero de elementos ja colocados
	int viz, ant[1000];
	double maisprox;
	double maisdist;
	int lrc [1000];
	int lrctam = 0;

	int inicio = rg.IRandom(0,numerovertices-1);

	// inicialmente, nenhum elemento esta na arvore e
	// a menor distancia eh infinito
	for(i,numerovertices) {
		arvore[i] = false;
		mindist[i] = INF;
	}

	// menor distancia ate o inicio eh zero
	mindist[inicio] = 0.0;
	viz = inicio;

	while (cont < numerovertices-1) {
		// coloca o no na arvore
		arvore[viz] = true;
		// ajusta a distancia dos vizinhos do no
		for(i,numerovertices) {
			double p = 0.0;
			for(j,numobjetivos) p += (lambda[j] * custos[j][viz][i]);
			if (!arvore[i] && i != viz && mindist[i] > p) {
				mindist[i] = p;
				ant[i] = viz;
			}
		}

		viz = -1;
		maisprox = INF;
		maisdist = 0.0;
		lrctam = 0;

		// coloca os que nao tem distancia inf na lrc. o tamanho da lrc sera regulado dps de acordo com o custo
		for(i,numerovertices) {
			if (!arvore[i] && mindist[i] < INF) {
				lrc [lrctam] = i;
				lrctam++;
				if (mindist[i] < maisprox)
					maisprox = mindist[i];
				if (mindist[i] > maisdist)
					maisdist = mindist[i];
			}
		}

		double maxcustoaceito = maisprox + (maisdist-maisprox)*PER_ACCEPTED;

		int auxlrc [1000];
		int auxlrctam = 0;
		for(i,lrctam) {
			if (mindist[lrc[i]] > maxcustoaceito) continue;
			else {
				auxlrc [auxlrctam] = lrc[i];
				auxlrctam++;
			}
		}

		viz = auxlrc [rg.IRandom (0, auxlrctam-1)];

		// adiciona a aresta entre ant[viz] e viz
		if ( ant[viz]< viz){
			s.edges[cont][0] = ant[viz];
			s.edges[cont][1] = viz;
		} else {
			s.edges[cont][0] = viz;
			s.edges[cont][1] = ant[viz];
		}		

		cont++;
	}
	// atualiza os custos da solucao
	s.calcularObjetivos();
}

#undef INF
#undef for

#endif
