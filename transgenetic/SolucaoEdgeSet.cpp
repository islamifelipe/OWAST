#ifndef SOLUCAOZG_CPP
#define SOLUCAOZG_CPP
/*This code file was kindly provided by Monteiro */

#include <cstdio>
#include <queue>
#include "Solucao.cpp"
#include "UnionFind.cpp"
#include "param.h"
#include "auxEdgeStruct.h"
#include <algorithm> // std::sort
#include <iostream>

using namespace std;

extern double custos[NUMOBJETIVOS][NUMEROVERTICES][NUMEROVERTICES];

typedef struct {
	int listaadj[NUMEROVERTICES][NUMEROVERTICES], graus[NUMEROVERTICES];
	bool completo;
} grafo;


class SolucaoEdgeSet : public Solucao {
	public:
	int edges[NUMEROVERTICES-1][2]; // para cada linha (aresta da arvore), teremos duas colunas (vertices extremos i e j)
	int nEdges;
	UnionFind uf;
	grafo *g;
	double antigof[NUMOBJETIVOS];

	SolucaoEdgeSet(int n,TRandomMersenne &r) {
		nEdges = n;
		for (int i=0; i<NUMOBJETIVOS; i++){
			f[i]=0;
		}
		rg = &r;
		g = NULL;
	}
	~SolucaoEdgeSet() {

	}

    // copia somente os valores de fitness
    // util para guardar copias de solucoes somente para comparacao
    void shallowCopy(SolucaoEdgeSet &s) {
        for (int i=0; i<NUMOBJETIVOS; i++){
			s.f[i] = f[i];
		}
    }

    bool static myfunction (int i,int j) { return !(i<j); } // nao crescente
    double getOwa(double w[NUMOBJETIVOS]){
    	std::vector<int> myvector(f, f+NUMOBJETIVOS); 
		std::sort (myvector.begin(), myvector.end(), myfunction); 
		double ret = 0;
		for (int i=0; i<NUMOBJETIVOS; i++){
			ret += w[i]*myvector[i];
		}
		return ret;
		
    }

	/* Calcula o fitness atual da solucao
	 */
	void calcularObjetivos() {
		for (int j=0;j<NUMOBJETIVOS;j++){
			f[j] = 0.0;
		}
		for (int i=0;i<NUMEROVERTICES-1;i++)
			for (int j=0;j<NUMOBJETIVOS;j++)
				f[j] += f(j,edges[i][0],edges[i][1]);
	}

	/* gera uma arvore aleatoria
	 * Complexidade n */
    void doRandomWalk() {

        int vertlist [NUMEROVERTICES];
        for (int i = 0; i < NUMEROVERTICES; i++)
            vertlist[i]=i;
        int vertctr = NUMEROVERTICES-1; //tamanho valido da lista;

        int v_ind = rg->IRandom(0,vertctr);
        int v_esc = vertlist[v_ind];
        vertlist [v_ind] = vertlist[vertctr];
        vertlist [vertctr] = v_esc;
        vertctr--;
        int viz1, viz2, viz2_ind;
        int cont = 0;
        while (cont < NUMEROVERTICES-1) {

            viz1 = vertlist [rg->IRandom(vertctr+1, NUMEROVERTICES-1)];
            viz2_ind = rg->IRandom(0,vertctr);
            viz2 = vertlist[viz2_ind];

            vertlist [viz2_ind] = vertlist[vertctr];
            vertlist [vertctr] = viz2;
            vertctr--;
            if (viz1<viz2) {
	            edges[cont][0] = viz1;
	            edges[cont][1] = viz2;
	        } else {
	        	edges[cont][0] = viz2;
	            edges[cont][1] = viz1;
	        }
            cont++;
        }
        calcularObjetivos();
        //assert (confereArestas());
    }



	// /* Gera um individuo aleatorio
	//  * Complexidade O(n lg n) */
	// void geraIndividuoAleatorio() {
	//     g = new grafo;
	// 	g->completo = true;

	// 	for (int i=0;i<NUMEROVERTICES;i++)
	// 			g->graus[i] = NUMEROVERTICES;
	// 	doRandomWalk();
	// 	delete g;
	// }

	// /* Faz o crossover entre dois individuos
	//  * Complexidade O(n lg n) */
	// void crossover(const SolucaoEdgeSet &pai, const SolucaoEdgeSet &mae) {
	// 	bool adicionado[NUMEROVERTICES][NUMEROVERTICES];
	// 	memset(adicionado,0,sizeof(adicionado));
	// 	g = new grafo;
	// 	g->completo = false;
	// 	memset(g->graus,0,sizeof(g->graus));

