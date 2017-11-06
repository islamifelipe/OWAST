/*Este programa lê o aquivo saida de uma instância do MT
e retorna os resultados desejados :

Quantidade de vezes em que a populaçao precisou ser renovada
ou taxa de sucesso do crossover
ou taxa de sucesso da mutaçao
ou taxa de sucesso do SA
ou quantidade de avaliaçoes da funçao objetivo*/


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
using namespace std;


int main(int argc, const char * argv[]){
	
	double val;
	int cont =0;
	string aux, s;
	 while (cin>>s){
	 	if (s=="avaliado"){ cont++;
	 	}
	 	if (cont==1) {
	 		cin>>aux;
	 		cin>>val;
	 		//cout<<val<<endl;
	 		break;
	 	}
    }
   // cout<<nos<<","<<gap<<","<<obj<<","<<timee<<endl;
    cout<<val<<endl;
}
