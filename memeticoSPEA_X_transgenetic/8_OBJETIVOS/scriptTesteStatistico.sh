#!/bin/bash


for p in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 #1000
do
	for i in 1 2 3
	do
		cat ../../memetic_SEPA_R/Testes/8_OBJETIVOS/$p/Hurwicz/anticorrelated/$p.anticorr$i/$p.anticorr"$i"_sampleFile.log ../../transgenetic/Testes/8_OBJETIVOS/$p/Hurwicz/anticorrelated/$p.anticorr$i/$p.anticorr"$i"_sampleFile.log > inputFilter.in
		../../../../Pesquisa_AGM/Epsilon/PISA/statistics_c_source/mann-whit inputFilter.in ../../../../Pesquisa_AGM/Epsilon/PISA/statistics_c_source/param.txt Hurwicz/anticorrelated/mann_whit_$p.anticorr$i.out
		
	done
done

