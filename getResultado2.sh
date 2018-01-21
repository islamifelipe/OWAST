#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do 
	
	for k in 1 2 3
	do
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr$k/$i.corr"$k"_plasm1.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr$k/$i.corr"$k"_plasm2.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr$k/$i.corr"$k"_plasm3.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr$k/$i.corr"$k"_primTrans.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr$k/$i.corr"$k"_saTrans.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr$k/$i.corr"$k"_avaliado.log
		

		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_plasm1.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_plasm2.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_plasm3.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_primTrans.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_saTrans.log
		./getResultado2 <  transgenetic64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr$k/$i.anticorr"$k"_avaliado.log
		echo ""

	
	done
	# ./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr2/$i.corr2_avaliado.log
	# ./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_trimmed/correlated/$i.corr3/$i.corr3_avaliado.log
done 

# echo "\n"

# for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
# do 
# 	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr1/$i.anticorr1_avaliado.log
# 	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr2/$i.anticorr2_avaliado.log
# 	./getResultado2 <  memetic_SEPA_R_64bit/Testes/5_OBJETIVOS/$i/k_trimmed/anticorrelated/$i.anticorr3/$i.anticorr3_avaliado.log
# done 

# crossovers
# mutaçoes
# renovada
# avaliado

# memetic_SEPA_R_64bit
# transgenetic64bit