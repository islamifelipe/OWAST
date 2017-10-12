#ifndef ZG_H
#define ZG_H

/*This code file was kindly provided by Monteiro */

#include "rand/randomc.h"

extern int numplasmideos;
extern int per_plas1;
extern int per_plas2;
extern int per_plas3;
extern double pro_trans1;
extern double pro_trans2;
extern double temperatura;
extern double taxadecaimento;
extern double iteracao;
extern double taxadecaimentoIteracao;
extern int numgeracoes;



extern int numobjetivos;
extern int numerovertices;
extern int numdirecoes;


#define PI 3.14159265
#define f(k,i,j) custos[k][i][j] // objetivo k, vertice i j 
#define EPS 1e-9 // qualquer coisa menor que esse valor, é considerado 0

// #define NUMOBJETIVOS2 10 // Varia
// #define NUMEROVERTICES2 500 // Varia
// #define NUMEROARESTAS2 (NUMEROVERTICES2-1)


/*Parâmetros do SPEA/R */
#define K_LAYER 6
// #define NUMDIRECOES2 ((NUMOBJETIVOS2*K_LAYER*(K_LAYER+3))/2+1)

/*Parâmetros da populçao*/
#define TAMANHOPOPULACAO 100  //#define TAMANHOPOPULACAO (NUMDIRECOES)  // 
#define TAMANHOREPOSITORIO (TAMANHOPOPULACAO*3)
#define PORCENT_RANDOM 10 //--- 
#define PORCENT_KCENTRUM 30 //---
#define PORCENT_KTRIMENT 30 //--- 
#define PORCENT_HURWICZ 30 //--- 


// #define QUANTGERACOES 50//40 - 50 // quantidade de iteracoes do TANSGENETICO
// #define NUMPLASMIDEOS 20 // 13 - 20 quantidade total de plasmideos
// #define PER_PLAS1 30 // 25 - 31 percentagem de plasmideos gerados pelo rmc-prim
// #define PER_PLAS2 40 // 35 - 41 percentagem de plasmideos gerados por uma soluçao
// #define PER_PLAS3 (100 - PER_PLAS1 - PER_PLAS2) // // percentagem de plasmideos gerados por duas soluçoes
// #define PROB_TRANS2 0.4//0.3 - 0.45// SA
// #define PROB_TRANS1 0.8 // 0.5 - 0.8// primTrans


// /*Parâmetros para o Simulated Annealing*/
// #define TEMPERATURA 26 // 20 - 26 // vai sendo dividido por FATORDECAIMENTO
// #define FATORDECAIMENTO 1.7//1.7 - 2.0
// #define FATORDECAIMENTOITERACAO 1.7//1.4 - 1.7
// #define ITERACAO_K 15 //10 - 15 // vai sendo multiplicado por FATORDECAIMENTOITERACAO

// O algoritmo para quando a temperatura for menor que 1
// quanto menor a temperatura, maior a quantidade de iteraçoes


#endif
