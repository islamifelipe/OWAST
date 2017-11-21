#!/bin/bash
for p in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do
	for i in 1 2 3
	do #transgenetic #memetic_SEPA_R
		./lerTempo ../../transgenetic/Testes/10_OBJETIVOS/$p/Hurwicz/anticorrelated/$p.anticorr"$i"/$p.anticorr"$i"_timeFile.log teste.log 
	done

done