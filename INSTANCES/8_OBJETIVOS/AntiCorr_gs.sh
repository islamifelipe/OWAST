#!/bin/bash

for i in 5 7 10 15 20  25 30 35 40 45 50 100 
do

	
	../.././gs < k_trimmed/anticorrelated/$i.anticorr1.in > TESTE/gs/k_trimmed/anticorrelated/$i.anticorr1.out
	../.././gs < k_trimmed/anticorrelated/$i.anticorr2.in > TESTE/gs/k_trimmed/anticorrelated/$i.anticorr2.out
	../.././gs < k_trimmed/anticorrelated/$i.anticorr3.in > TESTE/gs/k_trimmed/anticorrelated/$i.anticorr3.out
	

	../.././gs < k_centrum/anticorrelated/$i.anticorr1.in > TESTE/gs/k_centrum/anticorrelated/$i.anticorr1.out
	../.././gs < k_centrum/anticorrelated/$i.anticorr2.in > TESTE/gs/k_centrum/anticorrelated/$i.anticorr2.out
	../.././gs < k_centrum/anticorrelated/$i.anticorr3.in > TESTE/gs/k_centrum/anticorrelated/$i.anticorr3.out
	

	../.././gs < Hurwicz/anticorrelated/$i.anticorr1.in > TESTE/gs/Hurwicz/anticorrelated/$i.anticorr1.out
	../.././gs < Hurwicz/anticorrelated/$i.anticorr2.in > TESTE/gs/Hurwicz/anticorrelated/$i.anticorr2.out
	../.././gs < Hurwicz/anticorrelated/$i.anticorr3.in > TESTE/gs/Hurwicz/anticorrelated/$i.anticorr3.out
	
done