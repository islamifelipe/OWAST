#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 500 600 700 800 900 1000
do
	./getResultado2 <  transgenetic/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr1/$i.corr1_avaliado.log
	./getResultado2 <  transgenetic/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr2/$i.corr2_avaliado.log
	./getResultado2 <  transgenetic/Testes/8_OBJETIVOS/$i/Hurwicz/correlated/$i.corr3/$i.corr3_avaliado.log
done 
