#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do
	c=1
	while [ $c -le 30 ]; 
    do
    		./getTempo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_tempoProOtimoo.log
			./getTempo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_tempoProOtimoo.log
			./getTempo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_tempoProOtimoo.log
			

    		./getTempo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_tempoProOtimoo.log
			./getTempo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_tempoProOtimoo.log
			./getTempo <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_"$c".out  >> transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_tempoProOtimoo.log
			c=$((c+1))
    done
done 
