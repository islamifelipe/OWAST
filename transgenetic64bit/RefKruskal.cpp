
#ifndef REFKRUSKAL_CPP
#define REFKRUSKAL_CPP


#include "param.h"
#include "SolucaoEdgeSet.cpp"
#include "auxEdgeStruct.h"
#include "UnionFind.cpp"
#include <iostream>
using namespace std;

class RefKruskal {
private:
	UnionFind uf;

public:
	RefKruskal() {}

	void executar(SolucaoEdgeSet ref, int reftam, SolucaoEdgeSet &s, struct ordenacao & arestas) {

		// for(int i = 0; i < NUMOBJETIVOS; i++) {
		// 	s.setObj(i,0.0);
		// }

		uf.clear();
		
		for (int i = 0; i < reftam; i++) {
			s.edges[i][0] = ref.edges[i][0];
			s.edges[i][1] = ref.edges[i][1];
			uf.unionClass (s.edges[i][0], s.edges[i][1]);
			// s.setObj (0, s.getObj(0) + custos[0][s.edges[i][0]][s.edges[i][1]]);
			// s.setObj (1, s.getObj(1) + custos[1][s.edges[i][0]][s.edges[i][1]]);
		}
		// coloca NUMEROVERTICES-1 arestas do grafo sem formar ciclo
		int cont = reftam, edge = 0;
		//int quantArestasOrdem = min (NUMEROVERTICES*(NUMEROVERTICES-1)/2, 10*NUMEROVERTICES);
		int quantArestasOrdem = NUMEROVERTICES*(NUMEROVERTICES-1)/2;

		while (cont < NUMEROVERTICES-1) {

			// anda ate a proxima aresta que pode ser inserida
			while (uf.sameClass(arestas.arestas[edge].a,arestas.arestas[edge].b) && (edge < quantArestasOrdem) ) edge++;
			//cout<<quantArestasOrdem<<endl;
			if (! (edge < quantArestasOrdem) ) {
				cerr << "limite do edge ultrapassado!" << endl;
				exit (1);
			}
			// coloca a aresta na solucao
			s.edges[cont][0] = arestas.arestas[edge].a;
			s.edges[cont][1] = arestas.arestas[edge].b;
			// s.setObj(0,s.getObj(0)+f(0,s.edges[cont][0],s.edges[cont][1]));
			// s.setObj(1,s.getObj(1)+f(1,s.edges[cont][0],s.edges[cont][1]));
			uf.unionClass( arestas.arestas[edge].a, arestas.arestas[edge].b );
			cont++;
		}
		// assert (s.confereArestas());
		s.calcularObjetivos();
	}

	// void executar(SolucaoEdgeSet ref, int reftam, SolucaoEdgeSet &s, struct ordenacao & arestas, int maxTam) {

	// 	// for(int i = 0; i < NUMOBJETIVOS; i++) {
	// 	// 	s.setObj(i,0.0);
	// 	// }

	// 	uf.clear();
		
	// 	for (int i = 0; i < reftam; i++) {
	// 		s.edges[i][0] = ref.edges[i][0];
	// 		s.edges[i][1] = ref.edges[i][1];
	// 		uf.unionClass (s.edges[i][0], s.edges[i][1]);
	// 		// s.setObj (0, s.getObj(0) + custos[0][s.edges[i][0]][s.edges[i][1]]);
	// 		// s.setObj (1, s.getObj(1) + custos[1][s.edges[i][0]][s.edges[i][1]]);
	// 	}
	// 	// coloca NUMEROVERTICES-1 arestas do grafo sem formar ciclo
	// 	int cont = reftam, edge = 0;
	// 	int quantArestasOrdem = min (NUMEROVERTICES*(NUMEROVERTICES-1)/2, 10*NUMEROVERTICES);
	// 	//int quantArestasOrdem = NUMEROVERTICES*(NUMEROVERTICES-1)/2;
	// 	while (cont < maxTam) {

	// 		// anda ate a proxima aresta que pode ser inserida
	// 		while (uf.sameClass(arestas.arestas[edge].a,arestas.arestas[edge].b) && (edge < quantArestasOrdem) ) edge++;

	// 		if (! (edge < quantArestasOrdem) ) {
	// 			cerr << "limite do edge ultrapassado!" << endl;
	// 			exit (1);
	// 		}
	// 		// coloca a aresta na solucao
	// 		s.edges[cont][0] = arestas.arestas[edge].a;
	// 		s.edges[cont][1] = arestas.arestas[edge].b;
	// 		// s.setObj(0,s.getObj(0)+f(0,s.edges[cont][0],s.edges[cont][1]));
	// 		// s.setObj(1,s.getObj(1)+f(1,s.edges[cont][0],s.edges[cont][1]));
	// 		uf.unionClass( arestas.arestas[edge].a, arestas.arestas[edge].b );
	// 		cont++;
	// 	}
	// }
};

#endif

