/* Este programa ler uma tabela em modo texto csv (sem cabeçalho) e computa o %BestTime 

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

int contBest_GS_corr = 0;
int contBest_FER1_corr = 0;
int contBest_FER2_corr = 0;

int contBest_GS_anticorr = 0;
int contBest_FER1_anticorr = 0;
int contBest_FER2_anticorr = 0;
int contCorrDiv=0;
int contAntiCorrDiv =0;

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
		if ( tokens[2].compare("--")!=0 && tokens[2].find("%")==string::npos
			&& tokens[4].compare("--")!=0 && tokens[4].find("%")==string::npos
			&& tokens[6].compare("--")!=0 && tokens[6].find("%")==string::npos){
			double gs_tempo = stof(tokens[2]);
			double fer1_tempo = stof(tokens[4]);
			double fer2_tempo = stof(tokens[6]);
			if (gs_tempo < fer1_tempo && gs_tempo < fer2_tempo){
				contBest_GS_corr++;
			} else if (fer1_tempo < gs_tempo && fer1_tempo < fer2_tempo ){
				contBest_FER1_corr++;
			} else if (fer2_tempo < gs_tempo && fer2_tempo < fer1_tempo){
				contBest_FER2_corr++;
			}
			contCorrDiv++;
		}
		


		if ( tokens[9].compare("--")!=0 && tokens[9].find("%")==string::npos
			&& tokens[11].compare("--")!=0 && tokens[11].find("%")==string::npos
			&& tokens[13].compare("--")!=0 && tokens[13].find("%")==string::npos){
			double gs_tempo = stof(tokens[9]);
			double fer1_tempo = stof(tokens[11]);
			double fer2_tempo = stof(tokens[13]);
			if (gs_tempo < fer1_tempo && gs_tempo < fer2_tempo){
				contBest_GS_anticorr++;
			} else if (fer1_tempo < gs_tempo && fer1_tempo < fer2_tempo ){
				contBest_FER1_anticorr++;
			} else if (fer2_tempo < gs_tempo && fer2_tempo < fer1_tempo){
				contBest_FER2_anticorr++;
			}
			contAntiCorrDiv++;
		}
	}

	cout<<(float)contBest_GS_corr*100/(float)contCorrDiv<<" "<<(float)contBest_FER1_corr*100/(float)contCorrDiv<<" "<<(float)contBest_FER2_corr*100/(float)contCorrDiv<<" "<<(float)contBest_GS_anticorr*100/(float)contAntiCorrDiv<<" "<<(float)contBest_FER1_anticorr*100/(float)contAntiCorrDiv<<" "<<(float)contBest_FER2_anticorr*100/(float)contAntiCorrDiv<<endl;

}

