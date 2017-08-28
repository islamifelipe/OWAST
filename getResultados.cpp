
/*Este programa lê o aquivo saida de uma instância 
e retorna os resultados desejados :

nós		gap 	obj		tempo*/


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
	double nos, obj, gap, timee;
	 string s, aux;
	 while (cin>>s){
	 	if (s=="Explored"){
	 		cin>>nos;
	 	}
	 	if (s=="iterations)"){
			string a;
			cin>>a;
			cin>>timee;
	 	}
	 	if (s=="objective" && aux=="Best"){
	 		cin>>obj;
	 		string a,b,c, d, e;
	 		cin>>a;
	 		cin>>b;
	 		cin>>c;
	 		cin>>d;
	 		cin>>e;
	 		//cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
	 		cin>>gap;
	 	}
	 	aux = s;
    }
    cout<<nos<<" "<<gap<<" "<<obj<<" "<<timee<<endl;
}
