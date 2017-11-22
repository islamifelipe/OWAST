#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do 
	./getResultado2 <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_timeFile.log
	./getResultado2 <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_timeFile.log
	./getResultado2 <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_timeFile.log
done 

echo "\n"

for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do 
	./getResultado2 <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr1/$i.anticorr1_timeFile.log
	./getResultado2 <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr2/$i.anticorr2_timeFile.log
	./getResultado2 <  transgenetic64bit/Testes/10_OBJETIVOS/$i/Hurwicz/anticorrelated/$i.anticorr3/$i.anticorr3_timeFile.log
done 