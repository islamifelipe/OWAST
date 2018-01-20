#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do 
	
	for k in 1 2 3
	do
		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr$k/$i.corr"$k"_crossovers.log
		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr$k/$i.corr"$k"_mutaçoes.log
		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr$k/$i.corr"$k"_SA.log
		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr$k/$i.corr"$k"_renovada.log
		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/correlated/$i.corr$k/$i.corr"$k"_avaliado.log
		

		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_crossovers.log
		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_mutaçoes.log
		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_SA.log
		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_renovada.log
		./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_avaliado.log
		echo ""

	
	done
	# ./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_centrum/correlated/$i.corr2/$i.corr2_avaliado.log
	# ./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_centrum/correlated/$i.corr3/$i.corr3_avaliado.log
done 

# echo "\n"

# for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
# do 
# 	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr1/$i.anticorr1_avaliado.log
# 	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr2/$i.anticorr2_avaliado.log
# 	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_centrum/anticorrelated/$i.anticorr3/$i.anticorr3_avaliado.log
# done 

# crossovers
# mutaçoes
# renovada
# avaliado

# memetic_SEPA_R_64bit
# transgenetic64bit