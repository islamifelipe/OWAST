#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sys/times.h>
#include <sys/types.h>
#include <iostream>

#include "SolucaoEdgeSet.cpp"
using namespace std;

double custos[NUMOBJETIVOS][NUMEROVERTICES][NUMEROVERTICES];
double w[NUMOBJETIVOS];  // pesos OWA

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
			}
		}
	}
}

int main(){

	input(); // ler instância
	TRandomMersenne rg( 39495849 );
	// cout<<NUMEROVERTICES<<" "<<NUMOBJETIVOS<<endl;
	for (int i=0;i<NUMOBJETIVOS; i++){
		cout<<w[i]<<" ";
	}
	cout<<endl;
	// for (int i=0;i<NUMEROVERTICES-1;i++) {
	// 	for (int j=i+1;j<NUMEROVERTICES;j++) {
	// 		cout<<i<<" "<<j<<" ";
	// 		for (int ob = 0; ob<NUMOBJETIVOS; ob++){
	// 			cout<<custos[ob][i][j]<<" ";
	// 		}
	// 		cout<<endl;
	// 	}
	// }

	for (int i=0; i<10; i++){
		SolucaoEdgeSet *novo = new SolucaoEdgeSet(NUMEROVERTICES-1, rg);
		novo->doRandomWalk();
		novo->printSolucao();
		cout<<"OWA =  "<<novo->getOwa(w)<<endl;
		cout<<endl;
	}

}