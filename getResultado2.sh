#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do 
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/10_OBJETIVOS/$i/k_centrum/correlated/$i.corr1/$i.corr1_sampleFile.log
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/10_OBJETIVOS/$i/k_centrum/correlated/$i.corr2/$i.corr2_sampleFile.log
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/10_OBJETIVOS/$i/k_centrum/correlated/$i.corr3/$i.corr3_sampleFile.log
done 

echo "\n"

for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do 
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/10_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_sampleFile.log
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/10_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_sampleFile.log
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/10_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_sampleFile.log
done 

# memetic_SEPA_R_64bit
# transgenetic64bit