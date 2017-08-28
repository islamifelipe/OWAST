/*
#=======================================================================
# Islame Felipe DA COSTA FERNANDES --- Copyright 2017
#-----------------------------------------------------------------------
# This code implements the model of Galand and Spanjaard (2012) 
# applied to OWA-ST problem with p-objectives (where p is inputted in the instance)
# and uses the model of Magnanti e Wong (1984) for spanning tree
#=======================================================================

*/


#include <iostream>
#include <vector> 
#include <string>
#include <climits>
#include <stack>   
#include <utility>      // std::pair
#include <cmath>
#include <list>
#include "gurobi_c++.h"
#include <sys/times.h>
#include <unistd.h>
using namespace std;

#define M 1000000

int n, p;
struct tms tempsInit, tempsFinal1, tempsFinal; // para medir o tempo
//double coeficienteObjetv[n][n],matrix_peso1[n][n],matrix_peso2[n][n];;
double *coeficienteObjetv;//valores de w_i (com i de 1 até p)
vector<double **> custos;  // para guardar os custos. O vector terá 'p' elementos. Cada elemento é uma matriz que guardam o peso 'p' da aresta (i,j)
short **arestas;
short **result;
//std::vector<short**> S; // TODO: nao precisa mais de um vetor

void printResultado(){
  //for (int pp=0; pp<S.size(); pp++){
  //  double cont11=0, cont22 = 0;
    //short **result = S[pp];
    //cout<<"Arvore "<<pp+1<<endl;
    std::vector<int> vet;
    for (int i=0; i<p; i++){
      vet.push_back(0);
    }
    for (int i=0; i<n; i++){
      for (int j=i+1; j<n; j++){
        if (arestas[i][j] == 1){
          if (result[i][j] == 1){
            cout <<i<<" "<<j<<" ";
            for(int o=0; o<p; o++){
              cout<<custos[o][i][j]<<" " ;
              vet[o] += custos[o][i][j];
            }
            cout<<endl;
          }
        }
      }
    }
    cout<<"(";
    for (int i=0; i<p; i++){
      cout<<vet[i]<<" ";
    }
    cout<<")"<<endl;
    cout<<endl;
  //} 
}


// void *tempo(void *nnnn){
// 	while (true){
// 		times(&tempsFinal);   /* current time */ // clock final
// 		clock_t user_time = (tempsFinal.tms_utime - tempsInit.tms_utime);
// 		float sec = (float) user_time / (float) sysconf(_SC_CLK_TCK);
		
// 		if (sec>10800){ // se o tempo limite for atingido, esse if é ativado, o resultado (na ultima iteraçao, se for o caso) é escrito e o programa para 
// 			cout<<sec<<endl;
// 			cout<<"TEMPO LIMITE ATINGIDO...   " <<endl;

// 			//printResultado();
// 			//cout<<"saindo... valor de ppp="<<ppp<<endl;
// 			exit(-1);
// 		}
// 	}
// }

