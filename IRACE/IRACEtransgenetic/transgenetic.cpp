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
#include "simulatedannealing.cpp"
#include "Plasmideo.cpp"
#include "primTransposon.cpp"

using namespace std;

double ***custos; //[NUMOBJETIVOS][NUMEROVERTICES][NUMEROVERTICES];
double *w; //[NUMOBJETIVOS];  // pesos OWA
SolucaoEdgeSet *populacao[TAMANHOPOPULACAO];
SolucaoEdgeSet *repositorio[TAMANHOREPOSITORIO];
int sizeRepositorio; // no maximo TAMANHOREPOSITORIO
double **vetoresDirecoes;//[NUMDIRECOES][NUMOBJETIVOS];

std::vector<double> otimos;  // guarda os otimos a cada geraçao
std::vector<double> temposOtimos;  // guarda o tempo (decorrido desde o inicio) em que a soluçao i foi atingida
int quantPlas1; // quantidade de plas1;
int quantPlas2; // quantidade de plas2;
int quantPlas3; // quantidade de plas3;
int contPlasm1; // conta quantas vezes o plasmideo rmc-prim tenta atacar
int contSucessoPlasm1; // conta quantos sucessos o plasm1 teve em atacar
int contPlasm2; // conta quantas vezes o plasmideo "de uma soluçao" tenta atacar
int contSucessoPlasm2; // conta quantos sucessos o plasm2 teve em atacar
int contPlasm3; // conta quantas vezes o plasmideo "de duas soluçoes" tenta atacar
int contSucessoPlasm3; // conta quantos sucessos o plasm3 teve em atacar
int contPrimTrans; // conta a quantidade e vezes em que o primTrans tenta atacar
int contSucessPrimTrans; // conta a quantidade de sucesso que o primTrans obteve
int contSucessoSA; // quantidade de vezes em que o SA retornou uma soluçao melhor (trans2)
int contQuantCalculouFitness; // guarda a quantidade de vezes em que a funçao calculaOwa foi invocada
int quantSAinvocado; // quantidade de vezes em que o SA (trans2) foi invocado

struct tms tempoAntes, tempoDepois, tempoDepois222;


int numplasmideos;
int per_plas1;
int per_plas2;
int per_plas3;
double pro_trans1;
double pro_trans2;
double temperatura;
double taxadecaimento;
double iteracao;
double taxadecaimentoIteracao;
int numgeracoes;

int numobjetivos;
int numerovertices;
int numdirecoes;


void contSucessPlas(int index){
	if (index>=0 && index<quantPlas1) contSucessoPlasm1++;
	else if (index>=quantPlas1 && index<quantPlas2+quantPlas1) contSucessoPlasm2++;
	else contSucessoPlasm3++;
}

void contAtaquePlas(int index){
	if (index>=0 && index<quantPlas1) contPlasm1++;
	else if (index>=quantPlas1 && index<quantPlas2+quantPlas1) contPlasm2++;
	else contPlasm3++;
}

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
	if (index!=-1) {
		*otimo = *populacao[index];
	}
}

void getLambda(double lambda[10], TRandomMersenne &rg){
	int op = rg.IRandom(0,4);
	int index2, k, lim;
	double alfa[6] = {0.2, 0.3, 0.4, 0.6, 0.7, 0.8};
	switch(op){
		case 0: // vetores do SPEA/R
			index2 = rg.IRandom(0,numdirecoes-1);
			for (int ll=0; ll<numobjetivos; ll++) lambda[ll] =  vetoresDirecoes[index2][ll];
			break;
		case 1: // vetor do k-centrum
			k = rg.IRandom(1,numobjetivos);
			for (int ll=0; ll<k; ll++)lambda[ll] = 1.0/k;
			for (int ll=k; ll<numobjetivos; ll++) lambda[ll] = 0;
			break;
		case 2: // vetor do k-trimmed
			lim = (int) numobjetivos/2-1;
			if (lim==0) lim = 1;
			k = rg.IRandom(1,lim);
			for (int i=0; i<k; i++) lambda[i] = 0;
			for (int i=k; i<numobjetivos-k; i++) lambda[i] = 1.0/(numobjetivos-(2.0*k));
			for (int i=numobjetivos-k; i<numobjetivos; i++)lambda[i] = 0;
			break;
		case 3: // vetor do Hurwicz
			index2 = rg.IRandom(0,5);
			lambda[0] = alfa[index2];
			lambda[numobjetivos-1] = 1.0 - alfa[index2];
			for (int ll=1; ll<numobjetivos-1; ll++)lambda[ll] = 0;
			break;
		default: // vetor w (argumento da instância)
			for (int ll=0; ll<numobjetivos; ll++)lambda[ll] =  w[ll];
			break;

	}
}

