#ifndef PLASMIDEO_CPP
#define PLASMIDEO_CPP

#include <cassert>
#include "SolucaoEdgeSet.cpp"
#include "param.h"
#include "rmcPrim.cpp"
#include <list>
#include <string>
#include <iostream>
using namespace std;


/*This code file was kindly provided by Monteiro */

#define FOR(i,a,b) for(int i=a;i<b;i++)
class Plasmideo {

	private:
	int **trechoInserir;//[NUMEROARESTAS][2];
	UnionFind uf;
    TRandomMersenne *rg;
    int tamTrecho;

	public:
	Plasmideo(){
		trechoInserir = new int*[numerovertices-1];
		for (int i=0; i<numerovertices-1; i++){
			trechoInserir[i] = new int[2];
		}
	}
	Plasmideo(TRandomMersenne *r) {
		trechoInserir = new int*[numerovertices-1];
		for (int i=0; i<numerovertices-1; i++){
			trechoInserir[i] = new int[2];
		}
		rg = r;
	}
	void setRandom(TRandomMersenne *r) { rg = r; }

    void printTrechoInserir () {
        FOR(i, 0, tamTrecho) {
            FOR(j, 0, 2) {
                cout << trechoInserir [i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }

    /*Plasmido construido como o rmcPrim de tamanho (tam) limitado*/
	void geraPlasm_rmcPrim (double lambda[10], int tam) {
        tamTrecho = tam;
		SolucaoEdgeSet *agm = new SolucaoEdgeSet(numerovertices-1, *rg); // TODO: fazer sem new
	 	rmcPrim (*agm,lambda,*rg, tamTrecho);
	 	FOR(i, 0, tamTrecho) {
            trechoInserir [i][0] = agm->edges[i][0];
            trechoInserir [i][1] = agm->edges[i][1];
        }
	}

	void geraPlasm_Solucao(SolucaoEdgeSet &s, int tam) {

		tamTrecho = tam;

        int c = 0;
        bool naarvore[1000];// = {  false }; // diz (true) nos vértices que ja estivem na cadeia (subtree) do plasmideo
		for(int i=0; i<1000; i++) naarvore[i] = false;
        int e = rg->IRandom(0,numerovertices-1-1); // aresta inicial
		
        trechoInserir[0][0] = s.edges[e][0];
		trechoInserir[0][1] = s.edges[e][1];
		
        naarvore[s.edges[e][0]] = naarvore[s.edges[e][1]] = true;
        
        std::swap( s.edges[e][0], s.edges[c][0] );
        std::swap( s.edges[e][1], s.edges[c][1] );
        c++;
        
        // cria uma lista das arestas conectadas a arvore atual
        int lista[1000], tamLista = 0;
        while (c < tamTrecho) {
            tamLista = 0;
            FOR(i,c,numerovertices-1) {
                if (naarvore[s.edges[i][0]] || naarvore[s.edges[i][1]]) {
                    //fprintf(stderr,"Colocando (%d,%d) na lista\n",s->edges[i][0],s->edges[i][1]);
                    lista[tamLista++] = i;
                }
            }

            // a lista nunca pode estar vazia!
            if (!(tamLista > 0)) {
                fprintf (stderr, "TamLista: %d\n", tamLista);
            }
            assert(tamLista > 0);

            // escolhe aleatoriamente uma das arestas da lista
            int esc = lista[rg->IRandom(0,tamLista-1)];
            naarvore[s.edges[esc][0]] = naarvore[s.edges[esc][1]] = true;
            //fprintf(stderr,"Escolhida aresta (%d,%d)\n",s->edges[esc][0],s->edges[esc][1]);

            // joga a aresta "esc" para o comeco do conjunto
            std::swap( s.edges[esc][0], s.edges[c][0] );
            std::swap( s.edges[esc][1], s.edges[c][1] );
            c++;
        }

        FOR(i, 1, tam) {
            trechoInserir [i][0] = s.edges[i][0];
            trechoInserir [i][1] = s.edges[i][1];
        }

	}
	
	/* Funcionamento: coloca as arestas do trecho do plasmideo, tenta colocar o maximo possivel de arestas
		originais da solucao e caso a solucao nao fique completa, preenche com arestas quaisquer */
	void atacaSolucao(SolucaoEdgeSet &s) {
		uf.clear();
		SolucaoEdgeSet nova;
		nova = s; 
		int contEdges = 0;
		// s.printSolucao();
		// cout<<"s OWA = "<<s.getOWA()<<endl;
		// coloca as arestas do trecho selecionado
		FOR(i,0,tamTrecho) {
			nova.edges[contEdges][0] = trechoInserir[i][0];
			nova.edges[contEdges++][1] = trechoInserir[i][1];
			uf.unionClass(trechoInserir[i][0],trechoInserir[i][1]);
		}
		// tenta colocar as arestas da solucao
		FOR(i,0,numerovertices-1) {
			if (!uf.sameClass(s.edges[i][0],s.edges[i][1])) {
				nova.edges[contEdges][0] = s.edges[i][0];
				nova.edges[contEdges++][1] = s.edges[i][1];
				uf.unionClass(s.edges[i][0],s.edges[i][1]);
			}
		}
		while (contEdges < numerovertices-1) {
			int e[2] = { rg->IRandom(0,numerovertices-1), rg->IRandom(0,numerovertices-1) };
			if (uf.sameClass(e[0],e[1])) continue;
			if (e[0]<e[1]){
				nova.edges[contEdges][0] = e[0];
				nova.edges[contEdges++][1] = e[1];
			} else {
				nova.edges[contEdges][0] = e[1];
				nova.edges[contEdges++][1] = e[0];
			}
			uf.unionClass(e[0],e[1]);
		}
		nova.calcularObjetivos();
		s = nova;
		
	}
	// após o ataque, deve-se calcular o OWA


	/*IDEIA DE PLASMIDEO:
	tome dois endossimbiontes (A e B)
	O plasmideo P será tal que P = (A | B) - (A & B) NAO FORME CICLO
	Inspiraçao: compor um plasmideo cuja informaçao genética una 
	arestas que, possivelmente, ainda nao se uniram pra formar uma mesma arvore 
	@param tam é o tamanho maximo do plasmideo*/
	void geraPlasTwoSolutions(SolucaoEdgeSet &s1, SolucaoEdgeSet &s2, int tam){

		int amostral[2*1000][2];
		int sizeAmostral = 0;
		bool ha = false;
		for (int i=0; i<numerovertices-1; i++){
			ha = false;
			for(int j=0; j<numerovertices-1 && ha==false; j++) ha = (s1.edges[i][0]==s2.edges[j][0] && s1.edges[i][1]==s2.edges[j][1]) || (s1.edges[i][1]==s2.edges[j][0] && s1.edges[i][0]==s2.edges[j][1]);
			if (ha==false){
				amostral[sizeAmostral  ][0] = s1.edges[i][0];
				amostral[sizeAmostral++][1] = s1.edges[i][1];
			}
		}

		for (int i=0; i<numerovertices-1; i++){
			ha = false;
			for(int j=0; j<numerovertices-1 && ha==false; j++) ha = (s2.edges[i][0]==s1.edges[j][0] && s2.edges[i][1]==s1.edges[j][1]) || (s2.edges[i][1]==s1.edges[j][0] && s2.edges[i][0]==s1.edges[j][1]);
			if (ha==false){
				amostral[sizeAmostral  ][0] = s2.edges[i][0];
				amostral[sizeAmostral++][1] = s2.edges[i][1];
			}
		}
		UnionFind uf;
		uf.clear();
		if (sizeAmostral>tam){ //numerovertices-1
			tamTrecho=0;
			int cont=0;
			while (tamTrecho<tam && cont<sizeAmostral){
				int index = rg->IRandom(0,sizeAmostral-1);
				if (uf.sameClass(amostral[index][0],amostral[index][1])==false){
					uf.unionClass(amostral[index][0],amostral[index][1]);
					trechoInserir [tamTrecho  ][0] = amostral[index][0];
					trechoInserir [tamTrecho++][1] = amostral[index][1];
				}
				cont++;
			}
		} else {
			tamTrecho = 0;
			for (int i=0; i<sizeAmostral; i++){
				if (uf.sameClass(amostral[i][0],amostral[i][1])==false){
					uf.unionClass(amostral[i][0],amostral[i][1]);
					trechoInserir [tamTrecho  ][0] = amostral[i][0];
					trechoInserir [tamTrecho++][1] = amostral[i][1];
				}
			}
		}
	}
};

#endif
