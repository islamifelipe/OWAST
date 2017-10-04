
/*Este programa lê o aquivo saida de uma instância do MT
e retorna os resultados desejados :

tempo até atingir o otimo*/


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
	// FILE * entrada = fopen (argv[1], "r");

	// if (entrada==NULL) return 1;
	 //char  buffer[1026];
	double obj, ant, tem;
	 string s, aux;
	 double objBu, tempo;
	 while (cin>>s){
	 	if (s=="tempo(s)):"){
	 		for (int i=0; i<51; i++){
	 			cin>>obj;
	 			cin>>aux; //,
	 			cin>>tem;
	 			//cout<<obj<<" "<<tem<<endl;
	 			cin>>aux; // s
	 			if (i>0){
	 				if (ant!=obj){
	 					objBu = obj;
	 					tempo = tem;
	 				}
	 			} else{
	 				objBu = obj;
	 				tempo = tem;
	 			}
	 			ant = obj;
	 		}	
	 		
	 		break;
	 	}
    }
   // cout<<nos<<","<<gap<<","<<obj<<","<<timee<<endl;
    cout<<tempo<<endl;
}
