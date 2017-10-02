#!/bin/bash

#5 objetivos
for i in 5 7 10 15 20  25 30 35 40 45 50 100 
do


	../.././fernandes < k_centrum/anticorrelated/$i.anticorr1.in > TESTE/fernandes/k_centrum/anticorrelated/$i.anticorr1.out
	../.././fernandes < k_centrum/anticorrelated/$i.anticorr2.in > TESTE/fernandes/k_centrum/anticorrelated/$i.anticorr2.out
	../.././fernandes < k_centrum/anticorrelated/$i.anticorr3.in > TESTE/fernandes/k_centrum/anticorrelated/$i.anticorr3.out
	

done