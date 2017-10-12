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
#include <fstream>      // std::ifstream 
#include <time.h>       /* time */

#include "rmcPrim.cpp"
#include "SolucaoEdgeSet.cpp"
#include "popInicial.cpp"
#include "vetoresDirecao.cpp"
//#include "tabuSearch.cpp"
#include "simulatedannealing.cpp"

using namespace std;

//double custos[NUMOBJETIVOS][NUMEROVERTICES][NUMEROVERTICES];
//double w[NUMOBJETIVOS];  // pesos OWA

double ***custos;
double *w;  // pesos OWA
SolucaoEdgeSet *populacao[TAMANHOPOPULACAO];
SolucaoEdgeSet *Q[TAMANHOPOPULACAO*2];
//double vetoresDirecoes[NUMDIRECOES][NUMOBJETIVOS];
double **vetoresDirecoes;
double thetaM; // é o maior ângulo entre dois vetores adjacentes, para todos os vetores direcoes
// thetaM DEVE SER CALCULADO NO MOMENTO QUE OS VETORES SAO DETERMINADOS
int contaRenovacao =0;
std::vector<double> otimos;  // guarda os otimos a cada geraçao
std::vector<double> temposOtimos;  // guarda o tempo (decorrido desde o inicio) em que a soluçao i foi atingida
int contCrossovers; // quantidade de crossovers executados
int contMutacoes; // quantidade de mutaçoes executadas
int contSucessoCrossovers; // quantidade de crossovers com sucesso (individuos melhores que os pais)
int contSucessoMutacoes; // quantidade de mutaçoes com sucesso (individuos melhores que o anterior sem mutaçao)
int contSucessoSA; // quantidade de vezes em que o SA retornou uma soluçao melhor
int contQuantCalculouFitness; // guarda a quantidade de vezes em que a funçao calculaOwa foi invocada
int quantSAinvocado; // quantidade de vezes em que o SA foi invocado



//parametros proIrace
int numgeracoes;
double taxamutacao;
double taxacruzamento;
double temperatura;
double taxadecaimento;
double iteracao;
double taxadecaimentoIteracao;

int numobjetivos;
int numerovertices;
int numdirecoes;


struct tms tempoAntes, tempoDepois, tempoDepois222;


void input(const char *instanceName){
        std::ifstream inn;
        inn.open(instanceName, std::ifstream::in);
        inn>>numerovertices;
        inn>>numobjetivos;
        custos = new double**[numobjetivos];
        for (int i=0; i<numobjetivos; i++){
        	custos[i] = new double*[numerovertices];
        	for (int j=0; j<numerovertices; j++){
        		custos[i][j] = new double[numerovertices];
        	}
        }
        w = new double[numobjetivos];
        numdirecoes = ((numobjetivos*K_LAYER*(K_LAYER+3))/2+1);
        vetoresDirecoes = new double*[numdirecoes];
        for (int i=0; i<numdirecoes; i++){
        	vetoresDirecoes[i] = new double[numobjetivos];
        }
        for (int i=0; i<numobjetivos; i++){
                inn>>w[i];
        }
        int org, dest;
        for (int i=0;i<numerovertices-1;i++) {
                for (int j=i+1;j<numerovertices;j++) {
                        inn>>org;
                        inn>>dest;
                        if (org!=i) cout<<"ERRO Leitura 1"<<endl;
                        if (dest!=j) cout<<"ERRO Leitura 2"<<endl;
                        for (int ob = 0; ob<numobjetivos; ob++){
                                inn>>custos[ob][i][j];
                                custos[ob][j][i] = custos[ob][i][j];
                        }
                }
        }
}


void setOtimo(SolucaoEdgeSet * otimo){

	double valorOtimo = otimo->getOWA();
	int index = -1;
	for (int i=0; i<TAMANHOPOPULACAO; i++){
		if (populacao[i]->getOWA()<valorOtimo){
			valorOtimo = populacao[i]->getOWA();
			index = i;
		}
	}
	if (index!=-1) *otimo = *populacao[index];
}



