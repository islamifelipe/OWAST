#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500
do
	c=1
	while [ $c -le 30 ]; 
    do
    		./getTempo <  Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_tempoProOtimo.log
			./getTempo <  Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_tempoProOtimo.log
			./getTempo <  Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> Trabalho2/Testes/10_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_tempoProOtimo.log
			c=$((c+1))
    done
done 
