#!/bin/bash


for i in 5 7 10 15 20 25 30 35 40 45 50 100 200 300 400 500 600 700
do
	./getResultados < INSTANCES/8_OBJETIVOS/TESTE/gs/k_trimmed/anticorrelated/$i.anticorr1.out
	./getResultados < INSTANCES/8_OBJETIVOS/TESTE/gs/k_trimmed/anticorrelated/$i.anticorr2.out
	./getResultados < INSTANCES/8_OBJETIVOS/TESTE/gs/k_trimmed/anticorrelated/$i.anticorr3.out
done 
