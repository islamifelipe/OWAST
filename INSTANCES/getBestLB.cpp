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

int contBestLB_GS_corr = 0;
int contBestLB_FER1_corr = 0;
int contBestLB_FER2_corr = 0;

int contBestLB_GS_anticorr = 0;
int contBestLB_FER1_anticorr = 0;
int contBestLB_FER2_anticorr = 0;

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
	int cont=0;
	while (innn>>linha){
		cont++;
		// /cout<<linha<<endl;
		
		std::vector<string> tokens = split(linha, ',');
		if ( tokens[1].compare("--")!=0 ){
			std::size_t pos = tokens[1].find("_"); 
			string fg = tokens[1].substr (pos+1);
			if (fg.compare("{1}")==0 || fg.compare("{12}")==0 || fg.compare("{13}")==0 || fg.compare("{123}")==0){
				contBestLB_GS_corr++;
			}
			if (fg.compare("{2}")==0 || fg.compare("{12}")==0 || fg.compare("{23}")==0 || fg.compare("{123}")==0){
				contBestLB_FER1_corr++;
			}

			if (fg.compare("{3}")==0 || fg.compare("{13}")==0 || fg.compare("{23}")==0 || fg.compare("{123}")==0){
				contBestLB_FER2_corr++;
			}
		}
		


		if ( tokens[8].compare("--")!=0 ){
			std::size_t pos = tokens[8].find("_"); 
			string fg = tokens[8].substr (pos+1);
			if (fg.compare("{1}")==0 || fg.compare("{12}")==0 || fg.compare("{13}")==0 || fg.compare("{123}")==0){
				contBestLB_GS_anticorr++;
			}
			if (fg.compare("{2}")==0 || fg.compare("{12}")==0 || fg.compare("{23}")==0 || fg.compare("{123}")==0){
				contBestLB_FER1_anticorr++;
			}

			if (fg.compare("{3}")==0 || fg.compare("{13}")==0 || fg.compare("{23}")==0 || fg.compare("{123}")==0){
				contBestLB_FER2_anticorr++;
			}
		}


	}
	cout<<(float)contBestLB_GS_corr*100/54.0<<" "<<(float)contBestLB_FER1_corr*100/54.0<<" "<<(float)contBestLB_FER2_corr*100/54.0<<" "<<(float)contBestLB_GS_anticorr*100/54.0<<" "<<(float)contBestLB_FER1_anticorr*100/54.0<<" "<<(float)contBestLB_FER2_anticorr*100/54.0<<endl;
	
	
}