void criaPlasmideos(TRandomMersenne &rg, Plasmideo *pl){
	for (int i=0;i<numplasmideos;i++)
		pl[i].setRandom(&rg);
	double lambda[10];
	quantPlas1 = (int) per_plas1*numplasmideos/100;
	quantPlas2 = (int) per_plas2*numplasmideos/100;
	quantPlas3 = (int) per_plas3*numplasmideos/100;
	if (quantPlas1+quantPlas2+quantPlas3==numplasmideos-1)quantPlas3++;
	int tam, cont=0, index2, index3;
	for (int i=0; i<quantPlas1 && cont<numplasmideos; i++){
		tam =rg.IRandom(2,(int)(0.5*(numerovertices-1)));// NOTAR: DIFERENTE DE SILVIA
		getLambda(lambda, rg);
		pl[cont].geraPlasm_rmcPrim(lambda, tam);
		cont++;
	}
	for (int i=0; i<quantPlas2 && cont<numplasmideos; i++){
		index2 = rg.IRandom(0,sizeRepositorio-1);
		tam =rg.IRandom(2,(int)(0.5*(numerovertices-1)));// NOTAR: DIFERENTE DE SILVIA
		pl[cont].geraPlasm_Solucao(*repositorio[index2], tam);
		cont++;
	}
	for (int i=0; i<quantPlas3 && cont<numplasmideos; i++){
		index3 = rg.IRandom(0,sizeRepositorio-1);
		index2 = rg.IRandom(0,sizeRepositorio-1);
		tam =rg.IRandom(2,(int)(0.5*(numerovertices-1))); // NOTAR: DIFERENTE DE SILVIA
		pl[cont].geraPlasTwoSolutions(*repositorio[index2], *repositorio[index3], tam);
		cont++;
	}	
}

/* O ótimo corrente deve sempre ser atacado
  O ótimo corrente deve sempre fornecer genes pra (pelo menos) um plasmideo
	Os demais podem ser aleatorios (mas devem constar)
  
	CRIAR UMA LISTA (REPOSITORIO) COM AS INFORMACOES GENETICAS
	TAL REPOSITORIO É VAZIO INICIALMENTE
	ELE SERÁ PREENCHIDO COM UMA **COPIA** DOS ENDOSSIMBIONTES
	UM ENDOSSIMBIONTE DA **POPULACAO** É ESCOLHIDO PARA SER ATACADO
		(1) CASO O ATAQUE FUNCIONE, TAL  ENDOSSIMBIONTE DA **POPULACAO** É MODIFICADO
		E UMA COPIA DO SEU MATERIAL GENÉTICO É INSERIDO NO REPOSITORIO	
  */

void addRepositorio(TRandomMersenne &rg, SolucaoEdgeSet *novaS){
	if (sizeRepositorio<TAMANHOREPOSITORIO){
		repositorio[sizeRepositorio] = new SolucaoEdgeSet(numerovertices-1,rg);
		*repositorio[sizeRepositorio++] = *novaS; 
	}else{
		double max = INT_MIN;
		int index = -1;
		for (int i=0; i<sizeRepositorio; i++){
			if (repositorio[i]->getOWA()>max){
				max = repositorio[i]->getOWA();
				index = i;
			}
		}
		//int index = rg.IRandom(0,sizeRepositorio-1);
		if (novaS->getOWA()<max)
			*repositorio[index] = *novaS;
	}
}

