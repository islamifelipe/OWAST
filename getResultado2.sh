#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500
do
	./getResultado2 <  Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_avaliacoes.log
	./getResultado2 <  Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_avaliacoes.log
	./getResultado2 <  Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_avaliacoes.log
done 
