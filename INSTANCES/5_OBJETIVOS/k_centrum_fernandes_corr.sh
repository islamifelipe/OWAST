#!/bin/bash

#5 objetivos
for i in 5 7 10 15 20 25 30 35 40 45 50 100 
do
	../.././fernandes < k_centrum/correlated/$i.corr1.in > TESTE/fernandes/k_centrum/correlated/$i.corr1.out
	../.././fernandes < k_centrum/correlated/$i.corr2.in > TESTE/fernandes/k_centrum/correlated/$i.corr2.out
	../.././fernandes < k_centrum/correlated/$i.corr3.in > TESTE/fernandes/k_centrum/correlated/$i.corr3.out
		
done