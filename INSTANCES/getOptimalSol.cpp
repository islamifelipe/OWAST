/* Este programa ler uma tabela em modo texto csv (sem cabeçalho) e computa o %OptimalSol 

Formato da saida:

		correlated					       anticorrelated
	GS		FER1	FER2				GS		FER1	FER2

*/

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
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;

std::ifstream innn;

int contOpt_GS_corr = 0;
int contOpt_FER1_corr = 0;
int contOpt_FER2_corr = 0;

int contOpt_GS_anticorr = 0;
int contOpt_FER1_anticorr = 0;
int contOpt_FER2_anticorr = 0;

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


int main(int argc, const char * argv[]){
	
	innn.open(argv[1], std::ifstream::in);

	string linha;
	while (innn>>linha){
		
		// /cout<<linha<<endl;
		std::vector<string> tokens = split(linha, ',');
		if ( tokens[2].compare("--")!=0 && tokens[2].find("%")==string::npos){
			contOpt_GS_corr++;
		}
		if (tokens[4].compare("--")!=0 && tokens[4].find("%")==string::npos){
			contOpt_FER1_corr++;
		}
		if (tokens[6].compare("--")!=0 && tokens[6].find("%")==string::npos){
			contOpt_FER2_corr++;
		}


		if (tokens[9].compare("--")!=0 && tokens[9].find("%")==string::npos){
			contOpt_GS_anticorr++;
		}
		if (tokens[11].compare("--")!=0 && tokens[11].find("%")==string::npos){
			contOpt_FER1_anticorr++;
		}
		if (tokens[13].compare("--")!=0 && tokens[13].find("%")==string::npos){
			contOpt_FER2_anticorr++;
		}
	}

	cout<<(float) contOpt_GS_corr*100/54.0<<" "<<(float)contOpt_FER1_corr*100/54<<" "<<(float)contOpt_FER2_corr*100/54.0<<" "<<(float)contOpt_GS_anticorr*100/54.0<<" "<<(float)contOpt_FER1_anticorr*100/54.0<<" "<<(float)contOpt_FER2_anticorr*100/54.0<<endl;

}

