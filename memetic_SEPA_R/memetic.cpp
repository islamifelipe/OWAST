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
	return s1->getOWA()<s2->getOWA();// || (s1->getOWA()==s2->getOWA() && s1->fitness<s2->fitness);
	// if (s1->getOWA()<s2->getOWA()) return true;
	// else  if (s1->getOWA()==s2->getOWA()){
	// 	return s1->fitness<s2->fitness;
	// } else return false;
} //  crescente
    
/*As soluçoes de elite sao aqueals de melhor fitess*/
void Environment_Selection2(){
	std::vector<SolucaoEdgeSet *> uniao;
	for (int i=0; i<TAMANHOPOPULACAO*2; i++) {
		uniao.push_back(Q[i]);
	}
	std::sort (uniao.begin(), uniao.end(), comparae2);
	cout<<"union[0] = "<<uniao[0]->getOWA()<<endl;
	for (int i=0; i<TAMANHOPOPULACAO; i++) *populacao[i]  = *uniao[i];

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
			Q[p]->f_normalized[i] = (Q[p]->getObj(i) - ideal[i])/(pior[i]- ideal[i]); /// TUDO : +1 ? 
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

	SolucaoEdgeSet * otimo = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	SolucaoEdgeSet * pai = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	SolucaoEdgeSet * mae = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
	SolucaoEdgeSet * filho = new SolucaoEdgeSet(NUMEROVERTICES-1, rg); //poderia ser global, pra otimizar;
			
	Reference_Generation(vetoresDirecoes,thetaM);
	alocaPopulacao(populacao, rg); // aloca populaçao inicial
	gerarPopulacao1(populacao, rg); // gera populaçao inicial
	*otimo = *populacao[0];
	int p1,p2,p3,p4;
	double otimoAntes = otimo->getOWA();
	int contSemMudanca = 0;
	SolucaoEdgeSet *novaPop[TAMANHOPOPULACAO]; // cria-se uma populaçao de descentes
	alocaPopulacao(novaPop, rg); 
	for (int i=0; i<TAMANHOPOPULACAO*2; i++) Q[i] = new SolucaoEdgeSet(NUMEROVERTICES-1, rg);
	
	
	for (int i=0; i<QUANTGERACOES; i++){ // para cada geraçao...
		
		setOtimo(otimo);
		// if (otimoAntes == otimo->getOWA()){
		// 	contSemMudanca++;
		// } else {
		// 	otimoAntes = otimo->getOWA();
		// 	contSemMudanca=0;
		// }
		// if (contSemMudanca==5){
		// 	gerarPopulacao1(populacao, rg); 
		// 	contSemMudanca=0;
		// }
		cout<<"Geraçao "<<i+1<<"  Otimo = "<<otimo->getOWA()<<endl;
		// for (int ppp=0; ppp<TAMANHOPOPULACAO; ppp++){
		// 	cout<<"\t"<<populacao[ppp]->getOWA()<<" ---- "<<populacao[ppp]->fitness<<endl;
		// }
		cout<<"\n"<<endl;
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
			// filho foi definido; Agora aplica-se mutaçao
			p = rg.Random();
			if (p<TAXADEMUTACAO){
				novaPop[j]->mutacao(*filho);
				novaPop[j]->calculaOwa(w); // necessario
			} else{
				filho->calculaOwa(w); // TODO : talvez desnecessario!!!
				*novaPop[j] = *filho;
			}
			SA(*novaPop[j], rg);
		}
		for (int oeir=0; oeir<TAMANHOPOPULACAO; oeir++) *Q[oeir] = *populacao[oeir];
		for (int oeir=0, conttt=TAMANHOPOPULACAO; oeir<TAMANHOPOPULACAO; oeir++, conttt++) *Q[conttt] = *novaPop[oeir];
		Objective_Normalization();
		Associate();
		Fitness_Assignment();
		Environment_Selection2(); // o vetor populacao[..] tará as malhores solucoes encontras

	}

	return otimo;

}

int main(){

	input(); // ler instância
	TRandomMersenne rg( 309405904950 );
	
	// Reference_Generation(vetoresDirecoes, thetaM);
	// alocaPopulacao(populacao, rg); // aloca populaçao inicial
	// gerarPopulacao1(populacao, rg); // gera populaçao inicial
	//cout<<"thetaM = "<<thetaM<<endl;
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

	SolucaoEdgeSet *otimo  = memetic(rg);
	otimo->printSolucao();
	cout<<"OWA = "<<otimo->getOWA()<<endl;

}