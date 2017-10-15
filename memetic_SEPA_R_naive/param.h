#ifndef ZG_H
#define ZG_H

/*This code file was kindly provided by Monteiro */

#include "rand/randomc.h"



#define PI 3.14159265
#define f(k,i,j) custos[k][i][j] // objetivo k, vertice i j 
#define EPS 1e-9 // quanquer coisa menor que esse valor, é considerado 0

#define NUMOBJETIVOS 10 // Varia
#define NUMEROVERTICES 50 // Varia
#define NUMEROARESTAS (NUMEROVERTICES-1)


/*Parâmetros do SPEA/R */
#define K_LAYER 6
#define NUMDIRECOES ((NUMOBJETIVOS*K_LAYER*(K_LAYER+3))/2+1)

/*Parâmetros da populçao*/
#define TAMANHOPOPULACAO 100  //#define TAMANHOPOPULACAO (NUMDIRECOES)  // 
#define PORCENT_RANDOM 10 //--- 
#define PORCENT_KCENTRUM 30 //---
#define PORCENT_KTRIMENT 30 //--- 
#define PORCENT_HURWICZ 30 //--- 

/*Parâmetros do GA*/
#define TAXADECRUZAMENTO 0.95  //0.97//0.90 - 0.99 //0.97  // 98% por geraçao
#define TAXADEMUTACAO 0.11//0.1 - 0.3 // 10% por geraçao
#define QUANTGERACOES 46//50 //40 - 50 // quantidade de iteracoes do M-GA

/*Parâmetros da busca tabu -- NAO UTILIZADO NO MOMENTO*/
#define MAX_ITERATIONS 20
#define MAX_VIZINHOS 20
#define TABUTENURE 3 


/*Parâmetros para o Simulated Annealing*/
#define TEMPERATURA 20//24 // 20 - 26 // vai sendo dividido por FATORDECAIMENTO
#define FATORDECAIMENTO 1.78//2.0//1.7 - 2.0
#define FATORDECAIMENTOITERACAO 1.66//1.4 - 1.7
#define ITERACAO_K 10 //10 - 15 // vai sendo multiplicado por FATORDECAIMENTOITERACAO


// O algoritmo para quando a temperatura for menor que 1
// quanto menor a temperatura, maior a quantidade de iteraçoes


#endif
