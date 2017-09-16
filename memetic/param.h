#ifndef ZG_H
#define ZG_H

/*This code file was kindly provided by Monteiro */

#include "rand/randomc.h"


#define f(k,i,j) custos[k][i][j] // objetivo k, vertice i j 
#define EPS 1e-9 // quanquer coisa menor que esse valor, é considerado 0

#define NUMOBJETIVOS 4 // Varia
#define NUMEROVERTICES 15 // TESTE
#define NUMEROARESTAS (NUMEROVERTICES-1)


/*Parâmetros do SPEA/R */
#define K_LAYER 5
#define NUMDIRECOES ((NUMOBJETIVOS*K_LAYER*(K_LAYER+3))/2+1)

/*Parâmetros da populçao*/
#define TAMANHOPOPULACAO (NUMDIRECOES) //#define TAMANHOPOPULACAO 100
#define PORCENT_RANDOM 25
#define PORCENT_KCENTRUM 25
#define PORCENT_KTRIMENT 25
#define PORCENT_HURWICZ 25

/*Parâmetros da busca tabu*/
#define MAX_ITERATIONS 20
#define MAX_VIZINHOS 20
#define TABUTENURE 3 

/*Parâmetros para o Simulated Annealing*/
#define TEMPERATURA 40 // vai sendo dividido por FATORDECAIMENTO
#define FATORDECAIMENTO 2.5
#define ITERACAO_K 20 // vai sendo multiplicado por FATORDECAIMENTO
// O algoritmo para quando a temperatura for menor que 1
// quanto menor a temperatura, maior a quantidade de iteraçoes


#endif


