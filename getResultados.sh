#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 
do
	./getResultados < INSTANCES/10_OBJETIVOS/TESTE/fernandes2/Hurwicz/anticorrelated/$i.anticorr1.out
	./getResultados < INSTANCES/10_OBJETIVOS/TESTE/fernandes2/Hurwicz/anticorrelated/$i.anticorr2.out
	./getResultados < INSTANCES/10_OBJETIVOS/TESTE/fernandes2/Hurwicz/anticorrelated/$i.anticorr3.out
done 