/*ataca todos da populao, inclusive o otimo*/
SolucaoEdgeSet *transgenetic(TRandomMersenne &rg){
	SolucaoEdgeSet * otimo = new SolucaoEdgeSet(numerovertices-1, rg); //poderia ser global, pra otimizar;
	sizeRepositorio = 0;
	Reference_Generation(vetoresDirecoes);
	alocaPopulacao(populacao, rg); // aloca populaçao inicial
	gerarPopulacao3(populacao, rg,vetoresDirecoes);//cout<<"thetaM = "<<thetaM<<endl;
	for (int i=0; i<TAMANHOPOPULACAO; i++) addRepositorio(rg, populacao[i]);
	*otimo = *populacao[0];
	int indexPlas;
	double p;
	PrimTransposon ptrans(&rg); // nao precisa ser redeclarado a cada iteraçao!!!
	for (int i=0; i<numgeracoes; i++){ // para cada geraçao...
		setOtimo(otimo);
		otimos.push_back(otimo->getOWA());
		times(&tempoDepois222);
		temposOtimos.push_back((double) (tempoDepois222.tms_utime - tempoAntes.tms_utime) / 100.0);
		//cria os PLASMIDEOS
		Plasmideo *pl = new Plasmideo[numplasmideos];
		criaPlasmideos(rg, pl);
		for (int plas = 0; plas<numplasmideos; plas++){
			SolucaoEdgeSet copia;
			copia = *otimo;//*populacao[index];
			pl[plas].atacaSolucao(copia);
			contAtaquePlas(plas);
			copia.calculaOwa(w);
			if(copia.getOWA()<otimo->getOWA()){
				addRepositorio(rg, otimo);
				contSucessPlas(plas);
				*otimo = copia;
			}
		}
		//cout<<"Geracao "<<i+1<<" otimo = "<<otimo->getOWA()<<endl;
		for (int pppt = 0; pppt < TAMANHOPOPULACAO; pppt++){
			indexPlas = rg.IRandom(0,numplasmideos-1);
			SolucaoEdgeSet copia;
			copia = *populacao[pppt];//*populacao[index];
			pl[indexPlas].atacaSolucao(copia);
			contAtaquePlas(indexPlas);
			copia.calculaOwa(w);
			if(copia.getOWA()<populacao[pppt]->getOWA()){
				addRepositorio(rg, populacao[pppt]);
				contSucessPlas(indexPlas);
				*populacao[pppt] = copia;
			}
			p = rg.Random();
			if (p<pro_trans1){
				copia = *populacao[pppt];
				double lambda[10];
				getLambda(lambda, rg);
				ptrans.atacaSolucao(copia,lambda);
				copia.calculaOwa(w);
				if (copia.getOWA()<populacao[pppt]->getOWA()){
					//cout<<"OWA = "<<populacao[s1]->getOWA()<<endl;
					addRepositorio(rg, populacao[pppt]);
					*populacao[pppt] = copia;
					contSucessPrimTrans++;
				
				}
			}
			p = rg.Random();
			if (p<pro_trans2){
				double fitg = populacao[pppt]->getOWA();
				addRepositorio(rg, populacao[pppt]);
				SA(*populacao[pppt], rg);
				if (populacao[pppt]->getOWA()<fitg) contSucessoSA++;
			}

		}
	}

	return otimo;
}


int main(int argc, char *argv[]){
        char *instanceName = NULL;

        for (int i = 1; i < argc; i++) {
                if (strcmp(argv[i], "-NUMPLASMIDEOS") == 0) {
                        numplasmideos = atoi(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-PER_PLAS1") == 0) {
                        per_plas1 = atoi(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-PER_PLAS2") == 0) {
                        per_plas2 = atoi(argv[i+1]);
                        i++;
                }
                // if (strcmp(argv[i], "-PER_PLAS3") == 0) {
                //         per_plas3 = atoi(argv[i+1]);
                //         i++; // definido como a diferença entre per_plas1 e per_plas2
                // }
                if (strcmp(argv[i], "-PROB_TRANS2") == 0) {
                        pro_trans2 = atof(argv[i+1]);
                        i++;
                }
                if (strcmp(argv[i], "-PROB_TRANS1") == 0) {
                        pro_trans1 = atof(argv[i+1]);
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

  //       numplasmideos = NUMPLASMIDEOS;
		//per_plas1 = 100;
		//  per_plas2 = 0;
		// // pro_trans1 = PROB_TRANS1;
		//  pro_trans2 = PROB_TRANS2;
		//  temperatura = TEMPERATURA;
		//  taxadecaimento = FATORDECAIMENTO;
		//  iteracao = ITERACAO_K;
		//  taxadecaimentoIteracao = FATORDECAIMENTOITERACAO;
		//  numgeracoes = 50;
       per_plas3 = 100 - per_plas1 - per_plas2;
        TRandomMersenne rg( time(NULL) );//6041901 time(NULL) ); //48594589849

        input(instanceName);

        SolucaoEdgeSet *otimo  = transgenetic(rg);


        cout<<otimo->getOWA()<<endl;
        return 0;
}
        