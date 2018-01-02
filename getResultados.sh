#!/bin/bash


for i in 5 7 10 15 20 25 30 35 40 45 50 100 200 300 400 500 600 700
do
	./getResultados INSTANCES/10_OBJETIVOS/TESTE/gs/k_trimmed/correlated/$i.corr1.out INSTANCES/10_OBJETIVOS/TESTE/fernandes/k_trimmed/correlated/$i.corr1.out INSTANCES/10_OBJETIVOS/TESTE/fernandes2/k_trimmed/correlated/$i.corr1.out   INSTANCES/10_OBJETIVOS/TESTE/gs/k_trimmed/anticorrelated/$i.anticorr1.out INSTANCES/10_OBJETIVOS/TESTE/fernandes/k_trimmed/anticorrelated/$i.anticorr1.out INSTANCES/10_OBJETIVOS/TESTE/fernandes2/k_trimmed/anticorrelated/$i.anticorr1.out
	./getResultados INSTANCES/10_OBJETIVOS/TESTE/gs/k_trimmed/correlated/$i.corr2.out INSTANCES/10_OBJETIVOS/TESTE/fernandes/k_trimmed/correlated/$i.corr2.out INSTANCES/10_OBJETIVOS/TESTE/fernandes2/k_trimmed/correlated/$i.corr2.out   INSTANCES/10_OBJETIVOS/TESTE/gs/k_trimmed/anticorrelated/$i.anticorr2.out INSTANCES/10_OBJETIVOS/TESTE/fernandes/k_trimmed/anticorrelated/$i.anticorr2.out INSTANCES/10_OBJETIVOS/TESTE/fernandes2/k_trimmed/anticorrelated/$i.anticorr2.out
	./getResultados INSTANCES/10_OBJETIVOS/TESTE/gs/k_trimmed/correlated/$i.corr3.out INSTANCES/10_OBJETIVOS/TESTE/fernandes/k_trimmed/correlated/$i.corr3.out INSTANCES/10_OBJETIVOS/TESTE/fernandes2/k_trimmed/correlated/$i.corr3.out   INSTANCES/10_OBJETIVOS/TESTE/gs/k_trimmed/anticorrelated/$i.anticorr3.out INSTANCES/10_OBJETIVOS/TESTE/fernandes/k_trimmed/anticorrelated/$i.anticorr3.out INSTANCES/10_OBJETIVOS/TESTE/fernandes2/k_trimmed/anticorrelated/$i.anticorr3.out
done 
