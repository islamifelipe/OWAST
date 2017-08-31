#!/bin/bash


for i in 5 7 10 12 15 17 20 22 25 27 30 33 35 
do
	./getResultados < 4_OBJETIVOS/TESTE/gs/anticorrelated/$i.anticorr1.out
	./getResultados < 4_OBJETIVOS/TESTE/gs/anticorrelated/$i.anticorr2.out
	./getResultados < 4_OBJETIVOS/TESTE/gs/anticorrelated/$i.anticorr3.out
done 
