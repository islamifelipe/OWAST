#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do
	c=1
	while [ $c -le 30 ]; 
    do
    		./getInfo <  transgenetic/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_"$c".out  >> transgenetic/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_avaliado.log
			./getInfo <  transgenetic/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_"$c".out  >> transgenetic/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_avaliado.log
			./getInfo <  transgenetic/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_"$c".out  >> transgenetic/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_avaliado.log
			c=$((c+1))
    done
done 