bool comparae2 (SolucaoEdgeSet *s1, SolucaoEdgeSet *s2) { 
	return s1->getOWA()<s2->getOWA(); //|| (s1->getOWA()==s2->getOWA()));// && s1->fitness<s2->fitness);
	
} 
    
/*As soluçoes de elite sao aqueals de melhor fitess*/
void Environment_Selection2(SolucaoEdgeSet *novaPop[TAMANHOPOPULACAO]){
	std::vector<SolucaoEdgeSet *> uniao;
	for (int oeir=0; oeir<TAMANHOPOPULACAO; oeir++) uniao.push_back(populacao[oeir]);
	for (int oeir=0; oeir<TAMANHOPOPULACAO; oeir++) uniao.push_back(novaPop[oeir]);
	
	std::sort (uniao.begin(), uniao.end(), comparae2);
	for (int i=0; i<TAMANHOPOPULACAO; i++) *populacao[i]  = *uniao[i];

	// std::vector<SolucaoEdgeSet *> uniao;
	// for (int oeir=0; oeir<TAMANHOPOPULACAO; oeir++) uniao.push_back(populacao[oeir]);
	// for (int oeir=0; oeir<TAMANHOPOPULACAO; oeir++) uniao.push_back(novaPop[oeir]);
		
	// std::sort (uniao.begin(), uniao.end(), comparae2);
	
	// *populacao[0]  = *uniao[0];
	// int  cont=1;
	// for (int i=1; cont<TAMANHOPOPULACAO/3 && i<uniao.size(); i++) {
	// 	if (abs(populacao[cont-1]->getOWA()-uniao[i]->getOWA())>EPS){
	// 		*populacao[cont++]  = *uniao[i];
	// 	}
	// }
	// //cout<<"cont = "<<cont<<endl;
	// for (int i=1; cont<TAMANHOPOPULACAO && i<uniao.size(); i++){
	// 	*populacao[cont++]  = *uniao[i];
	// }

}

