#!/bin/bash


for p in 1000
do
	for i in 1 2 3
	do
		cat ../../memetic_SEPA_R/Testes/8_OBJETIVOS/$p/k_centrum/correlated/$p.corr$i/$p.corr"$i"_sampleFile.log ../../transgenetic/Testes/8_OBJETIVOS/$p/k_centrum/correlated/$p.corr$i/$p.corr"$i"_sampleFile.log > inputFilter.in
		../../../../Pesquisa_AGM/Epsilon/PISA/statistics_c_source/mann-whit inputFilter.in ../../../../Pesquisa_AGM/Epsilon/PISA/statistics_c_source/param.txt k_centrum/correlated/mann_whit_$p.corr$i.out
		
		cat ../../memetic_SEPA_R/Testes/8_OBJETIVOS/$p/k_centrum/anticorrelated/$p.anticorr$i/$p.anticorr"$i"_sampleFile.log ../../transgenetic/Testes/8_OBJETIVOS/$p/k_centrum/anticorrelated/$p.anticorr$i/$p.anticorr"$i"_sampleFile.log > inputFilter.in
		../../../../Pesquisa_AGM/Epsilon/PISA/statistics_c_source/mann-whit inputFilter.in ../../../../Pesquisa_AGM/Epsilon/PISA/statistics_c_source/param.txt k_centrum/anticorrelated/mann_whit_$p.anticorr$i.out
		
	done
done

