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
#include "primTransposon.cpp"
// #include "kruskalTransposon.cpp"

using namespace std;

double custos[NUMOBJETIVOS][NUMEROVERTICES][NUMEROVERTICES];
double w[NUMOBJETIVOS];  // pesos OWA
SolucaoEdgeSet *populacao[TAMANHOPOPULACAO];
SolucaoEdgeSet *repositorio[TAMANHOREPOSITORIO];
int sizeRepositorio; // no maximo TAMANHOREPOSITORIO
double vetoresDirecoes[NUMDIRECOES][NUMOBJETIVOS];

std::vector<double> otimos;  // guarda os otimos a cada geraçao
std::vector<double> temposOtimos;  // guarda o tempo (decorrido desde o inicio) em que a soluçao i foi atingida
int quantPlas1; // quantidade de plas1;
int quantPlas2; // quantidade de plas2;
int quantPlas3; // quantidade de plas3;
int contPlasm1; // conta quantas vezes o plasmideo rmc-prim tenta atacar
int contSucessoPlasm1 = 0; // conta quantos sucessos o plasm1 teve em atacar
float sumMelhoriaPlasm1 = 0; // conta o quanto o plasm1 melhora
int contPlasm2 = 0; // conta quantas vezes o plasmideo "de uma soluçao" tenta atacar
int contSucessoPlasm2= 0; // conta quantos sucessos o plasm2 teve em atacar
float sumMelhoriaPlasm2= 0; // conta o quanto o plasm2 melhora
int contPlasm3= 0; // conta quantas vezes o plasmideo "de duas soluçoes" tenta atacar
int contSucessoPlasm3= 0; // conta quantos sucessos o plasm3 teve em atacar
float sumMelhoriaPlasm3= 0; // conta o quanto o plasm3 melhora
int contPrimTrans= 0; // conta a quantidade e vezes em que o primTrans tenta atacar
int contSucessPrimTrans= 0; // conta a quantidade de sucesso que o primTrans obteve
float sumMelhoriaPrimTrans= 0; // conta o quanto o PrimTrans melhora
int contSucessoSA= 0; // quantidade de vezes em que o SA retornou uma soluçao melhor (trans2)
int contQuantCalculouFitness= 0; // guarda a quantidade de vezes em que a funçao calculaOwa foi invocada
float sumMelhoriaSA= 0; // conta o quanto o SA melhora
int quantSAinvocado= 0; // quantidade de vezes em que o SA (trans2) foi invocado


struct ordenacao ordenacoes[NUMDIRECOES];

struct tms tempoAntes, tempoDepois, tempoDepois222;


void contSucessPlas(int index, float valor){
	if (index>=0 && index<quantPlas1) {
		contSucessoPlasm1++;
		sumMelhoriaPlasm1+=valor;
	} else if (index>=quantPlas1 && index<quantPlas2+quantPlas1){
		 contSucessoPlasm2++;
		 sumMelhoriaPlasm2+=valor;
	} else {
		contSucessoPlasm3++;
		sumMelhoriaPlasm3+=valor;
	}
}

void contAtaquePlas(int index){
	if (index>=0 && index<quantPlas1) contPlasm1++;
	else if (index>=quantPlas1 && index<quantPlas2+quantPlas1) contPlasm2++;
	else contPlasm3++;
}

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

void getLambda(double lambda[NUMOBJETIVOS]){
	int op = IRandom(0,4);
	int index2, k, lim;
	double alfa[6] = {0.2, 0.3, 0.4, 0.6, 0.7, 0.8};
	switch(op){
		case 0: // vetores do SPEA/R
			index2 = IRandom(0,NUMDIRECOES-1);
			for (int ll=0; ll<NUMOBJETIVOS; ll++) lambda[ll] =  vetoresDirecoes[index2][ll];
			break;
		case 1: // vetor do k-centrum
			k = IRandom(1,NUMOBJETIVOS);
			for (int ll=0; ll<k; ll++)lambda[ll] = 1.0/k;
			for (int ll=k; ll<NUMOBJETIVOS; ll++) lambda[ll] = 0;
			break;
		case 2: // vetor do k-trimmed
			lim = (int) NUMOBJETIVOS/2-1;
			if (lim==0) lim = 1;
			k = IRandom(1,lim);
			for (int i=0; i<k; i++) lambda[i] = 0;
			for (int i=k; i<NUMOBJETIVOS-k; i++) lambda[i] = 1.0/(NUMOBJETIVOS-(2.0*k));
			for (int i=NUMOBJETIVOS-k; i<NUMOBJETIVOS; i++)lambda[i] = 0;
			break;
		case 3: // vetor do Hurwicz
			index2 = IRandom(0,5);
			lambda[0] = alfa[index2];
			lambda[NUMOBJETIVOS-1] = 1.0 - alfa[index2];
			for (int ll=1; ll<NUMOBJETIVOS-1; ll++)lambda[ll] = 0;
			break;
		default: // vetor w (argumento da instância)
			for (int ll=0; ll<NUMOBJETIVOS; ll++)lambda[ll] =  w[ll];
			break;

	}
}

