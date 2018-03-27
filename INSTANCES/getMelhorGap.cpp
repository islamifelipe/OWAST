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

int contBestGap_GS_corr = 0;
int contBestGap_FER1_corr = 0;
int contBestGap_FER2_corr = 0;

int contBestGap_GS_anticorr = 0;
int contBestGap_FER1_anticorr = 0;
int contBestGap_FER2_anticorr = 0;

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
		if ( tokens[2].compare("--")!=0 && tokens[4].compare("--")!=0 &&  tokens[6].compare("--")!=0
			&& tokens[2].find("%")!=string::npos && tokens[4].find("%")!=string::npos && tokens[6].find("%")!=string::npos){
			
				std::size_t pos = tokens[2].find("%"); 
				float gs = stof(tokens[2].substr (0,pos));

				pos = tokens[4].find("%"); 
				float fer1 = stof(tokens[4].substr (0,pos));

				pos = tokens[6].find("%"); 
				float fer2 = stof(tokens[6].substr (0,pos));

				if (gs < fer1 && gs < fer2){
					contBestGap_GS_corr++;
				} else if (fer1 < gs && fer1 < fer2){
					contBestGap_FER1_corr++;
				} else if (fer2 < gs && fer2 < fer1){
					contBestGap_FER2_corr++;
				}

		}


		if ( tokens[9].compare("--")!=0 && tokens[11].compare("--")!=0 &&  tokens[13].compare("--")!=0
			&& tokens[9].find("%")!=string::npos && tokens[11].find("%")!=string::npos && tokens[13].find("%")!=string::npos){
			
				std::size_t pos = tokens[9].find("%"); 
				float gs = stof(tokens[9].substr (0,pos));

				pos = tokens[11].find("%"); 
				float fer1 = stof(tokens[11].substr (0,pos));

				pos = tokens[13].find("%"); 
				float fer2 = stof(tokens[13].substr (0,pos));

				if (gs < fer1 && gs < fer2){
					contBestGap_GS_anticorr++;
				} else if (fer1 < gs && fer1 < fer2){
					contBestGap_FER1_anticorr++;
				} else if (fer2 < gs && fer2 < fer1){
					contBestGap_FER2_anticorr++;
				}

		}
		


	}
		cout<<contBestGap_GS_corr<<" "<<contBestGap_FER1_corr<<" "<<contBestGap_FER2_corr<<" "<<contBestGap_GS_anticorr<<" "<<contBestGap_FER1_anticorr<<" "<<contBestGap_FER2_anticorr<<endl;
	
	
}

