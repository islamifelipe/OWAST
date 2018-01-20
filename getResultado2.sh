#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do 
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_tempoProOtimoo.log
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_tempoProOtimoo.log
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_tempoProOtimoo.log
done 

echo "\n"

for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do 
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_tempoProOtimoo.log
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_tempoProOtimoo.log
	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_tempoProOtimoo.log
done 

#30.corr3_timeFile
#anticorr2_tempoProOtimoo
#30.corr3_sampleFile


# memetic_SEPA_R_64bit
# transgenetic64bit