#!/bin/bash

for i in 5 7 10 15 20  25 30 35 40 45 50 100 
do
	../.././gs < k_trimmed/correlated/$i.corr1.in > TESTE/gs/k_trimmed/correlated/$i.corr1.out
	../.././gs < k_trimmed/correlated/$i.corr2.in > TESTE/gs/k_trimmed/correlated/$i.corr2.out
	../.././gs < k_trimmed/correlated/$i.corr3.in > TESTE/gs/k_trimmed/correlated/$i.corr3.out
	

	../.././gs < k_centrum/correlated/$i.corr1.in > TESTE/gs/k_centrum/correlated/$i.corr1.out
	../.././gs < k_centrum/correlated/$i.corr2.in > TESTE/gs/k_centrum/correlated/$i.corr2.out
	../.././gs < k_centrum/correlated/$i.corr3.in > TESTE/gs/k_centrum/correlated/$i.corr3.out
	

	../.././gs < Hurwicz/correlated/$i.corr1.in > TESTE/gs/Hurwicz/correlated/$i.corr1.out
	../.././gs < Hurwicz/correlated/$i.corr2.in > TESTE/gs/Hurwicz/correlated/$i.corr2.out
	../.././gs < Hurwicz/correlated/$i.corr3.in > TESTE/gs/Hurwicz/correlated/$i.corr3.out
	
done