	// 	for (int i=0;i<NUMEROVERTICES-1;i++) {
	// 		if (!adicionado[pai.edges[i][0]][pai.edges[i][1]]) {
	// 			adicionado[pai.edges[i][0]][pai.edges[i][1]] = adicionado[pai.edges[i][1]][pai.edges[i][0]] = true;
	// 			g->listaadj[pai.edges[i][0]][g->graus[pai.edges[i][0]]++] = pai.edges[i][1];
	// 			g->listaadj[pai.edges[i][1]][g->graus[pai.edges[i][1]]++] = pai.edges[i][0];
	// 		}
	// 	}
	// 	for (int i=0;i<NUMEROVERTICES-1;i++) {
	// 		if (!adicionado[mae.edges[i][0]][mae.edges[i][1]]) {
	// 			adicionado[mae.edges[i][0]][mae.edges[i][1]] = adicionado[mae.edges[i][1]][mae.edges[i][0]] = true;
	// 			g->listaadj[mae.edges[i][0]][g->graus[mae.edges[i][0]]++] = mae.edges[i][1];
	// 			g->listaadj[mae.edges[i][1]][g->graus[mae.edges[i][1]]++] = mae.edges[i][0];
	// 		}
	// 	}
	// 	doRandomWalk();
	// 	delete g;
	// }

	// /* Faz a troca das arestas ai e aj, religando no formato 2-OPT
	//  * Complexidade O(1) */
	// void trocaArestas(int ai, int aj, char tipo) {
	// 	int a = edges[ai][0];
	// 	int b = edges[ai][1];
	// 	int c = edges[aj][0];
	// 	int d = edges[aj][1];

	// 	int novaA[2]={0,0}, novaB[2]={0,0};
	// 	novaA[0] = a;
	// 	novaB[0] = b;

	// 	// se todos ficarem na mesma componente, junta AC/BD, se nao junta AD/BC
	// 	if (tipo == 0) {
	// 		// faz a uniao AC e BD
	// 		novaA[1] = c;
	// 		novaB[1] = d;
	// 	} else if (tipo == 1){
	// 		// faz a uniao AD e BC
	// 		novaA[1] = d;
	// 		novaB[1] = c;
	// 	}
	// 	edges[ai][0] = novaA[0];
	// 	edges[ai][1] = novaA[1];
	// 	edges[aj][0] = novaB[0];
	// 	edges[aj][1] = novaB[1];
	// }

	// char calcularTrocaArestas(int ai, int aj) {
	// 	// Calcula a possivel troca das arestas "ai" com "aj"
	// 	// Complexidade O(n)
	// 	// uniao busca
	// 	uf.clear();
	// 	antigof[0] = getObj(0);
	// 	antigof[1] = getObj(1);
	// 	f[0] = f[1] = 0.0;
	// 	for (int i=0;i<NUMEROVERTICES-1;i++)
	// 		if (i != ai && i != aj) {
	// 			uf.unionClass(edges[i][0],edges[i][1]);
	// 			for (int k=0;k<NUMOBJETIVOS;k++)
	// 				f[k] +=  f(k,edges[i][0],edges[i][1]);
	// 		}
	// 	int a = edges[ai][0];
	// 	int b = edges[ai][1];
	// 	int c = edges[aj][0];
	// 	int d = edges[aj][1];

	// 	char tipoTroca;
	// 	// junta a-c e b-d
	// 	uf.unionClass(a,c);
	// 	uf.unionClass(b,d);
	// 	// se todos ficarem na mesma componente, junta AC/BD, se nao junta AD/BC
	// 	if (uf.sameClass(a,b) && uf.sameClass(a,c) && uf.sameClass(a,d)) {
	// 		// faz a uniao AC e BD
	// 		tipoTroca = 0;
	// 		for (int k=0;k<NUMOBJETIVOS;k++)
	// 			f[k] = f[k] + ( f(k,a,c) + f(k,b,d) );
	// 	} else {
	// 		// faz a uniao AD e BC
	// 		tipoTroca = 1;
	// 		for (int k=0;k<NUMOBJETIVOS;k++)
	// 			f[k] = f[k] + ( f(k,a,d) + f(k,b,c) );
	// 	}
	// 	return tipoTroca;
	// }

	// //efetua remocao de aresta ai, adicionando a aresta de menor custo que reconecta a arvore
	// void substAresta (int ai, int index, fitVecNode * fitVec[]) {


	// 	uf.clear();

	// 	antigof[0] = getObj(0);
	// 	antigof[1] = getObj(1);
	// 	f[0] = f[1] = 0.0;

	// 	int a = edges[ai][0];
	// 	int b = edges[ai][1];
	// 	for (int i=0;i<NUMEROVERTICES-1;i++) {
	// 		if (i != ai) {
	// 			uf.unionClass(edges[i][0],edges[i][1]);
	// 			for (int k=0;k<NUMOBJETIVOS;k++)
	// 				f[k] +=  f(k,edges[i][0],edges[i][1]);
	// 		}
	// 	}

