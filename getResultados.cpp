
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
using namespace std;

std::ifstream innn;
void leeer(){
	double nos, obj, gap, timee;
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
	 		innn>>d;
	 		innn>>e;
	 		//cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
	 		innn>>gap;
	 	}
	 	aux = s;
    }
   cout<<nos<<",";
    if (timee>=3600){ 
    	
    	cout<<gap<<"% "<<","<<obj<<",";;
    }
    else {
    	cout<<timee<<"s "<<","<<obj<<",";;
	}
}


int main(int argc, const char * argv[]){
	innn.open(argv[1], std::ifstream::in);
	leeer();
	innn.close();
	innn.open(argv[2], std::ifstream::in);
	leeer();
	innn.close();
	innn.open(argv[3], std::ifstream::in);
	leeer();
	innn.close();
	innn.open(argv[4], std::ifstream::in);
	leeer();
	innn.close();
	innn.open(argv[5], std::ifstream::in);
	leeer();
	innn.close();
	innn.open(argv[6], std::ifstream::in);
	leeer();
	cout<<endl;
}
