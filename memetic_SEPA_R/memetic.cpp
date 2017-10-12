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
#include "tabuSearch.cpp"
#include "simulatedannealing.cpp"

using namespace std;

double custos[NUMOBJETIVOS][NUMEROVERTICES][NUMEROVERTICES];
double w[NUMOBJETIVOS];  // pesos OWA
SolucaoEdgeSet *populacao[TAMANHOPOPULACAO];
SolucaoEdgeSet *Q[TAMANHOPOPULACAO*2];
double vetoresDirecoes[NUMDIRECOES][NUMOBJETIVOS];
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

struct tms tempoAntes, tempoDepois, tempoDepois222;

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
	if (index!=-1) *otimo = *populacao[index];
}



bool comparae (SolucaoEdgeSet *s1, SolucaoEdgeSet *s2) { return (s1->fitness<s2->fitness); } //  crescente
    

void Environment_Selection(){
	
	std::vector<SolucaoEdgeSet * > regiao[NUMDIRECOES] ; // regiao[i] --> conjunto de soluçoes da regiao i

	for (int i=0; i<NUMDIRECOES; i++){
		for (int q = 0; q<TAMANHOPOPULACAO*2; q++){
			if (Q[q]->index_subregiao == i){
				regiao[i].push_back(Q[q]);
			}
		}
	}
	
	int cont = 0; // deve serr menor que TAMANHOPOPULACAO
	while (cont<TAMANHOPOPULACAO){
		std::vector<SolucaoEdgeSet*> H;
		for (int i=0; i<NUMDIRECOES; i++){ // pega o individuo de menor fitness da regiao i
			int q_index_menor = -1;
			double fitnesss = INT_MAX;
			for (int q = 0; q<regiao[i].size(); q++){
				if (regiao[i][q]->fitness < INT_MAX) {
					q_index_menor = q;
					fitnesss= regiao[i][q]->fitness;
				}
			}
			// encontramos o individuo de menor fitness na regiao i
			if (q_index_menor!=-1){
				H.push_back(regiao[i][q_index_menor]);
				//regiao[i][q_index_menor]->fitness = INT_MAX;
				regiao[i].erase(regiao[i].begin()+q_index_menor);
			}
		}
		if (cont+H.size()<TAMANHOPOPULACAO){
			for (int i=0; i<H.size(); i++){
				*populacao[cont++] = *H[i];
			}
		} else {
			std::sort (H.begin(), H.end(), comparae);
			for (int i=0; i<H.size() && cont<TAMANHOPOPULACAO; i++){
				*populacao[cont++] = *H[i];
			}
		}
	}
	
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

void Objective_Normalization(){
	double ideal[NUMOBJETIVOS];
	double pior[NUMOBJETIVOS];
	for (int i=0; i<NUMOBJETIVOS; i++){ // pega o i-ésimo melhor e pior objetivos
		ideal[i] = Q[0]->getObj(i);
		pior[i] = Q[0]->getObj(i);
		for (int p=0; p<TAMANHOPOPULACAO*2; p++){
			if (Q[p]->getObj(i)<ideal[i]) ideal[i] = Q[p]->getObj(i);
			if (Q[p]->getObj(i)>pior[i]) pior[i] = Q[p]->getObj(i);
		}
	}

	for (int p=0; p<TAMANHOPOPULACAO*2; p++){
		for (int i=0; i<NUMOBJETIVOS; i++){
			Q[p]->f_normalized[i] = (Q[p]->getObj(i) - ideal[i])/(pior[i]- ideal[i]); /// TODO : +1 ? 
		}
	}
}

void Associate() {
	for (int q=0; q<TAMANHOPOPULACAO*2; q++){ //para o individuo q em Q ...
		double minAngulo = INT_MAX;
		int indexw = 0;
		for (int w = 0; w<NUMDIRECOES; w++){  // olha-se o ângulo de cada vetor e pega-se o menor
			double produtoInterno = 0;
			double normaSol = 0;
			double normaDirecao = 0;
			for (int j=0; j<NUMOBJETIVOS; j++){
				produtoInterno += Q[q]->f_normalized[j]*vetoresDirecoes[w][j];
				normaSol += Q[q]->f_normalized[j]*Q[q]->f_normalized[j];
				normaDirecao += vetoresDirecoes[w][j]*vetoresDirecoes[w][j];
			}
			normaSol = sqrt(normaSol);
			normaDirecao = sqrt(normaDirecao);
			// acos dá o ângulo do arco-cosceno em radianos. Transformamos pra graus
			double angulo = acos (produtoInterno/(normaDirecao*normaSol)) * (180.0 / PI);
			//cout<<"\tângulo vetor "<<w<<" = "<<angulo<<endl;
			if (angulo<minAngulo){
				minAngulo = angulo;
				indexw = w;
			}
		}
		Q[q]->theta_angulo = minAngulo;
		Q[q]->index_subregiao = indexw;
		//cout<<"Menor  = "<<Q[q]->theta_angulo<<" regiao : "<<Q[q]->index_subregiao<<endl;
	}
}

void Fitness_Assignment(){
	int S[TAMANHOPOPULACAO*2];
	for (int a=0; a<TAMANHOPOPULACAO*2; a++){ // primeiro calcula-se S(a);
		int sumSa = 0;
	 	for (int q2=0; q2<TAMANHOPOPULACAO*2; q2++){
			if (a!=q2 && Q[q2]->index_subregiao == Q[a]->index_subregiao && *Q[a]>>*Q[q2]){
				sumSa++;
			}
		}
		S[a] = sumSa;	
	}


	for (int a=0; a<TAMANHOPOPULACAO*2; a++){// calcula-se fitnesss
		
		int Ra = 0;
		for (int b=0; b<TAMANHOPOPULACAO*2; b++){
			if (a!=b && Q[a]->index_subregiao == Q[b]->index_subregiao && *Q[b]>>*Q[a]){
				Ra += S[b];
			}
		}

		double Da = Q[a]->theta_angulo/(thetaM+Q[a]->theta_angulo);
		double fitnesss_local = Da + Ra;
		double fitnesss = fitnesss_local;//+Q[a]->getOWA();
		Q[a]->fitness = fitnesss;
		//cout<<"fitess local de "<<a<<" = "<<fitnesss_local<<"  --- fitnesss global = "<<Q[a]->fitness<<"    ---- OWA = "<<Q[a]->getOWA()<<endl;

	}
}

SolucaoEdgeSet * memetic(TRandomMersenne &rg){

	contCrossovers = 0; 
	contMutacoes = 0; 
	contSucessoCrossovers = 0;
	contSucessoMutacoes = 0;
	contSucessoSA = 0; 
	contQuantCalculouFitness = 0;
	quantSAinvocado = 0;

	SolucaoEdgeSet * otimo = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	// SolucaoEdgeSet * pai = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	// SolucaoEdgeSet * mae = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	SolucaoEdgeSet * filho = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
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
	
	
	for (int i=0; i<QUANTGERACOES; i++){ // para cada geraçao...
		
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
		cout<<"Geracao "<<i+1<<" otimo = "<<otimo->getOWA()<<endl;
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
			if (p<TAXADECRUZAMENTO){
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
			if (p<TAXADEMUTACAO){
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
	int seemente = std::atoi(argv[1]);
	TRandomMersenne rg(seemente);
	cout<<"========= Estatisticas ========= "<<endl;
	cout<<"Semente utilizada : "<<seemente<<endl;
	FILE *samplefile = fopen(argv[2],"a");
	FILE *tempofile = fopen(argv[3],"a");
	input(); // ler instância
	// TRandomMersenne rg( 309405904950 ); //48594589849
	
	/* CALCULA O TEMPO */
	
	times(&tempoAntes);

	SolucaoEdgeSet *otimo  = memetic(rg);

	times(&tempoDepois);

	otimos.push_back(otimo->getOWA());
	temposOtimos.push_back( (double) (tempoDepois.tms_utime - tempoAntes.tms_utime) / 100.0 );

	/*========= Estatistica ========= */
	fprintf(stdout,"Tempo(s) Final = %.2lf\n", (double) (tempoDepois.tms_utime - tempoAntes.tms_utime) / 100.0 );
	fprintf(tempofile,"%.2lf\n", (double) (tempoDepois.tms_utime - tempoAntes.tms_utime) / 100.0 );
   	cout<<"Quantidade de geraçoes = "<<QUANTGERACOES<<endl;
   	cout<<"Quantas vezes em que a populaçao foi renovada = "<<contaRenovacao<<endl;
   	cout<<"Quantidade de crossovers = "<<contCrossovers<<endl;
   	cout<<"Quantidade de sucesso dos crossovers = "<<contSucessoCrossovers<<endl;
   	cout<<"Taxa de sucesso dos crossovers = "<<(double)contSucessoCrossovers/contCrossovers<<endl;
   	cout<<"Quantidade de mutaçoes = "<<contMutacoes<<endl;
   	cout<<"Quantidade de sucesso da mutaçao = "<<contSucessoMutacoes<<endl;
   	cout<<"Taxa de sucesso das mutaçoes = "<<(double)contSucessoMutacoes/contMutacoes<<endl;
   	cout<<"Quantidade de vezes em que o SA foi invocado = "<<quantSAinvocado<<endl;
   	cout<<"Quantidade de sucesso do SA = "<<contSucessoSA<<endl;
   	cout<<"TAXA de sucesso do SA = "<<(double)contSucessoSA/quantSAinvocado<<endl;
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