SolucaoEdgeSet * memetic(TRandomMersenne &rg){

	contCrossovers = 0; 
	contMutacoes = 0; 
	contSucessoCrossovers = 0;
	contSucessoMutacoes = 0;
	contSucessoSA = 0; 
	contQuantCalculouFitness = 0;
	quantSAinvocado = 0;

	SolucaoEdgeSet * otimo = new SolucaoEdgeSet(numerovertices-1, rg); //poderia ser global, pra otimizar;
	// SolucaoEdgeSet * pai = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	// SolucaoEdgeSet * mae = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	SolucaoEdgeSet * filho = new SolucaoEdgeSet(numerovertices-1, rg); //poderia ser global, pra otimizar;
	int pai, mae;		
	Reference_Generation(vetoresDirecoes,thetaM);
	alocaPopulacao(populacao, rg); // aloca populaçao inicial
	gerarPopulacao3(populacao, rg,vetoresDirecoes); // gera populaçao inicial
	*otimo = *populacao[0];
	int p1,p2,p3,p4;
	double otimoAntes = otimo->getOWA();
	int contSemMudanca = 0;
	SolucaoEdgeSet *novaPop[TAMANHOPOPULACAO]; // cria-se uma populaçao de descentes
	alocaPopulacao(novaPop, rg); 
	//for (int i=0; i<TAMANHOPOPULACAO*2; i++) Q[i] = new SolucaoEdgeSet(NUMEROVERTICES-1, rg);
	
	
	for (int i=0; i<numgeracoes; i++){ // para cada geraçao...
		
		setOtimo(otimo);
		otimos.push_back(otimo->getOWA());
		times(&tempoDepois222);
		temposOtimos.push_back((double) (tempoDepois222.tms_utime - tempoAntes.tms_utime) / 100.0);
		if (otimoAntes == otimo->getOWA()){
			contSemMudanca++;
		} else {
			otimoAntes = otimo->getOWA();
			contSemMudanca=0;
		}
		if (contSemMudanca==5){
			contaRenovacao++;
			for (int i=0; i<TAMANHOPOPULACAO/2; i++) {
				int idfjifj  = rg.IRandom(0,TAMANHOPOPULACAO-1);
				rmcPrim(*filho, w, rg);
				filho->calculaOwa(w);
				*populacao[idfjifj] = *filho;
				
			}
			for (int i=0; i<TAMANHOPOPULACAO/3; i++){
				int idfjifj  = rg.IRandom(0,TAMANHOPOPULACAO-1);
				filho->mutacao(*otimo);
				filho->calculaOwa(w);
				*populacao[idfjifj] = *filho;
			}
			contSemMudanca=0;
		}
		// for (int aap = 0; aap<TAMANHOPOPULACAO; aap++){
		// 	cout<<populacao[aap]->getOWA()<<endl;
		// }
		//cout<<"Geracao "<<i+1<<" otimo = "<<otimo->getOWA()<<endl;
		for (int j=0; j<TAMANHOPOPULACAO; j++){ // deve-se criar TAMANHOPOPULACAO novos individuos

			/*SORTEIA 4 individuos*/
			/*Faz-se o torneio binario entre eles*/
			p1 = rg.IRandom(0, TAMANHOPOPULACAO-1);
			p2 = rg.IRandom(0, TAMANHOPOPULACAO-1);
			p3 = rg.IRandom(0, TAMANHOPOPULACAO-1);
			p4 = rg.IRandom(0, TAMANHOPOPULACAO-1);

			if(populacao[p1]->getOWA()<populacao[p2]->getOWA()){
				pai = p1;;
			} else {
				pai = p2;
			}
			if (populacao[p3]->getOWA()<populacao[p4]->getOWA()){
				mae = p3;
			} else {
				mae = p4;
			}

			double p = rg.Random();
			if (p<taxacruzamento){
				filho->crossover(*populacao[pai], *populacao[mae]);
				filho->calculaOwa(w);
				if (filho->getOWA()<populacao[pai]->getOWA() || filho->getOWA()<populacao[mae]->getOWA()) contSucessoCrossovers++;
			} else {
				filho->doRandomWalk();
				filho->calculaOwa(w);
			}
			if (filho->getOWA()<otimo->getOWA()) *otimo = *filho;
			// filho foi definido; Agora aplica-se mutaçao
			p = rg.Random();
			if (p<taxamutacao){
				novaPop[j]->mutacao(*filho);
				novaPop[j]->calculaOwa(w); // necessario
				if (novaPop[j]->getOWA() < filho->getOWA()) contSucessoMutacoes++;
			} else{
				filho->calculaOwa(w);
				*novaPop[j] = *filho;
			}
			double fitsss = novaPop[j]->getOWA();
			SA(*novaPop[j], rg);
			if (novaPop[j]->getOWA()<fitsss) contSucessoSA++;
		}
		Environment_Selection2(novaPop); // o vetor populacao[..] tará as malhores solucoes encontras

	}

	return otimo;

}
int main(int argc, char *argv[]){
        char *instanceName = NULL;
        for (int i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-TAXADECRUZAMENTO") == 0) {
                        taxacruzamento = atof(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-TAXADEMUTACAO") == 0) {
                        taxamutacao = atof(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-TEMPERATURA") == 0) {
                        temperatura = atof(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-FATORDECAIMENTO") == 0) {
                        taxadecaimento = atof(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-ITERACAO_K") == 0) {
                        iteracao = atoi(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-FATORDECAIMENTOITERACAO") == 0) {
                        taxadecaimentoIteracao = atof(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-QUANTGERACOES") == 0) {
                        numgeracoes = atoi(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-instance") == 0 || strcmp(argv[i], "-i") == 0) {
                        instanceName = argv[i+1];
                        i++;
                }
        }

        TRandomMersenne rg( time(NULL) );//6041901  ); //48594589849

        input(instanceName);

        times(&tempoAntes);

        SolucaoEdgeSet *otimo  = memetic(rg);

        times(&tempoDepois);

        cout<<otimo->getOWA()<<endl;
        return 0;
}
                          