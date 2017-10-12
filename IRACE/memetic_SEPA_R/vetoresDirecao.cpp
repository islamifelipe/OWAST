#ifndef VETORESDIRECAO
#define VETORESDIRECAO

#include <cmath>
#include "param.h"
#include "SolucaoEdgeSet.cpp"

void Reference_Generation(double **vetoresDirecoes, double &thetaM){
	double B[10][10]; // b-ésimo vetor X coordenada
	double D[10][K_LAYER][10]; // o vetor D_i^r // B_i X r X coordenada
	//double Dchapeu[NUMOBJETIVOS][K_LAYER][]; // vetor Dchapeu^t_r_i // B_i X r X t X coordenada
	for (int i=0; i<numobjetivos; i++) vetoresDirecoes[0][i] = 1.0/numobjetivos; // vetor C
	for (int b=0; b<numobjetivos; b++){
		for (int i=0; i<numobjetivos; i++) B[b][i] = 0.0;
		B[b][b] = 1.0; // o b-ésimo vetor tem a coordenada b igual a 1 
	}
	for (int i=0; i<numobjetivos; i++){ // para cada B_i
		for (int r=1; r<K_LAYER+1; r++){ // r = 1, ..., k;
			double fator = (double)r/K_LAYER;
			for (int oo=0; oo<numobjetivos; oo++) D[i][r-1][oo] = vetoresDirecoes[0][oo] + fator*(B[i][oo] - vetoresDirecoes[0][oo]);
		}
	}


	int cont = 1;
	for (int i=0; i<numobjetivos; i++){ // para cada B_i
		for (int r=1; r<K_LAYER+1; r++){ // r = 1, ..., k;
			for (int oo=0; oo<numobjetivos; oo++){
					vetoresDirecoes[cont][oo] = D[i][r-1][oo];
			}
			cont++;
			for (int t=1; t<r+1; t++){ // t = 1, ..., k
				double fator = (double) t/(r+1);
				for (int oo=0; oo<numobjetivos; oo++){
					if (i+1<numobjetivos) vetoresDirecoes[cont][oo] = D[i][t-1][oo] + (fator)*(D[i+1][r-1][oo] - D[i][t-1][oo]);
					else vetoresDirecoes[cont][oo] = D[i][t-1][oo] + (fator)*(D[0][r-1][oo] - D[i][t-1][oo]);
				}
				cont++;

			}
		}
	}

	/// caluclo de thetaM
	thetaM = INT_MIN;
	for (int i=0; i<numdirecoes; i++){
		double min=INT_MAX;
		for (int j=0; j<numdirecoes; j++){ // calcula o ângulo entre i e j
			
			double produtoInterno = 0;
			double norma_i = 0;
			double norma_j = 0;
			for (int o=0; o<numobjetivos; o++){
				produtoInterno += vetoresDirecoes[i][o]*vetoresDirecoes[j][o];
				norma_i += vetoresDirecoes[i][o]*vetoresDirecoes[i][o];
				norma_j += vetoresDirecoes[j][o]*vetoresDirecoes[j][o];
			}

			norma_i = sqrt(norma_i);
			norma_j = sqrt(norma_j);
			// acos dá o ângulo do arco-cosceno em radianos. Transformamos pra graus
			double angulo = acos (produtoInterno/(norma_i*norma_j)) * (180.0 / PI);	
			// angul entre direçao i e j
			if (angulo<min){
				min = angulo;
			}
		}
		if (min>thetaM){
			thetaM = min; // thetaM deve ser maximo
		}
	}
}


#endif