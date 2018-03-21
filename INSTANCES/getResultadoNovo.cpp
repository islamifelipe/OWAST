
/*Este programa lê o aquivo saida de uma instância do solver
e retorna os resultados desejados :

nós		gap 	obj		tempo*/
#include <iomanip>      // std::setprecision

#include <iostream>
#include <vector> 
#include <string>
#include <climits>
#include <stack>   
#include <utility>      // std::pair
#include <cmath>
#include <list>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>     /* srand, rand */
#include <fstream>      // std::ifstream
#include <cmath>
#include <stdio.h>
using namespace std;

struct modelo
{
	double ub; // mesmo valor o z
	double lb;
	double timee;
	double nos;
};

int corr_contBestLB_GS = 0;
int corr_contBestLB_FER1 = 0;
int corr_contBestLB_FER2 = 0;


int anticorr_contBestLB_GS = 0;
int anticorr_contBestLB_FER1 = 0;
int anticorr_contBestLB_FER2 = 0;

#define PRECISAO 1.00e-01//0.001//0.00001
bool equalfloat(double a, double b){
	return abs(a-b)<=PRECISAO;
	
}

bool maiorQuefloat(double a, double b){ //retorna true se a>b
	return a-b>PRECISAO;
}

bool maiorIgualQuefloat(double a, double b){ //returna true se a>=b
	return maiorQuefloat(a, b)||equalfloat(a, b);	
}

std::ifstream innn;
void leeer(struct modelo &model){
	double obj, gap, lb, timee, nos;
	 string s, aux;
	 while (innn>>s){
	 	if (s=="Explored"){
	 		innn>>nos;
	 	}
	 	if (s=="iterations)"){
			string a;
			innn>>a;
			innn>>timee;
	 	}
	 	if (s=="objective" && aux=="Best"){
	 		innn>>obj;
	 		string a,b,c, d, e;
	 		innn>>a;
	 		innn>>b;
	 		innn>>c;
	 		innn>>lb;
	 		innn>>d;
	 		innn>>e;
	 		// cout<<a<<" "<<b<<" "<<c<<" "<<" "<<lb<<" "<<d<<" "<<e<<endl;
	 		innn>>gap;
	 	}
	 	aux = s;
    }
    model.lb = lb;
    model.ub = obj;
    model.timee = timee;
    model.nos = nos;
}



// void contt(bool corr, int i){
// 	if (corr==true){
// 		if (i==1){
// 			corr_contBestLB_GS++;
// 		} else if (i==2){
// 			corr_contBestLB_FER1++;
// 		} else if (i==3){
// 			corr_contBestLB_FER2++;
// 		}
// 	}else {
// 		if (i==1){
// 			anticorr_contBestLB_GS++;
// 		} else if (i==2){
// 			anticorr_contBestLB_FER1++;
// 		} else if (i==3){
// 			anticorr_contBestLB_FER2++;
// 		}
// 	}
// }

void printLinha(struct modelo gs, struct modelo fer1, struct modelo fer2, bool corr){

	// cout<<gs.lb<<" "<<fer1.lb<<" "<<fer2.lb<<endl;
	double maiorLB = 0;
	double vet[3] = {gs.lb, fer1.lb, fer2.lb};
	for (int i=0; i<3; i++){
		if (maiorQuefloat(vet[i],maiorLB)==true) maiorLB = vet[i];
	}
	// cout<<"maiorLB = "<<maiorLB<<endl;
	if (maiorLB>0){
		printf("%.2f_{", maiorLB);
		// cout<<maiorLB<<"_{";
		for (int i=0; i<3; i++){
			if (equalfloat(vet[i],maiorLB)==true) {
				// contt(corr, i+1);
				cout<<i+1;
			}
		}
		cout<<"}"<<",";
	} else {
		cout<<"--"<<",";
	}
	if(gs.timee<3600) printf("%.2fs,", gs.timee); //cout<<gs.timee<<"s"<<",";
	else if (maiorQuefloat(maiorLB,0)==false) cout<<"--"<<",";
	else {
		if  (gs.ub>0) printf("%.2f%%,", 100*(gs.ub - maiorLB)/maiorLB); //cout<<100*(gs.ub - maiorLB)/maiorLB<<"%"<<",";
		else cout<<"--"<<",";
	}
	if (gs.ub>0) printf("%.2f,", gs.ub);//cout<<gs.ub<<",";
	else cout<<"--"<<",";

	if(fer1.timee<3600) printf("%.2fs,",fer1.timee);//cout<<fer1.timee<<"s"<<",";
	else if (maiorQuefloat(maiorLB,0)==false) cout<<"--"<<",";
	else {
		if (fer1.ub>0) printf("%.2f%%,", 100*(fer1.ub - maiorLB)/maiorLB); //cout<<100*(fer1.ub - maiorLB)/maiorLB<<"%"<<",";
		else cout<<"--"<<",";
	}
	if (fer1.ub>0) printf("%.2f,",fer1.ub);//cout<<fer1.ub<<",";
	else cout<<"--"<<",";

	if(fer2.timee<3600) printf("%.2fs,",fer2.timee); //cout<<fer2.timee<<"s"<<",";
	else if (maiorQuefloat(maiorLB,0)==false) cout<<"--"<<",";
	else {
		if (fer2.ub>0) printf("%.2f%%,",100*(fer2.ub - maiorLB)/maiorLB); //cout<<100*(fer2.ub - maiorLB)/maiorLB<<"%"<<",";
		else cout<<"--"<<",";
	}
	if (fer2.ub>0) printf("%.2f,", fer2.ub);///cout<<fer2.ub<<",";
	else cout<<"--"<<",";

}

int main(int argc, const char * argv[]){
	struct modelo gs = {0,0,0};
	struct modelo fer1 = {0,0,0};
	struct modelo fer2 = {0,0,0};
	innn.open(argv[1], std::ifstream::in);
	leeer(gs);
	innn.close();
	innn.open(argv[2], std::ifstream::in);
	leeer(fer1);
	innn.close();
	innn.open(argv[3], std::ifstream::in);
	leeer(fer2);
	innn.close();

	printLinha(gs, fer1, fer2, true);



	struct modelo antigs = {0,0,0};
	struct modelo antifer1 = {0,0,0};
	struct modelo antifer2 = {0,0,0};
	innn.open(argv[4], std::ifstream::in);
	leeer(antigs);
	innn.close();
	innn.open(argv[5], std::ifstream::in);
	leeer(antifer1);
	innn.close();
	innn.open(argv[6], std::ifstream::in);
	leeer(antifer2);
	innn.close();

	printLinha(antigs, antifer1, antifer2, false);

	cout<<endl;

	// cout<<gs.lb<<" "<<gs.ub<<" "<<gs.timee<<" "<<gs.nos<<endl;
	// cout<<fer1.lb<<" "<<fer1.ub<<" "<<fer1.timee<<" "<<fer1.nos<<endl;
	// cout<<fer2.lb<<" "<<fer2.ub<<" "<<fer2.timee<<" "<<fer2.nos<<endl;
	
}
