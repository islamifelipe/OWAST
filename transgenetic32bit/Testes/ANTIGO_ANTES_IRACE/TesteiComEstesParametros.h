#ifndef ZG_H
#define ZG_H

/*This code file was kindly provided by Monteiro */

#include "rand/randomc.h"


#define PI 3.14159265
#define f(k,i,j) custos[k][i][j] // objetivo k, vertice i j 
#define EPS 1e-9 // qualquer coisa menor que esse valor, é considerado 0

#define NUMOBJETIVOS 10 // Varia
#define NUMEROVERTICES 50 // Varia
#define NUMEROARESTAS (NUMEROVERTICES-1)


/*Parâmetros do SPEA/R */
#define K_LAYER 6
#define NUMDIRECOES ((NUMOBJETIVOS*K_LAYER*(K_LAYER+3))/2+1)

/*Parâmetros da populçao*/
#define TAMANHOPOPULACAO 100  //#define TAMANHOPOPULACAO (NUMDIRECOES)  // 
#define TAMANHOREPOSITORIO (TAMANHOPOPULACAO*3)
#define PORCENT_RANDOM 10 //--- 
#define PORCENT_KCENTRUM 30 //---
#define PORCENT_KTRIMENT 30 //--- 
#define PORCENT_HURWICZ 30 //--- 


#define QUANTGERACOES 50 // quantidade de iteracoes do TANSGENETICO
#define NUMPLASMIDEOS 15 // quantidade total de plasmideos
#define PER_PLAS1 50 // percentagem de plasmideos gerados pelo rmc-prim
#define PER_PLAS2 40 // percentagem de plasmideos gerados por uma soluçao
#define PER_PLAS3 10 // percentagem de plasmideos gerados por duas soluçoes
#define PROB_TRANS2 0.3 // SA
#define PROB_TRANS1 0.8 // primTrans

/*Parâmetros para o Simulated Annealing*/
#define TEMPERATURA 30 // vai sendo dividido por FATORDECAIMENTO
#define FATORDECAIMENTO 1.8
#define FATORDECAIMENTOITERACAO 1.8
#define ITERACAO_K 15 // vai sendo multiplicado por FATORDECAIMENTOITERACAO
// O algoritmo para quando a temperatura for menor que 1
// quanto menor a temperatura, maior a quantidade de iteraçoes


#endif


#define NUMEROVERTICES 30
#define NUMEROVERTICES 35
#define NUMEROVERTICES 40
#define NUMEROVERTICES 45
#define NUMEROVERTICES 50
#define NUMEROVERTICES 100
#define NUMEROVERTICES 200
#define NUMEROVERTICES 300
#define NUMEROVERTICES 400
#define NUMEROVERTICES 500
#define NUMEROVERTICES 600
#define NUMEROVERTICES 700
#define NUMEROVERTICES 800
#define NUMEROVERTICES 900
#define NUMEROVERTICES 1000
#define NUMEROVERTICES 30
#define NUMEROVERTICES 35
#define NUMEROVERTICES 40
#define NUMEROVERTICES 45
#define NUMEROVERTICES 50
#define NUMEROVERTICES 100
#define NUMEROVERTICES 200
#define NUMEROVERTICES 300
#define NUMEROVERTICES 400
#define NUMEROVERTICES 500
#define NUMEROVERTICES 600
#define NUMEROVERTICES 700
#define NUMEROVERTICES 800
#define NUMEROVERTICES 900
#define NUMEROVERTICES 1000
#define NUMEROVERTICES 30
#define NUMEROVERTICES 35
#define NUMEROVERTICES 40
#define NUMEROVERTICES 45
#define NUMEROVERTICES 50
#define NUMEROVERTICES 100
#define NUMEROVERTICES 200
#define NUMEROVERTICES 300
#define NUMEROVERTICES 400
#define NUMEROVERTICES 500
#define NUMEROVERTICES 600
#define NUMEROVERTICES 700
#define NUMEROVERTICES 800
#define NUMEROVERTICES 900
#define NUMEROVERTICES 1000
#define NUMEROVERTICES 30
#define NUMEROVERTICES 35
#define NUMEROVERTICES 40
#define NUMEROVERTICES 45
#define NUMEROVERTICES 50
#define NUMEROVERTICES 100
#define NUMEROVERTICES 200
#define NUMEROVERTICES 300
#define NUMEROVERTICES 400
#define NUMEROVERTICES 500
#define NUMEROVERTICES 600
#define NUMEROVERTICES 700
#define NUMEROVERTICES 800
#define NUMEROVERTICES 900
#define NUMEROVERTICES 1000
