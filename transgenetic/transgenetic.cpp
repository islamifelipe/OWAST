#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sys/times.h>
#include <sys/types.h>
#include <iostream>
#include <math.h>       /* acos, cos */
#include <climits>

#include "rmcPrim.cpp"
#include "SolucaoEdgeSet.cpp"
#include "popInicial.cpp"
#include "vetoresDirecao.cpp"
#include "simulatedannealing.cpp"
#include "Plasmideo.cpp"

using namespace std;

double custos[NUMOBJETIVOS][NUMEROVERTICES][NUMEROVERTICES];
double w[NUMOBJETIVOS];  // pesos OWA
SolucaoEdgeSet *populacao[TAMANHOPOPULACAO];
SolucaoEdgeSet *Q[TAMANHOPOPULACAO*2];
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
		if (populacao[i]->getOWA()<otimo->getOWA()) *otimo = *populacao[i];
	}
}



bool comparae2 (SolucaoEdgeSet *s1, SolucaoEdgeSet *s2) { 
	return s1->getOWA()<s2->getOWA(); //|| (s1->getOWA()==s2->getOWA()));// && s1->fitness<s2->fitness);
	
} //  crescente
    
/*As soluçoes de elite sao aqueals de melhor fitess*/
void Environment_Selection2(SolucaoEdgeSet *novaPop[TAMANHOPOPULACAO]){
	std::vector<SolucaoEdgeSet *> uniao;
	for (int oeir=0; oeir<TAMANHOPOPULACAO; oeir++) uniao.push_back(populacao[oeir]);
	for (int oeir=0; oeir<TAMANHOPOPULACAO; oeir++) uniao.push_back(novaPop[oeir]);
		

	// for (int i=0; i<TAMANHOPOPULACAO*2; i++) {
	// 	uniao.push_back(Q[i]);
	// }
	std::sort (uniao.begin(), uniao.end(), comparae2);
	//cout<<"union[0] = "<<uniao[0]->getOWA()<<endl;
	for (int i=0; i<TAMANHOPOPULACAO; i++) *populacao[i]  = *uniao[i];
	

}

int main(){

	input(); // ler instância
	TRandomMersenne rg( 309405904950 ); //48594589849
	
	Reference_Generation(vetoresDirecoes);
	alocaPopulacao(populacao, rg); // aloca populaçao inicial
	gerarPopulacao3(populacao, rg,vetoresDirecoes);//cout<<"thetaM = "<<thetaM<<endl;
	// for (int i=0; i<TAMANHOPOPULACAO; i++){
	// 	for (int j=0; j<TAMANHOPOPULACAO; j++){
	// 		if (*populacao[i]>>*populacao[j]){
	// 			for (int o=0; o<NUMOBJETIVOS; o++){
	// 				cout<<populacao[i]->getObj(o)<<" ";
	// 			}
	// 			cout<<"   DOMINA   ";
	// 			for (int o=0; o<NUMOBJETIVOS; o++){
	// 				cout<<populacao[j]->getObj(o)<<" ";
	// 			}
	// 			cout<<"\n"<<endl;
	// 		}
	// 	}
	// }
	



	// Objective_Normalization();
	// for (int i=0; i<TAMANHOPOPULACAO; i++){
	// 	for (int o=0; o<NUMOBJETIVOS; o++) {
	// 		cout<<populacao[i]->getObj(o)<<" ";
	// 	}
	// 	cout<<"  ----->  ";
	// 	for (int o=0; o<NUMOBJETIVOS; o++) {
	// 		cout<<populacao[i]->f_normalized[o]<<" ";
	// 	}
	// 	cout<<endl;
	// }
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
	
	int index = rg.IRandom(0,TAMANHOPOPULACAO-1);
	int index2 = rg.IRandom(0,NUMDIRECOES-1);
	cout<<"Individuo "<<index+1<<endl;
	populacao[index]->printSolucao();
	cout<<"OWA = "<<populacao[index]->getOWA()<<endl;
	Plasmideo plas(&rg);
	int tam  =rg.IRandom(2,8);
	double lambda[NUMOBJETIVOS];
	for (int ll=0; ll<NUMOBJETIVOS; ll++){
		lambda[ll] =  vetoresDirecoes[index2][ll];
	} 
	plas.geraPlasm_rmcPrim(lambda, tam);
	cout<<"Plamideo de tamanho "<<tam<<endl;
	SolucaoEdgeSet nova = *populacao[index];
	plas.atacaSolucao(nova);
	cout<<endl;
	nova.printSolucao();
	cout<<"OWA = "<<nova.getOWA()<<endl;
	if(nova.getOWA()<populacao[index]->getOWA()){
		cout<<"ATAQUE BEM SUCEDIDO!"<<endl;
	}


	// int index = rg.IRandom(0,TAMANHOPOPULACAO-1);
	// cout<<"Individuo "<<index+1<<endl;
	// populacao[index]->printSolucao();
	// SolucaoEdgeSet *nova = new SolucaoEdgeSet(NUMEROVERTICES-1, rg);
	// rmcPrim(*nova,vetoresDirecoes[43],rg, 4);
	// cout<<endl;
	// nova->printSolucao();

	
	// cout<<TAMANHOPOPULACAO<<endl;
	// SolucaoEdgeSet *otimo  = memetic(rg);
	// otimo->printSolucao();
	// cout<<"OWA = "<<otimo->getOWA()<<endl;

}