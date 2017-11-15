#ifndef KRUSKALTRANSPOSON
#define KRUSKALTRANSPOSON

#include "param.h"
#include "SolucaoEdgeSet.cpp"
#include "auxEdgeStruct.h"
#include "RefKruskal.cpp"

#include <list>
#include <string>
#include <math.h>
#include <ctime>

#include <iostream>

using namespace std;

#define FOR(i,a,b) for(int i=a;i<b;i++)

extern int contPrimTrans; // conta a quantidade e vezes em que o primTrans tenta atacar


/*This code file was kindly provided by Monteiro */



class KruskalTransposon{
	//private:
		//TRandomMersenne *rg;
	public:
		KruskalTransposon(){}
		// KruskalTransposon(TRandomMersenne *r) {
		// 	rg = r;
		// }
		// void setRandom(TRandomMersenne *r) { rg = r; }

		/*Permite que um número aleatório entre 5 e 10% das arestas de s permaneçam na solução, completando com arestas geradas a partir do rmcKruskal */
		void atacaSolucao(SolucaoEdgeSet &s, struct ordenacao & order) {
			contPrimTrans++;
			double lambda [NUMOBJETIVOS];
			for (int i=0; i<NUMOBJETIVOS; i++) lambda[i] = order.v_esc[i];;
			int reftam;
			int nArestas = NUMEROVERTICES-1;

			reftam = IRandom((int)(nArestas*0.1), (int)(nArestas*0.3));
			//assert (reftam > 0);

			auxEdgeSet fitVec [nArestas];
			for (int i = 0; i < nArestas; i++) {
				fitVec[i].fit = lambda[0]*f(0, s.edges[i][0], s.edges[i][1]) +
					        lambda[1]*f(1, s.edges[i][0], s.edges[i][1]);
				fitVec[i].a = s.edges[i][0];
				fitVec[i].b = s.edges[i][1];
			}
			stable_sort (fitVec, fitVec + nArestas, auxEdgeSetComp);

			//soteiam-se aleatoriamente reftam arestas diferentes
			//uma aresta é escolhida se o rand for maior que seu prob[i] e menor ou igual ao prob de i+1
			//estas arestas vao para ref
			SolucaoEdgeSet ref (reftam);

			int tam = 0;
			double prob;
			bool inref [nArestas];
			for (int i = 0; i < nArestas; i++)
				inref [i] = false;


			while (tam != reftam) {

				prob = sin (genrand64_real3()*PI/(-2.0)) + 1.0;
				//assert (!(prob < 0) && !(prob > 1));

				int ind = (int)(prob*((double)(nArestas))); //gera o indice do vetor de fitness. 
				if (ind == nArestas)
					ind = (int)( (prob/2.0) * ((double)(nArestas)) ); //gera o indice do vetor de fitness. 

				//assert (ind > -1 && ind < nArestas);

				if (!inref[ind]) {
					ref.edges[tam][0] = fitVec[ind].a;
					ref.edges[tam][1] = fitVec[ind].b;
					inref[ind] = true;
					tam++;
				}
			}
			RefKruskal refkrus;
			refkrus.executar (ref, reftam, s, order);
		}
};

#endif