/* A instância deve ter
n p 
w_1 ... w_p // coeficientes
i j v_1 .... v_p

p é a quantidade de objetivos
*/
int main(){
	int origem, destino; // vértices para cada aresta;
	int id = 0; // id das arestas que leremos do arquivo para criar o grafo
	cin>>n; // quantidade de vértices do grafo;
	cin>>p; // quantidade de objetivos
	arestas = new short*[n];
	coeficienteObjetv = new double[p];
	for (int i=0; i<n; i++){
		arestas[i] = new short[n];
	}
	for (int o=0; o<p; o++){ // para cada objetivo
		custos.push_back(new double*[n]);
		for (int i=0; i<n; i++){
			custos[o][i] = new double[n];
		}
	}


	result = new short*[n];
	for (int ii=0; ii<n; ii++){
		result[ii] = new short[n];
	}

	GRBEnv env = GRBEnv();;
	env.set("OutputFlag","0");
  env.set(GRB_DoubleParam_TimeLimit, 10800);
	GRBModel model = GRBModel(env);;

	GRBVar **y, **x, **z, **r;

  	y = new GRBVar*[n];  // 0's ou 1's (y aqui nao é a variavel de galand)
   	x = new GRBVar*[n]; // fluxo
   	z = new GRBVar*[p]; // variavel de Fernández et al (2016)
   	r = new GRBVar*[p]; //  variavel y de Galand e Spanjaard (2012)

   	for (int i=0; i<n;i++){
        y[i] = new GRBVar[n];
        x[i] = new GRBVar[n];
   	}
   	for (int o=0; o<p; o++){
   		z[o] = new GRBVar[p];
      r[o] = new GRBVar[p];
   	}

	int constrCont=0;

	for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      arestas[i][j] = 0;
    }
  }
 	for (int i=0; i<p; i++){
 		cin>>coeficienteObjetv[i]; 
 		//aproveitar esse laço para iniciar a variavel zij =)
 		for (int j=0; j<p; j++){
      z[i][j] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "z"+std::to_string(i)+std::to_string(j));
 		  r[i][j] = model.addVar(0.0, 1000000, 0.0, GRB_CONTINUOUS, "r"+std::to_string(i)+std::to_string(j));
    
    }
 	}

	while (cin>>origem){
		cin>>destino;
		for (int o=0; o<p; o++){
			cin>>custos[o][origem][destino];
		}
		x[origem][destino] = model.addVar(0.0, 1000000, 0.0, GRB_CONTINUOUS, "x"+std::to_string(origem)+std::to_string(destino)); // variavel do modelo de Magnanti e Wong (1984)
    x[destino][origem] = model.addVar(0.0, 1000000, 0.0, GRB_CONTINUOUS, "x"+std::to_string(destino)+std::to_string(origem)); // variavel do modelo de Magnanti e Wong (1984)
    y[origem][destino] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY, "y"+std::to_string(origem)+std::to_string(destino));  // variavel do modelo de Magnanti e Wong (1984)
      
    arestas[origem][destino] = 1;
    arestas[destino][origem] = 1;
		id++;
	}
	int nA = id; // quantidade de arestas do grafo	

  model.update();

  // Set objective: 
  GRBLinExpr omeva = 0;
  for (int i=0; i<p; i++){
    GRBLinExpr valrv = 0;
    for (int j=0; j<p; j++){
      valrv = valrv + r[i][j];
    }
    omeva = omeva + coeficienteObjetv[i]*valrv;
  }
  model.setObjective(omeva,GRB_MINIMIZE); 


  for (int j=0; j<p; j++){
  	GRBLinExpr summ = 0;
  	for (int i=0; i<p; i++){
  		summ   = summ  + z[i][j];
  	}
  	model.addConstr(summ, GRB_EQUAL, 1,std::to_string(constrCont++));
  //	cout<<summ<<" = 1"<<endl;
	}

	//cout<<endl;
  for (int i=0; i<p; i++){
  	GRBLinExpr summ;
  	for (int j=0; j<p; j++){
  		summ   = summ  + z[i][j];
  	}
  	model.addConstr(summ, GRB_EQUAL, 1,std::to_string(constrCont++));
  	//cout<<summ<<" = 1"<<endl;
  }

  for (int i=0; i<p-1; i++){
    GRBLinExpr summ1 = 0;
    GRBLinExpr summ2 = 0;
    for (int j=0; j<p; j++){
      summ1 = summ1 + r[i][j];
    }
    for (int j=0; j<p; j++){
      summ2 = summ2 + r[i+1][j];
    }
    model.addConstr(summ1, GRB_GREATER_EQUAL, summ2,std::to_string(constrCont++));
  }

  for (int i=0; i<p; i++){
    for (int j=0; j<p; j++){
      GRBLinExpr esq = r[i][j];
      GRBLinExpr dir = M*z[i][j];
      model.addConstr(esq, GRB_LESS_EQUAL, dir,std::to_string(constrCont++));
    }
  }

  for (int j=0; j<p; j++){
    GRBLinExpr esq = 0;
    for (int i=0; i<p; i++){
      esq = esq + r[i][j];
    }
    GRBLinExpr dir = 0;
    for(int origem=0; origem<n; origem++){
      for(int destino=origem+1; destino<n; destino++){
        if (arestas[origem][destino]==1){
          dir = dir+ custos[j][origem][destino]*y[origem][destino];
        }
      }
    }
    model.addConstr(esq, GRB_EQUAL, dir,std::to_string(constrCont++));
  
  }



  // TREE

    GRBLinExpr constr5 ;
    double co = 1;
    double com = -1;
    for (int j=0+1; j<n; j++){
    	if (arestas[0][j] == 1)
        	constr5 = constr5 + x[0][j];
    }
    model.addConstr(constr5, GRB_EQUAL, n-1,std::to_string(constrCont++));
  


    // // Add constraint:
    for (int j=1; j<n; j++){
      GRBLinExpr constr2 = 0;
      for (int i=0; i<n; i++){
        if (arestas[i][j] == 1){
          constr2 = constr2 + x[i][j];
        }
      }
      GRBLinExpr constr3 = 0;
      for (int k=0; k<n; k++){
        if (arestas[j][k] == 1){
          constr3 = constr3 + x[j][k];
        }
      }
      GRBLinExpr constr4 = constr2 - constr3;
      //cout<<constr4<<endl;
      model.addConstr(constr4, GRB_EQUAL, 1,std::to_string(constrCont++));
    }

    double coef = (double) n - 1;
    for (int i=0; i<n; i++){
      for (int j=i+1; j<n; j++){
      	if (arestas[i][j] == 1){
	        GRBLinExpr constr8;
	        GRBLinExpr constr9;
	        constr8.addTerms(&coef,&y[i][j],1);
	        constr9.addTerms(&co  ,&x[i][j],1);
	        constr9.addTerms(&co  ,&x[j][i],1); //??
	      	model.addConstr(constr8, GRB_GREATER_EQUAL, constr9,std::to_string(constrCont++));
    	}
      }
    }

    for (int i=0; i<n; i++){

      for (int j=i+1; j<n; j++){
      	if (arestas[i][j] == 1){
	        GRBLinExpr constr22;
	        GRBLinExpr constr33;
	        constr22.addTerms(&co  ,&y[i][j],1);
	        constr33.addTerms(&co  ,&x[i][j],1);
	        constr33.addTerms(&co  ,&x[j][i],1); //???
	       // cout<<constr22<<GRB_LESS_EQUAL<<constr33<<endl;     
	        model.addConstr(constr22, GRB_LESS_EQUAL, constr33,std::to_string(constrCont++));
    	}
      }
    }



    //int nn = 0; // n do algoritmo de Lokman and Koksalan 	
    /* 
	* Executa modelo de Fernández (2016) 	
	*/
	try {
		  times(&tempsInit);



      
      model.optimize();
      times(&tempsFinal); 
      clock_t user_time = (tempsFinal.tms_utime - tempsInit.tms_utime);
      float sec = (float) user_time / (float) sysconf(_SC_CLK_TCK);
      cout<<"Tempo: "<<sec<<" segundos"<<endl;
      cout<<endl;

	    int optimstatus = model.get(GRB_IntAttr_Status);
		if (optimstatus != GRB_INFEASIBLE){
			for (int i=0; i<n; i++){
			    for (int j=i+1; j<n; j++){
			     	if (arestas[i][j] == 1){
			     		result[i][j] = y[i][j].get(GRB_DoubleAttr_X);
				    }
			    }
			}
		} else {cout<<"Inviavel"<<endl;}
		//S.push_back(result);
		// cout<<"Resultado:"<<endl;
		printResultado();

  	 } catch(GRBException e) {
	    cout << "Error code = " << e.getErrorCode() << endl;
	    cout << e.getMessage() << endl;
	 } catch(...) {
	    cout << "Exception during optimization" << endl;
	 }
   	
	return 0;
}