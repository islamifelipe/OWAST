#!/bin/bash


for i in 30 35 40 45 50 100 200 300 400 
do
	./getResultados < INSTANCES/8_OBJETIVOS/TESTE/fernandes2/Hurwicz/correlated/$i.corr1.out
	./getResultados < INSTANCES/8_OBJETIVOS/TESTE/fernandes2/Hurwicz/correlated/$i.corr2.out
	./getResultados < INSTANCES/8_OBJETIVOS/TESTE/fernandes2/Hurwicz/correlated/$i.corr3.out
done 
