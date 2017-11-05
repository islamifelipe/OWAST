#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do
	c=1
	while [ $c -le 30 ]; 
    do
    		./getInfo <  memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_"$c".out  >> memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_renovada.log
			./getInfo <  memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_"$c".out  >> memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_renovada.log
			./getInfo <  memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_"$c".out  >> memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_renovada.log
			c=$((c+1))
    done
done 
