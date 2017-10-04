#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500
do
	c=1
	while [ $c -le 30 ]; 
    do
    		./getInfo <  Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_"$c".out  >> Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_avaliacoes.log
			./getInfo <  Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_"$c".out  >> Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_avaliacoes.log
			./getInfo <  Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_"$c".out  >> Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_avaliacoes.log
			c=$((c+1))
    done
done 
