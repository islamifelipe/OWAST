#ifndef VETORESDIRECAO
#define VETORESDIRECAO

#include <cmath>
#include "param.h"
#include "SolucaoEdgeSet.cpp"

void Reference_Generation(double vetoresDirecoes[NUMDIRECOES][NUMOBJETIVOS]){
	double B[NUMOBJETIVOS][NUMOBJETIVOS]; // b-ésimo vetor X coordenada
	double D[NUMOBJETIVOS][K_LAYER][NUMOBJETIVOS]; // o vetor D_i^r // B_i X r X coordenada
	//double Dchapeu[NUMOBJETIVOS][K_LAYER][]; // vetor Dchapeu^t_r_i // B_i X r X t X coordenada
	for (int i=0; i<NUMOBJETIVOS; i++) vetoresDirecoes[0][i] = 1.0/NUMOBJETIVOS; // vetor C
	for (int b=0; b<NUMOBJETIVOS; b++){
		for (int i=0; i<NUMOBJETIVOS; i++) B[b][i] = 0.0;
		B[b][b] = 1.0; // o b-ésimo vetor tem a coordenada b igual a 1 
	}
	for (int i=0; i<NUMOBJETIVOS; i++){ // para cada B_i
		for (int r=1; r<K_LAYER+1; r++){ // r = 1, ..., k;
			double fator = (double)r/K_LAYER;
			for (int oo=0; oo<NUMOBJETIVOS; oo++) D[i][r-1][oo] = vetoresDirecoes[0][oo] + fator*(B[i][oo] - vetoresDirecoes[0][oo]);
		}
	}


	int cont = 1;
	for (int i=0; i<NUMOBJETIVOS; i++){ // para cada B_i
		for (int r=1; r<K_LAYER+1; r++){ // r = 1, ..., k;
			for (int oo=0; oo<NUMOBJETIVOS; oo++){
					vetoresDirecoes[cont][oo] = D[i][r-1][oo];
			}
			cont++;
			for (int t=1; t<r+1; t++){ // t = 1, ..., k
				double fator = (double) t/(r+1);
				for (int oo=0; oo<NUMOBJETIVOS; oo++){
					if (i+1<NUMOBJETIVOS) vetoresDirecoes[cont][oo] = D[i][t-1][oo] + (fator)*(D[i+1][r-1][oo] - D[i][t-1][oo]);
					else vetoresDirecoes[cont][oo] = D[i][t-1][oo] + (fator)*(D[0][r-1][oo] - D[i][t-1][oo]);
				}
				cont++;

			}
		}
	}
}


#endif