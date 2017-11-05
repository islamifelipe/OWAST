#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do
	./getResultado2 <  memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr1/$i.corr1_renovada.log
	./getResultado2 <  memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_renovada.log
	./getResultado2 <  memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_renovada.log
done 
