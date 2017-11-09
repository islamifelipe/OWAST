#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do 
	./getResultado2 <  memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_tempoProOtimoo.log
	./getResultado2 <  memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_tempoProOtimoo.log
	./getResultado2 <  memetic_SEPA_R/Testes/8_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_tempoProOtimoo.log
done 
