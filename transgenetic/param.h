#ifndef ZG_H
#define ZG_H

/*This code file was kindly provided by Monteiro */

#include "rand/randomc.h"

/* OPCOES DE DEBUG */
//#define DEBUG
#ifdef DEBUG
#define D(x) x
#endif
#ifndef DEBUG
#define D(x)
#endif

//#define ASSERT
#ifdef ASSERT
#define ASS(x) x
#endif
#ifndef ASSERT
#define ASS(x)
#endif

#define f(k,i,j) custos[k][i][j] // objetivo k, vertice i j 
#define EPS 1e-9 // quanquer coisa menor que esse valor, é considerado 0

#define NUMOBJETIVOS 8 // Varia
#define NUMEROVERTICES 15 // TESTE
#define NUMEROARESTAS (NUMEROVERTICES-1)

/*Parâmetros da populçao*/
#define TAMANHOPOPULACAO 100
#define PORCENT_RANDOM 25
#define PORCENT_KCENTRUM 25
#define PORCENT_KTRIMENT 25
#define PORCENT_HURWICZ 25

/*Parâmetros do SPEA/R */
#define K_LAYER 5
#define NUMDIRECOES ((NUMOBJETIVOS*K_LAYER*(K_LAYER+3))/2+1)

// Parametros do transgenético

#define NUMESCVECTORS 10
#define NUMTRANSPONSONS 2
#define NUMPLASMIDEOS 10
#define MAXIMOFALHASBUSCA 2

#define NUMSOLTRANSPOSON 3

#define NUMEROITERACOES 30 /* FIXME 500 */
#define NUMEROMCPRIM 142   /* NUMERO DE SOLUCOES INICIAIS GERADAS PELO MCPRIM */
#define ALGORITMOCONVERGIU 10 /* NUMERO DE GERACOES SEM MUDANCA NO PARETO SET PARA DIVERSIFICAR */
#define PCTDIVERSIFICACAO 0.0 /* PARCELA DA POPULACAO A SER ALTERADA NA DIVERSIFICACAO */

#endif


