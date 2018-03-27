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

int contBestSol_GS_corr = 0;
int contBestSol_FER1_corr = 0;
int contBestSol_FER2_corr = 0;

int contBestSol_GS_anticorr = 0;
int contBestSol_FER1_anticorr = 0;
int contBestSol_FER2_anticorr = 0;
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
		if ( tokens[3].compare("--")!=0 && tokens[5].compare("--")!=0 &&  tokens[7].compare("--")!=0){
			float solgs = stof(tokens[3]);
			float solfer1 = stof(tokens[5]);
			float solfer2 = stof(tokens[7]);
			if (solgs < solfer1 && solgs < solfer2){
				contBestSol_GS_corr++;
			} else if (solfer1 < solgs && solfer1 < solfer2){
				contBestSol_FER1_corr++;
			} else if (solfer2 < solgs && solfer2 < solfer1){
				contBestSol_FER2_corr++;
			}
			contCorrDiv++;
		}
		


		if ( tokens[10].compare("--")!=0 && tokens[12].compare("--")!=0 &&  tokens[14].compare("--")!=0){
			float solgs = stof(tokens[10]);
			float solfer1 = stof(tokens[12]);
			float solfer2 = stof(tokens[14]);
			if (solgs < solfer1 && solgs < solfer2){
				contBestSol_GS_anticorr++;
			} else if (solfer1 < solgs && solfer1 < solfer2){
				contBestSol_FER1_anticorr++;
			} else if (solfer2 < solgs && solfer2 < solfer1){
				contBestSol_FER2_anticorr++;
			}
			contAntiCorrDiv++;
		}
	}

	cout<<(float)contBestSol_GS_corr*100/(float)contCorrDiv<<" "<<(float)contBestSol_FER1_corr*100/(float)contCorrDiv<<" "<<(float)contBestSol_FER2_corr*100/(float)contCorrDiv<<" "<<(float)contBestSol_GS_anticorr*100/(float)contAntiCorrDiv<<" "<<(float)contBestSol_FER1_anticorr*100/(float)contAntiCorrDiv<<" "<<(float)contBestSol_FER2_anticorr*100/(float)contAntiCorrDiv<<endl;

}