void criaPlasmideos(Plasmideo pl[NUMPLASMIDEOS]){
	// for (int i=0;i<NUMPLASMIDEOS;i++)
	// 	pl[i].setRandom(&rg);
	double lambda[NUMOBJETIVOS];
	quantPlas1 = (int) PER_PLAS1*NUMPLASMIDEOS/100;
	quantPlas2 = (int) PER_PLAS2*NUMPLASMIDEOS/100;
	//quantPlas3 = (int) PER_PLAS3*NUMPLASMIDEOS/100;
	//if (quantPlas1+quantPlas2+quantPlas3==NUMPLASMIDEOS-1)quantPlas3++;
	quantPlas3 = NUMPLASMIDEOS - quantPlas1 -quantPlas2;
	int tam, cont=0, index2, index3;
	for (int i=0; i<quantPlas1 && cont<NUMPLASMIDEOS; i++){
		tam = IRandom(2,(int)(0.5*(NUMEROVERTICES-1)));// NOTAR: DIFERENTE DE SILVIA
		getLambda(lambda);
		pl[cont].geraPlasm_rmcPrim(lambda, tam);
		cont++;
	}
	//cout<<"cont = "<<quantPlas1<<endl;
	for (int i=0; i<quantPlas2 && cont<NUMPLASMIDEOS; i++){
		index2 = IRandom(0,sizeRepositorio-1);
		tam = IRandom(2,(int)(0.5*(NUMEROVERTICES-1)));// NOTAR: DIFERENTE DE SILVIA
		pl[cont].geraPlasm_Solucao(*repositorio[index2], tam);
		cont++;
	}
	//cout<<"cont = "<<quantPlas2<<endl;
	for (int i=0; i<quantPlas3 && cont<NUMPLASMIDEOS; i++){
		index3 = IRandom(0,sizeRepositorio-1);
		index2 = IRandom(0,sizeRepositorio-1);
		tam =IRandom(2,(int)(0.5*(NUMEROVERTICES-1))); // NOTAR: DIFERENTE DE SILVIA
		pl[cont].geraPlasTwoSolutions(*repositorio[index2], *repositorio[index3], tam);
		cont++;
	}	
	//cout<<"cont = "<<quantPlas3<<endl;
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

void addRepositorio( SolucaoEdgeSet *novaS){
	if (sizeRepositorio<TAMANHOREPOSITORIO){
		repositorio[sizeRepositorio] = new SolucaoEdgeSet(NUMEROVERTICES-1);
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


// void calculaOrdenacoes(double vetoresDirecoes[NUMDIRECOES][NUMOBJETIVOS]){
// 	for (int ve = 0; ve<NUMDIRECOES; ve++){
// 		for (int oo=0; oo<NUMOBJETIVOS; oo++) ordenacoes[ve].v_esc[oo] = vetoresDirecoes[ve][oo];
// 		int conttt = 0;
// 		for (int i=0; i<NUMEROVERTICES; i++){
// 			for (int j=i+1; j<NUMEROVERTICES; j++){
// 				double fit = 0;
// 				for (int oo=0; oo<NUMOBJETIVOS; oo++){
// 					fit += ordenacoes[ve].v_esc[oo]*custos[oo][i][j];
// 				}
// 				ordenacoes[ve].arestas[conttt].a = i;
// 				ordenacoes[ve].arestas[conttt].b = j;
// 				ordenacoes[ve].arestas[conttt++].fit = fit;
// 			}
// 		}
// 	}
// }

/*ataca todos da populao, inclusive o otimo*/
SolucaoEdgeSet *transgenetic(){
	SolucaoEdgeSet * otimo = new SolucaoEdgeSet(NUMEROVERTICES-1); //poderia ser global, pra otimizar;
	sizeRepositorio = 0;
	Reference_Generation(vetoresDirecoes);
	alocaPopulacao(populacao); // aloca populaçao inicial
	gerarPopulacao3(populacao, vetoresDirecoes);//cout<<"thetaM = "<<thetaM<<endl;
	// calculaOrdenacoes(vetoresDirecoes);
	for (int i=0; i<TAMANHOPOPULACAO; i++) {
		populacao[i]->isTree();
		addRepositorio(populacao[i]);
	}
	*otimo = *populacao[0];
	int indexPlas;
	double p;
	PrimTransposon ptrans;
	for (int i=0; i<QUANTGERACOES; i++){ // para cada geraçao...
		setOtimo(otimo);
		otimos.push_back(otimo->getOWA());
		times(&tempoDepois222);
		temposOtimos.push_back((double) (tempoDepois222.tms_utime - tempoAntes.tms_utime) / 100.0);
		
		//cria os PLASMIDEOS
		Plasmideo pl[NUMPLASMIDEOS];
		criaPlasmideos(pl);
		for (int plas = 0; plas<NUMPLASMIDEOS; plas++){
			SolucaoEdgeSet copia = *otimo;//*populacao[index];
			pl[plas].atacaSolucao(copia);
			contAtaquePlas(plas);
			copia.calculaOwa(w);
			if(copia.getOWA()<otimo->getOWA()){
				addRepositorio(otimo);
				//copia.isTree();
				contSucessPlas(plas, otimo->getOWA()-copia.getOWA());
				*otimo = copia;
			}
		}
		cout<<"Geracao "<<i+1<<" otimo = "<<otimo->getOWA()<<endl;
		for (int pppt = 0; pppt < TAMANHOPOPULACAO; pppt++){
			indexPlas = IRandom(0,NUMPLASMIDEOS-1);
			SolucaoEdgeSet copia = *populacao[pppt];//*populacao[index];
			pl[indexPlas].atacaSolucao(copia);
			contAtaquePlas(indexPlas);
			copia.calculaOwa(w);
			if(copia.getOWA()<populacao[pppt]->getOWA()){
				addRepositorio(populacao[pppt]);
				contSucessPlas(indexPlas, populacao[pppt]->getOWA()-copia.getOWA());
				*populacao[pppt] = copia;
				populacao[pppt]->isTree();
			}
			p = genrand64_real3();
			if (p<PROB_TRANS1){
				copia = *populacao[pppt];
				double lambda[NUMOBJETIVOS];
				getLambda(lambda);
				ptrans.atacaSolucao(copia,lambda);
				copia.calculaOwa(w);
				if (copia.getOWA()<populacao[pppt]->getOWA()){
					//cout<<"OWA = "<<populacao[s1]->getOWA()<<endl;
					sumMelhoriaPrimTrans += populacao[pppt]->getOWA()-copia.getOWA();
					//cout<<populacao[pppt]->getOWA()<<" ==> "<<copia.getOWA()<<endl;
					
					addRepositorio(populacao[pppt]);
					*populacao[pppt] = copia;
					populacao[pppt]->isTree();
					contSucessPrimTrans++;
					
				}
			}
			p = genrand64_real3();
			if (p<PROB_TRANS2){
				double fitg = populacao[pppt]->getOWA();
				addRepositorio(populacao[pppt]);
				SA(*populacao[pppt]);
				populacao[pppt]->isTree();
				if (populacao[pppt]->getOWA()<fitg) {
					contSucessoSA++;
					//cout<<populacao[pppt]->getOWA()<<" ==> "<<fitg<<endl;
					sumMelhoriaSA += fitg-populacao[pppt]->getOWA();
				}
			}

		}
	}

	return otimo;
}


int main(int argc, char *argv[]){
	int seemente = std::atoi(argv[1]);
	//TRandomMersenne rg(seemente);
	init_genrand64(seemente);
	cout<<"========= Estatisticas ========= "<<endl;
	cout<<"Semente utilizada : "<<seemente<<endl;
	FILE *samplefile = fopen(argv[2],"a");
	FILE *tempofile = fopen(argv[3],"a");
	input(); // ler instância

	times(&tempoAntes);

	SolucaoEdgeSet *otimo = transgenetic();
	// Reference_Generation(vetoresDirecoes);
	// alocaPopulacao(populacao); // aloca populaçao inicial
	// gerarPopulacao3(populacao, vetoresDirecoes);//cout<<"thetaM = "<<thetaM<<endl;

	// struct ordenacao order;
	// getLambda(order.v_esc);
	// int conttt = 0;
	// for (int i=0; i<NUMEROVERTICES; i++){
	// 	for (int j=i+1; j<NUMEROVERTICES; j++){
	// 		double fit = 0;
	// 		for (int oo=0; oo<NUMOBJETIVOS; oo++){
	// 			fit += order.v_esc[oo]*custos[oo][i][j];
	// 		}
	// 		order.arestas[conttt].a = i;
	// 		order.arestas[conttt].b = j;
	// 		order.arestas[conttt++].fit = fit;
	// 	}
	// }

	// int mmm = (NUMEROVERTICES*(NUMEROVERTICES-1))/2;
	// sort(order.arestas, order.arestas+mmm, auxEdgeSetComp);
	// KruskalTransposon transkruskal;
	// int index = IRandom(0, TAMANHOPOPULACAO-1);
	// cout<<populacao[index]->getOWA()<<endl;
	// transkruskal.atacaSolucao(*populacao[index], order);
	// populacao[index]->calculaOwa(w);
	// populacao[index]->isTree();
	// cout<<populacao[index]->getOWA()<<endl;
	// SA(*populacao[index]);
	// cout<<populacao[index]->getOWA()<<endl;
	times(&tempoDepois);

	otimos.push_back(otimo->getOWA());
	temposOtimos.push_back( (double) (tempoDepois.tms_utime - tempoAntes.tms_utime) / 100.0 );

	/*========= Estatistica ========= */
	fprintf(stdout,"Tempo(s) Final = %.2lf\n", (double) (tempoDepois.tms_utime - tempoAntes.tms_utime) / 100.0 );
	fprintf(tempofile,"%.2lf\n", (double) (tempoDepois.tms_utime - tempoAntes.tms_utime) / 100.0 );

	cout<<"Quantidade de geraçoes = "<<QUANTGERACOES<<endl;
   	cout<<"Quantidade de plasm1 = "<<quantPlas1<<endl;
   	cout<<"Quantidade de plasm2 = "<<quantPlas2<<endl;
   	cout<<"Quantidade de plasm3 = "<<quantPlas3<<endl;
   	cout<<"Quantidade de ataques do plasm1 = "<<contPlasm1<<endl;
   	cout<<"Quantidade de sucesso do plasm1 = "<<contSucessoPlasm1<<endl;
   	cout<<"Taxa de sucesso do plasm1 = "<<(double)contSucessoPlasm1/contPlasm1<<endl;
   	cout<<"Média de melhoria do plasm1 = "<<(contPlasm1==0?0:(float)sumMelhoriaPlasm1/contPlasm1)<<endl;;
   	cout<<"Quantidade de ataques do plasm2 = "<<contPlasm2<<endl;
   	cout<<"Quantidade de sucesso do plasm2 = "<<contSucessoPlasm2<<endl;
   	cout<<"Taxa de sucesso do plasm2 = "<<(double)contSucessoPlasm2/contPlasm2<<endl;
   	cout<<"Média de melhoria do plasm2 = "<<(contPlasm2==0?0:(float)sumMelhoriaPlasm2/contPlasm2)<<endl;;
   	cout<<"Quantidade de ataques do plasm3 = "<<contPlasm3<<endl;
   	cout<<"Quantidade de sucesso do plasm3 = "<<contSucessoPlasm3<<endl;
   	cout<<"Taxa de sucesso do plasm3 = "<<(double)contSucessoPlasm3/contPlasm3<<endl;
   	cout<<"Média de melhoria do plasm3 = "<<(contPlasm3==0?0:(float)sumMelhoriaPlasm3/contPlasm3)<<endl;;
   	cout<<"Quantidade de ataque do primTrans = "<<contPrimTrans<<endl;
   	cout<<"Quantidade de sucesso do primTrans = "<<contSucessPrimTrans<<endl;
   	cout<<"Taxa de sucesso do primTrans = "<<(double)contSucessPrimTrans/contPrimTrans<<endl;
   	cout<<"Média de melhoria do primTrans = "<<(contPrimTrans==0?0:(float)sumMelhoriaPrimTrans/contPrimTrans)<<endl;;
  	cout<<"Quantidade de ataques do saTrans = "<<quantSAinvocado<<endl;
   	cout<<"Quantidade de sucesso do saTrans = "<<contSucessoSA<<endl;
   	cout<<"Taxa de sucesso do saTrans = "<<(double)contSucessoSA/quantSAinvocado<<endl;
  	cout<<"Média de melhoria do saTrans = "<<(quantSAinvocado==0?0:(float)sumMelhoriaSA/quantSAinvocado)<<endl;;
  	cout<<"Quantidade de vezes em que o fitness foi avaliado = "<<contQuantCalculouFitness<<endl;


	cout<<"Evolucao do otimo por geracao (fitness, tempo(s)): "<<endl;
   	for (int i=0; i<otimos.size(); i++){
   		cout<<otimos[i]<<", "<<temposOtimos[i]<<"s"<<endl;
   	}

   	cout<<endl;
   	cout<<"Soluçao encontrada: "<<endl;
	otimo->printSolucao();
	cout<<"OWA = "<<otimo->getOWA()<<endl;
	fprintf(samplefile,"%.2lf\n",otimo->getOWA());
   	

	fclose(samplefile);
	fclose(tempofile);

}