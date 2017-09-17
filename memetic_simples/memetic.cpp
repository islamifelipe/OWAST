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

void setOtimo(SolucaoEdgeSet * otimo){
	for (int i=0; i<TAMANHOPOPULACAO; i++){
		if (populacao[i]->getOWA()<otimo->getOWA()) otimo = populacao[i];
	}
}



bool comparae (SolucaoEdgeSet *s1, SolucaoEdgeSet *s2) { return (s1->getOWA()<s2->getOWA()); } //  crescente
    
/*As soluçoes de elite sao aqueals de melhor fitess*/
void getlite(SolucaoEdgeSet *novaPop[TAMANHOPOPULACAO]){
	std::vector<SolucaoEdgeSet *> uniao;
	for (int i=0; i<TAMANHOPOPULACAO; i++) {
		uniao.push_back(populacao[i]);
		uniao.push_back(novaPop[i]);
	}
	std::sort (uniao.begin(), uniao.end(), comparae);
	for (int i=0; i<TAMANHOPOPULACAO; i++) populacao[i]  = uniao[i];

}

SolucaoEdgeSet * memetic(TRandomMersenne &rg){

	SolucaoEdgeSet * otimo = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	SolucaoEdgeSet * pai = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	SolucaoEdgeSet * mae = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	SolucaoEdgeSet * filho = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
			
	//Reference_Generation(vetoresDirecoes);
	alocaPopulacao(populacao, rg); // aloca populaçao inicial
	gerarPopulacao1(populacao, rg); // gera populaçao inicial
	otimo = populacao[0];
	int p1,p2,p3,p4;

	SolucaoEdgeSet *novaPop[TAMANHOPOPULACAO]; // cria-se uma populaçao de descentes
	alocaPopulacao(novaPop, rg); // aloca populaçao inicial
	
	for (int i=0; i<QUANTGERACOES; i++){ // para cada geraçao...
		setOtimo(otimo);
		cout<<"Geraçao "<<i+1<<endl;
		for (int j=0; j<TAMANHOPOPULACAO; j++){ // deve-se criar TAMANHOPOPULACAO novos individuos

			/*SORTEIA 4 individuos*/
			/*Faz-se o torneio binario entre eles*/
			p1 = rg.IRandom(0, TAMANHOPOPULACAO-1);
			p2 = rg.IRandom(0, TAMANHOPOPULACAO-1);
			p3 = rg.IRandom(0, TAMANHOPOPULACAO-1);
			p4 = rg.IRandom(0, TAMANHOPOPULACAO-1);

			if(populacao[p1]->getOWA()<populacao[p2]->getOWA()){
				*pai = *populacao[p1];
			} else {
				*pai = *populacao[p2];
			}
			if (populacao[p3]->getOWA()<populacao[p4]->getOWA()){
				*mae = *populacao[p3];
			} else {
				*mae = *populacao[p4];
			}

			double p = rg.Random();
			if (p<TAXADECRUZAMENTO){
				filho->crossover(*pai, *mae);
			} else { // se nao cruzar, o filho fica sendo o pai ou o mae (o melhor)
				if (pai->getOWA()<mae->getOWA()){
					*filho = *pai;
				}else {
					*filho = *mae;
				}
			}
			filho->calculaOwa(w); // TODO : talvez desnecessario!!!
			// filho foi definido; Agora aplica-se mutaçao
			p = rg.Random();
			if (p<TAXADEMUTACAO){
				novaPop[j]->mutacao(*filho);
				novaPop[j]->calculaOwa(w); // necessario
			} else{
				*novaPop[j] = *filho;
			}
			SA(*novaPop[j], rg);
		}
		getlite(novaPop); // o vetor populacao[..] tará as malhores solucoes encontras
	}

	return otimo;

}

int main(){

	input(); // ler instância
	TRandomMersenne rg( 45458992 );

	// Reference_Generation(vetoresDirecoes);
	// alocaPopulacao(populacao, rg); // aloca populaçao inicial
	// gerarPopulacao2(populacao, rg,vetoresDirecoes); // gera populaçao inicial
	
	// SolucaoEdgeSet *nova = new SolucaoEdgeSet(NUMEROVERTICES-1, rg);
	// populacao[0]->printSolucao();
	// cout<<"OWA pai = "<<populacao[0]->getOWA()<<endl;
	// cout<<endl;
	// populacao[5]->printSolucao();
	// cout<<"OWA pai = "<<populacao[5]->getOWA()<<endl;
	// cout<<endl;
	// nova->crossover(*populacao[0], *populacao[5]);
	// nova->printSolucao();
	// nova->calculaOwa(w);
	// cout<<"OWA NOVA = "<<nova->getOWA()<<endl;

	SolucaoEdgeSet *otimo  = memetic(rg);
	otimo->printSolucao();
	cout<<"OWA = "<<otimo->getOWA()<<endl;

}