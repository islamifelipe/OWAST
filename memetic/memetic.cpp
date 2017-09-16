#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sys/times.h>
#include <sys/types.h>
#include <iostream>

#include "rmcPrim.cpp"
#include "SolucaoEdgeSet.cpp"
#include "popInicial.cpp"
#include "vetoresDirecao.cpp"
#include "tabuSearch.cpp"
#include "simulatedannealing.cpp"
using namespace std;

double custos[NUMOBJETIVOS][NUMEROVERTICES][NUMEROVERTICES];
double w[NUMOBJETIVOS];  // pesos OWA
SolucaoEdgeSet *populacao[TAMANHOPOPULACAO];
double vetoresDirecoes[NUMDIRECOES][NUMOBJETIVOS];

void input(){
	int n,p; // esta leitura de n e p é somente para cumprir o formato da instância. Os valores de fato estao em param.h
	cin>>n;
	cin>>p;
	for (int i=0; i<NUMOBJETIVOS; i++){
		cin>>w[i];
	}
	int org, dest;
	for (int i=0;i<NUMEROVERTICES-1;i++) {
		for (int j=i+1;j<NUMEROVERTICES;j++) {
			cin>>org;
			cin>>dest;
			if (org!=i) cout<<"ERRO Leitura 1"<<endl;
			if (dest!=j) cout<<"ERRO Leitura 2"<<endl;
			for (int ob = 0; ob<NUMOBJETIVOS; ob++){
				cin>>custos[ob][i][j];
				custos[ob][j][i] = custos[ob][i][j];
			}
		}
	}
}

int main(){

	input(); // ler instância
	TRandomMersenne rg( 45458992 );
	Reference_Generation(vetoresDirecoes);
	alocaPopulacao(populacao, rg); // aloca populaçao inicial
	gerarPopulacao2(populacao, rg,vetoresDirecoes); // gera populaçao inicial


	SolucaoEdgeSet *nova = new SolucaoEdgeSet(NUMEROVERTICES-1, rg);
	populacao[0]->printSolucao();
	cout<<"OWA pai = "<<populacao[0]->getOWA()<<endl;
	cout<<endl;
	populacao[5]->printSolucao();
	cout<<"OWA pai = "<<populacao[5]->getOWA()<<endl;
	cout<<endl;
	nova->crossover(*populacao[0], *populacao[5]);
	nova->printSolucao();
	nova->calculaOwa(w);
	cout<<"OWA NOVA = "<<nova->getOWA()<<endl;
	cout<<endl;
	SA(*populacao[5], rg);
	populacao[5]->printSolucao();
	cout<<"OWA populacao[5] = "<<populacao[5]->getOWA()<<endl;
	populacao[5]->calculaOwa(w);
	cout<<"OWA populacao[5] RECALCULADO = "<<populacao[5]->getOWA()<<endl;
	
	// cout<<endl;
	// int a1 = rg.IRandom(0,NUMEROVERTICES-1-1), a2;
	// while ((a2 = rg.IRandom(0,NUMEROVERTICES-1-1)) == a1);
	// viz->trocaArestas(a1,a2,viz->calcularTrocaArestas(a1,a2,*nova),*nova);
	// cout<<"Troca as arestas "<<a1<<" "<<a2<<endl;
	// viz->printSolucao();
	// viz->calculaOwa(w);
	// cout<<"OWA NOVA = "<<viz->getOWA()<<endl;

}