	// 	int edge = 0;
	// 	// anda ate a proxima aresta que pode ser inserida

	// 	while (uf.sameClass(fitVec[index][edge].a,fitVec[index][edge].b)) edge++;

	// 	if ( (fitVec[index][edge].a == a && fitVec[index][edge].b == b) ||
	// 			(fitVec[index][edge].a == b && fitVec[index][edge].b == a) ) {
	// 		edge++;
	// 		while (uf.sameClass(fitVec[index][edge].a,fitVec[index][edge].b)) edge++;
	// 	}
	// 	// coloca a aresta na solucao
	// 	edges[ai][0] = fitVec[index][edge].a;
	// 	edges[ai][1] = fitVec[index][edge].b;
	// 	setObj(0,getObj(0)+f(0,edges[ai][0],edges[ai][1]));
	// 	setObj(1,getObj(1)+f(1,edges[ai][0],edges[ai][1]));
	// 	uf.unionClass( fitVec[index][edge].a, fitVec[index][edge].b );

	// 	assert (confereArestas());
	// }

	// void desfazerCalculoTroca() {
	// 	f[0] = antigof[0];
	// 	f[1] = antigof[1];
	// }

	// // TEM DE SER CHAMADO ANTES DA TROCA!
	// int getArestaEntrou(int i, int j, char tipo, int arest, int no) {
	// 	if (tipo == 0) {
	// 		int nos[2][2] = { {edges[i][0],edges[j][0]}, {edges[i][1],edges[j][1]} };
	// 		return nos[ arest ][ no ];
	// 	} else {
	// 		int nos[2][2] = { {edges[i][0],edges[j][1]}, {edges[i][1],edges[j][0]} };
	// 		return nos[ arest ][ no ];
	// 	}
	// }
	// int getArestaSaiu(int i, int j, char tipo, int arest, int no) {
	// 	int nos[2][2] = { {edges[i][0],edges[i][1]}, {edges[j][0],edges[j][1]} };
	// 	return nos[ arest ][ no ];
	// }


	// void mutacao() {
	// 	int a1 = rg->IRandom(0,NUMEROVERTICES-1-1), a2;
	// 	while ((a2 = rg->IRandom(0,NUMEROVERTICES-1-1)) == a1);
	// 	trocaArestas(a1,a2,calcularTrocaArestas(a1,a2));
	// }

	// void operator=(SolucaoEdgeSet &s) {
	// 	nEdges = s.nEdges;
	// 	f[0] = s.f[0];
	// 	f[1] = s.f[1];
	// 	memcpy(edges,s.edges,sizeof(edges));
	// 	antigof[0] = s.antigof[0];
	// 	antigof[1] = s.antigof[1];
	// }

	void printSolucao() {
		for (int i=0;i<NUMEROVERTICES-1;i++){
			cout<<edges[i][0]<<" "<<edges[i][1]<<" ";
			for (int o=0; o<NUMOBJETIVOS; o++){
				cout<<f(o,edges[i][0],edges[i][1])<<" ";
			}
			cout<<endl;	
		}
		cout<<"( ";
		for (int o=0; o<NUMOBJETIVOS; o++){
			cout<<this->f[o]<<" ";
		}
		cout<<")"<<endl;
	}

	// void printPonto(FILE *f) {
	// 	fprintf(f,"%.6lf %.6lf\n",getObj(0),getObj(1));
	// }

	// bool confereArestas() {
	// 	uf.clear();
	// 	bool usados[NUMEROVERTICES] = {false};
	// 	int numUsados = 0;
	// 	for (int i=0;i<NUMEROVERTICES-1;i++) {
	// 		if (uf.sameClass(edges[i][0],edges[i][1])) return false;
	// 		uf.unionClass(edges[i][0],edges[i][1]);
	// 		for (int j=0;j<2;j++) {
	// 	                if (!usados[edges[i][j]]) {
	//                			usados[edges[i][j]] = true;
 //        			        numUsados++;
 //                		}
	// 		}
	// 	}
	// 	if (numUsados != NUMEROVERTICES) return false;
	// 	return true;
	// }

	// bool confereObjetivos() {
	// 	double v[2] = {0.0,0.0};
	// 	for (int i=0;i<NUMEROVERTICES-1;i++) {
	// 		v[0] += f(0,edges[i][0],edges[i][1]);
	// 		v[1] += f(1,edges[i][0],edges[i][1]);
	// 	}
	// 	if (fabs(v[0])-EPS > f[0] || fabs(v[1])-EPS > f[1]) return false;
	// 	return true;
	// }

};

#endif
